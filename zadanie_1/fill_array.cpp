#include "arrays.h"

int** create(int m, int n) {
    int** matr = new int*[m];
    for (int i = 0; i < m; i++){
        matr[i] = new int[n];
    }
    return matr;
}

void deletee(int** matr, int m){
    for (int i = 0; i < m; i++){
        delete[] matr[i];
    }
    delete[] matr;
}

void zapolnit(int** matr, int m, int n, int minZn, int maxZn) {
    static random_device rd;
    static ranlux24_base gen(rd());
    uniform_int_distribution<int> dist(minZn, maxZn);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            matr[i][j] = dist(gen);
        }
    }
}

void print(int** matr, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            cout << matr[i][j] << " ";
        }
        cout << endl;
    }
}
