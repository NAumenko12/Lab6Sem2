#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>
using namespace std;

int** createMatrix(int M, int N);
void deleteMatrix(int** matrix, int M);
void fillRandom(int** matrix, int M, int N, int minVal, int maxVal);
void printMatrix(int** matrix, int M, int N);
int** switchMinMaxInRows(int** matrix, int M, int N);
vector<int> createDiffArray(int** matrix, int M, int N);
int findMaxDiffRow(const vector<int>& diff);
int digitSum(int number);
int findMaxDigitSumRow(int** matrix, int M, int N);

// Life Game MOYA LUBIMAYA

int** createField(int rows, int cols);
void deleteField(int** field, int rows);
void clearField(int** field, int rows, int cols);
void fillRandom(int** field, int rows, int cols);
void printField(int** field, int rows, int cols);
void clearConsole();
int countNeighbors(int** field, int rows, int cols, int row, int col);
int** nextGeneration(int** field, int rows, int cols);
void setBlock(int** field, int row, int col);
void setBeehive(int** field, int row, int col);
void setLoaf(int** field, int row, int col);
void setBoat(int** field, int row, int col);
void runAnimation(int** field, int rows, int cols, int generations, int delayMs);