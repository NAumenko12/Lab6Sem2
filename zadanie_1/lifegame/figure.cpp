#include "life.h"

void Block(int** pole, int stroka, int stolb){
    pole[stroka][stolb] = ALIVE;
    pole[stroka][stolb + 1] = ALIVE;
    pole[stroka + 1][stolb] = ALIVE;
    pole[stroka + 1][stolb + 1] = ALIVE;
}
void Beehive(int** pole, int stroka, int stolb){
    pole[stroka][stolb + 1] = ALIVE;
    pole[stroka][stolb + 2] = ALIVE;
    pole[stroka + 1][stolb] = ALIVE;
    pole[stroka + 1][stolb + 3] = ALIVE;
    pole[stroka + 2][stolb + 1] = ALIVE;
    pole[stroka + 2][stolb + 2] = ALIVE;
}

void Loaf(int** pole, int stroka, int stolb) {
    pole[stroka][stolb + 1] = ALIVE;
    pole[stroka][stolb + 2] = ALIVE;
    pole[stroka + 1][stolb] = ALIVE;
    pole[stroka + 1][stolb + 3] = ALIVE;
    pole[stroka + 2][stolb + 1] = ALIVE;
    pole[stroka + 2][stolb + 3] = ALIVE;
    pole[stroka + 3][stolb + 2] = ALIVE;
}

void Boat(int** pole, int stroka, int stolb){
    pole[stroka][stolb] = ALIVE;
    pole[stroka][stolb + 1] = ALIVE;
    pole[stroka + 1][stolb] = ALIVE;
    pole[stroka + 1][stolb + 2] = ALIVE;
    pole[stroka + 2][stolb + 1] = ALIVE;
}

void Glider(int** pole, int stroka, int stolb){
    pole[stroka][stolb + 1] = ALIVE;
    pole[stroka + 1][stolb + 2] = ALIVE;
    pole[stroka + 2][stolb] = ALIVE;
    pole[stroka + 2][stolb + 1] = ALIVE;
    pole[stroka + 2][stolb + 2] = ALIVE;
}
