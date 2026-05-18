#include "arrays.h"

int findMinVStroke(int** matr, int stroka, int n){
    int min = matr[stroka][0];
    for (int j = 1; j < n; j++){
        if (matr[stroka][j] < min){
            min = matr[stroka][j];
        }
    }
    return min;
}
int findMaxVStroke(int** matr, int stroka, int n) {
    int max = matr[stroka][0];
    for (int j = 1; j < n; j++) {
        if (matr[stroka][j] > max) {
            max = matr[stroka][j];
        }
    }
    return max;
}
int poschitatRaznostMaxMin(int maxEl, int minEl) {
    return maxEl - minEl;
}
vector<int> createRaznostei(int** matr, int m, int n){
    vector<int> raznost(m);
    for (int i = 0; i < m; i++){
        int minEl = findMinVStroke(matr, i, n);
        int maxEl = findMaxVStroke(matr, i, n);
        raznost[i] = poschitatRaznostMaxMin(maxEl, minEl);
    }
    return raznost;
}

int findStrokMax(const vector<int>& raznost){
    int maxId {};
    for (int i = 1; i < raznost.size(); i++){
        if (raznost[i] > raznost[maxId]){
            maxId = i;
        }
    }
    return maxId;
}

