#pragma once

#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

using Byte = unsigned char;

const int BLOCK_SIZE = 16;
const int ROUND_COUNT = 10;
const int ROUND_KEY_COUNT = 11;
extern const Byte sbox[256];
extern const Byte invSbox[256];
extern const Byte rcon[11];

vector<Byte> generateRandomBytes(int size);
void saveBytesToFile(const vector<Byte>& data, const string& filename);
vector<Byte> readBytesFromFile(const string& filename);

string readTextFromConsole();
string readTextFromFile(const string& filename);
void writeTextToFile(const string& filename, const string& text);

vector<Byte> stringToBytes(const string& text);
string bytesToString(const vector<Byte>& data);

string bytesToHex(const vector<Byte>& data);
vector<Byte> hexToBytes(const string& hex);
void printBytesHex(const vector<Byte>& data, const string& title);

vector<vector<Byte>> expandKey(const vector<Byte>& key);
void printRoundKeys(const vector<vector<Byte>>& roundKeys);

void addPadding(vector<Byte>& data);
void removePadding(vector<Byte>& data);

void bytesToState(const Byte input[16], Byte state[4][4]);
void stateToBytes(Byte state[4][4], Byte output[16]);
void printState(Byte state[4][4], const string& title);

void addRoundKey(Byte state[4][4], const vector<Byte>& roundKey);
void subBytes(Byte state[4][4]);
void invSubBytes(Byte state[4][4]);
void shiftRows(Byte state[4][4]);
void invShiftRows(Byte state[4][4]);
void mixColumns(Byte state[4][4]);
void invMixColumns(Byte state[4][4]);

vector<Byte> encryptCBC(const vector<Byte>& text, const vector<Byte>& key, const vector<Byte>& iv);
vector<Byte> decryptCBC(const vector<Byte>& cipher, const vector<Byte>& key, const vector<Byte>& iv);
void encryptBlock(const Byte input[16], Byte output[16], const vector<vector<Byte>>& roundKeys, int blockNumber);
void decryptBlock(const Byte input[16], Byte output[16], const vector<vector<Byte>>& roundKeys, int blockNumber);
