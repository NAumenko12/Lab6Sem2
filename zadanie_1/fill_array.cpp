#include "arrays.h"

int** createMatrix(int M, int N){
    int** matrix = new int*[M];
    for (int i = 0; i < M; i++){
        matrix[i] = new int[N];
    }
    return matrix;
}
void deleteMatrix(int** matrix, int M){
    for (int i = 0; i < M; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
void fillRandom(int** matrix, int M, int N, int minVal, int maxVal){
    static random_device rd;
    static ranlux24_base gen(rd());
    uniform_int_distribution<int> dist(minVal, maxVal);
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            matrix[i][j] = dist(gen);
        }
    }
}

void printMatrix(int** matrix, int M, int N){
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}