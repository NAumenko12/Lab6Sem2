#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

double** createMatrix(int n);
double* createMassive(int n);
void deleteMatrix(double** a, int n);
void zapolnitSistem(double** a, double* b, double m, double nPar, double p);
void printSistem(double** a, double* b, int n);
void printKorni(double* x, int n);
void copySistem(double** fromA, double* fromB, double** toA, double* toB, int n);

int findGlavStroku(double** a, int n, int k);
void swapStroki(double** a, double* b, int str1, int str2);
void pryamoiHod(double** a, double* b, int n, double& det);
void obratniyHod(double** a, double* b, double* x, int n);
void gauss(double** a, double* b, double* x, int n);
void simpleIteration(double** a, double* b, int n, double eps);
