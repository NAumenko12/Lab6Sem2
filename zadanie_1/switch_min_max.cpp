#include "arrays.h"

int** pomenyatMinMaxStrok(int** matr, int m, int n){
    for (int i = 0; i < m; i++){
        int minInd = 0;
        int maxInd = 0;
        for (int j = 1; j < n; j++) {
            if (matr[i][j] < matr[i][minInd]){
                minInd = j;
            } 
            if (matr[i][j] > matr[i][maxInd]){
                maxInd = j;
            } 
        }
        swap(matr[i][minInd], matr[i][maxInd]);
    }
    return matr;
}
