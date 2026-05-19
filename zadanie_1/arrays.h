#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;
//zadanie 1
int** create(int m, int n);
void deletee(int** matr, int m);
void zapolnit(int** matr, int m, int n, int minZn, int maxZn);
void print(int** matr, int m, int n);
int** pomenyatMinMaxStrok(int** matr, int m, int n);

vector<int> createRaznostei(int** matr, int m, int n);
int findStrokMax(const vector<int>& raznost);

//zadani 2
int sumCifr(int chislo);
int findMaxSumCifrStrok(int** matr, int m, int n);

