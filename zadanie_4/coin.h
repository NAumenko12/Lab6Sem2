#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int** createMatrix(int N, int M);
void deleteMatrix(int** matrix, int N);
void inputMatrix(int** matrix, int N, int M);
void printMatrix(int** matrix, int N, int M);
int minMovesToHalf(int** matrix, int N, int M);