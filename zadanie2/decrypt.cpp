#include "aes.h"

void decryptBlock(const Byte input[16], Byte output[16], const vector<vector<Byte>>& roundKeys, int blockNumber){
    Byte state[4][4];
    bytesToState(input, state);
    printState(state, "\nРасшифрование блока " + to_string(blockNumber) + ". Начальное состояние State ");
    addRoundKey(state, roundKeys[10]);
    for (int round = 9; round >= 1; round--){
        invShiftRows(state);
        invSubBytes(state);
        addRoundKey(state, roundKeys[round]);
        invMixColumns(state);
        printState(state, "После раунда расшифрования " + to_string(round) + " ");
    }
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, roundKeys[0]);
    printState(state, "Финальное расшифрованное состояние State ");
    stateToBytes(state, output);
}

vector<Byte> decryptCBC(const vector<Byte>& cipher, const vector<Byte>& key, const vector<Byte>& iv){
    vector<Byte> result;
    vector<Byte> prev = iv;
    vector<vector<Byte>> roundKeys = expandKey(key);
    for (int block = 0; block < (int)cipher.size(); block += BLOCK_SIZE){
        Byte input[16];
        Byte output[16];
        for (int i = 0; i < BLOCK_SIZE; i++){
            input[i] = cipher[block + i];
        }
        decryptBlock(input, output, roundKeys, block / BLOCK_SIZE + 1);
        for (int i = 0; i < BLOCK_SIZE; i++){
            result.push_back(output[i] ^ prev[i]);
            prev[i] = input[i];
        }
    }
    removePadding(result);
    return result;
}
