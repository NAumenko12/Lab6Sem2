#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int** createMatrix(int n, int m);
void deleteMatrix(int** a, int n);
void zapolitMatrix(int** a, int n, int m);
void printMatrix(int** a, int n, int m);
int minHodovRisunka(int** a, int n, int m, int verh);
int minHodovDoPolovini(int** a, int n, int m);
int findBestVerh(int** a, int n, int m);
void printItogMatrix(int n, int m, int verh);
