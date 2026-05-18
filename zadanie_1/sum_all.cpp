#include "arrays.h"

int sumCifr(int chislo){
    int summa = 0;
    while (chislo > 0){
        summa += chislo % 10;
        chislo /= 10;
    }
    return summa;
}

int sumCifrStrok(int** matr, int stroka, int n){
    int sum {};
    for (int i = 0; i < n; i++) {
        sum += sumCifr(matr[stroka][i]);
    }
    return sum;
}

int findMaxSumCifrStrok(int** matr, int m, int n) {
    int maxInd {};
    int maxSum = sumCifrStrok(matr, 0, n);
    for (int i = 1; i < m; i++) {
        int sumStr = sumCifrStrok(matr, i, n);
        if (sumStr > maxSum) {
            maxSum = sumStr;
            maxInd = i;
        }
    }
    return maxInd;
}
