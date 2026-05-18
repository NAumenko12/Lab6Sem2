#include "life.h"

int** createPole(int m, int n){
    int** pole = new int*[m];
    for (int i = 0; i < m; i++){
        pole[i] = new int[n];
    }
    clearPole(pole, m, n);
    return pole;
}

void deletePole(int** pole, int m){
    for (int i = 0; i < m; i++){
        delete[] pole[i];
    }
    delete[] pole;
}

void printPole(int** pole, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            cout << pole[i][j] << " ";
        }
        cout << endl;
    }
}

void clearPole(int** pole, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            pole[i][j] = DEAD;
        }
    }
}

void zapolnitRandom(int** pole, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (rand() % 4 == 0){
                pole[i][j] = ALIVE;
            }else{
                pole[i][j] = DEAD;
            }
        }
    }
}
