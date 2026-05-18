#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unistd.h>
using namespace std;

const int DEAD = 0;
const int ALIVE = 1;

int** createPole(int m, int n);
void deletePole(int** pole, int m);
void clearPole(int** pole, int m, int n);
void zapolnitRandom(int** pole, int m, int n);
void printPole(int** pole, int m, int n);
int chetSosed(int** pole, int m, int n, int stroka, int stolb);
int** nextPokolenie(int** pole, int m, int n);
void Block(int** pole, int stroka, int stolb);
void Beehive(int** pole, int stroka, int stolb);
void Loaf(int** pole, int stroka, int stolb);
void Boat(int** pole, int stroka, int stolb);
void clearKonsol();
void zapuskAnim(int** pole, int m, int n, int pokoleniya, int pauza);
