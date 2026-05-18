#include "aes.h"

void encryptBlock(const Byte input[16], Byte output[16], const vector<vector<Byte>>& roundKeys, int blockNumber){
    Byte state[4][4];
    bytesToState(input, state);
    printState(state, "\nБлок " + to_string(blockNumber) + ". Начальное состояние State ");
    addRoundKey(state, roundKeys[0]);
    printState(state, "После AddRoundKey 0 ");
    for (int round = 1; round <= 9; round++){
        subBytes(state);
        printState(state, "После SubBytes " + to_string(round) + " ");
        shiftRows(state);
        printState(state, "После ShiftRows " + to_string(round) + " ");
        mixColumns(state);
        printState(state, "После MixColumns " + to_string(round) + " ");
        addRoundKey(state, roundKeys[round]);
        printState(state, "После AddRoundKey " + to_string(round) + " ");
    }
    subBytes(state);
    shiftRows(state);
    addRoundKey(state, roundKeys[10]);
    printState(state, "Финальное зашифрованное состояние State ");
    stateToBytes(state, output);
}

vector<Byte> encryptCBC(const vector<Byte>& text, const vector<Byte>& key, const vector<Byte>& iv){
    vector<Byte> data = text;
    vector<Byte> result;
    vector<Byte> prev = iv;
    vector<vector<Byte>> roundKeys = expandKey(key);
    addPadding(data);
    for (int block = 0; block < (int)data.size(); block += BLOCK_SIZE){
        Byte input[16];
        Byte output[16];
        for (int i = 0; i < BLOCK_SIZE; i++){
            input[i] = data[block + i] ^ prev[i];
        }
        encryptBlock(input, output, roundKeys, block / BLOCK_SIZE + 1);
        for (int i = 0; i < BLOCK_SIZE; i++){
            result.push_back(output[i]);
            prev[i] = output[i];
        }
    }
    return result;
}
