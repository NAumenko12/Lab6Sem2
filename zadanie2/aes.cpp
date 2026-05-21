#include "aes.h"


vector<Byte> generateRandomBytes(int size){
    vector<Byte> data(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 255);
    for (int i = 0; i < size; i++){
        data[i] = (Byte)dist(gen);
    }
    return data;
}

void addPadding(vector<Byte>& data){
    int count = BLOCK_SIZE - ((int)data.size() % BLOCK_SIZE);
    if (count == 0){
        count = BLOCK_SIZE;
    }
    for (int i = 0; i < count; i++){
        data.push_back((Byte)count);
    }
}

void removePadding(vector<Byte>& data){
    if (data.empty()){
        return;
    }
    int count = data.back();
    if (count > 0 && count <= BLOCK_SIZE && count <= (int)data.size()){
        for (int i = 0; i < count; i++){
            data.pop_back();
        }
    }
}

Byte gmul(Byte a, Byte b){
    Byte p = 0;
    for (int i = 0; i < 8; i++){
        if (b & 1){
            p ^= a;
        }
        bool hiBit = a & 0x80;
        a <<= 1;
        if (hiBit){
            a ^= 0x1b;
        }
        b >>= 1;
    }
    return p;
}

void bytesToState(const Byte input[16], Byte state[4][4]){
    for (int col = 0; col < 4; col++){
        for (int row = 0; row < 4; row++){
            state[row][col] = input[col * 4 + row];
        }
    }
}

void stateToBytes(Byte state[4][4], Byte output[16]){
    for (int col = 0; col < 4; col++){
        for (int row = 0; row < 4; row++){
            output[col * 4 + row] = state[row][col];
        }
    }
}

void printState(Byte state[4][4], const string& title){
    cout << title << endl;
    cout << hex << setfill('0');
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            cout << setw(2) << (int)state[i][j] << " ";
        }
        cout << endl;
    }
    cout << dec << setfill(' ');
}

void addRoundKey(Byte state[4][4], const vector<Byte>& roundKey){
    for (int col = 0; col < 4; col++){
        for (int row = 0; row < 4; row++){
            state[row][col] ^= roundKey[col * 4 + row];
        }
    }
}

void subBytes(Byte state[4][4]){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            state[i][j] = sbox[state[i][j]];
        }
    }
}

void invSubBytes(Byte state[4][4]){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            state[i][j] = invSbox[state[i][j]];
        }
    }
}

void shiftRows(Byte state[4][4]){
    Byte temp[4];
    for (int row = 1; row < 4; row++){
        for (int col = 0; col < 4; col++){
            temp[col] = state[row][(col + row) % 4];
        }
        for (int col = 0; col < 4; col++){
            state[row][col] = temp[col];
        }
    }
}

void invShiftRows(Byte state[4][4]){
    Byte temp[4];
    for (int row = 1; row < 4; row++){
        for (int col = 0; col < 4; col++){
            temp[(col + row) % 4] = state[row][col];
        }
        for (int col = 0; col < 4; col++){
            state[row][col] = temp[col];
        }
    }
}

void mixColumns(Byte state[4][4]){
    for (int col = 0; col < 4; col++){
        Byte a0 = state[0][col];
        Byte a1 = state[1][col];
        Byte a2 = state[2][col];
        Byte a3 = state[3][col];
        state[0][col] = gmul(a0, 2) ^ gmul(a1, 3) ^ a2 ^ a3;
        state[1][col] = a0 ^ gmul(a1, 2) ^ gmul(a2, 3) ^ a3;
        state[2][col] = a0 ^ a1 ^ gmul(a2, 2) ^ gmul(a3, 3);
        state[3][col] = gmul(a0, 3) ^ a1 ^ a2 ^ gmul(a3, 2);
    }
}

void invMixColumns(Byte state[4][4]){
    for (int col = 0; col < 4; col++){
        Byte a0 = state[0][col];
        Byte a1 = state[1][col];
        Byte a2 = state[2][col];
        Byte a3 = state[3][col];
        state[0][col] = gmul(a0, 14) ^ gmul(a1, 11) ^ gmul(a2, 13) ^ gmul(a3, 9);
        state[1][col] = gmul(a0, 9) ^ gmul(a1, 14) ^ gmul(a2, 11) ^ gmul(a3, 13);
        state[2][col] = gmul(a0, 13) ^ gmul(a1, 9) ^ gmul(a2, 14) ^ gmul(a3, 11);
        state[3][col] = gmul(a0, 11) ^ gmul(a1, 13) ^ gmul(a2, 9) ^ gmul(a3, 14);
    }
}
vector<vector<Byte>> expandKey(const vector<Byte>& key){
    vector<Byte> expanded(176);
    for (int i = 0; i < 16; i++){
        expanded[i] = key[i];
    }
    int bytesGenerated = 16;
    int rconIter = 1;
    Byte temp[4];
    while (bytesGenerated < 176){
        for (int i = 0; i < 4; i++){
            temp[i] = expanded[bytesGenerated - 4 + i];
        }
        if (bytesGenerated % 16 == 0){
            Byte first = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = first;
            for (int i = 0; i < 4; i++){
                temp[i] = sbox[temp[i]];
            }
            temp[0] ^= rcon[rconIter];
            rconIter++;
        }
        for (int i = 0; i < 4; i++){
            expanded[bytesGenerated] = expanded[bytesGenerated - 16] ^ temp[i];
            bytesGenerated++;
        }
    }
    vector<vector<Byte>> roundKeys(11, vector<Byte>(16));
    for (int r = 0; r < 11; r++){
        for (int i = 0; i < 16; i++){
            roundKeys[r][i] = expanded[r * 16 + i];
        }
    }
    return roundKeys;
}

void printRoundKeys(const vector<vector<Byte>>& roundKeys){
    for (int i = 0; i < (int)roundKeys.size(); i++){
        cout << "Раундовый ключ " << i << ": " << bytesToHex(roundKeys[i]) << endl;
    }
}
