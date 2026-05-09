#include "arrays.h"

#include "arrays.h"

int** switchMinMaxInRows(int** matrix, int M, int N) {
    for (int i = 0; i < M; i++) {
        int minIndex {};
        int maxIndex {};
        for (int j = 1; j < N; j++) {
            if (matrix[i][j] < matrix[i][minIndex]) {
                minIndex = j;
            }
            if (matrix[i][j] > matrix[i][maxIndex]) {
                maxIndex = j;
            }
        }
        int temp = matrix[i][minIndex];
        matrix[i][minIndex] = matrix[i][maxIndex];
        matrix[i][maxIndex] = temp;
    }
    return matrix;
}