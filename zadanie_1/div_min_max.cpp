#include "arrays.h"

vector<int> createDiffArray(int** matrix, int M, int N) {
    vector<int> diff(M);
    for (int i = 0; i < M; i++) {
        int minVal = matrix[i][0];
        int maxVal = matrix[i][0];
        for (int j = 1; j < N; j++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
            }
        }
        diff[i] = maxVal - minVal;
    }
    return diff;
}

int findMaxDiffRow(const vector<int>& diff) {
    int maxIndex {};
    int maxValue = diff[0];
    int index {};
    for (int value : diff) {
        if (value > maxValue) {
            maxValue = value;
            maxIndex = index;
        }
        index++;
    }
    return maxIndex;
}

int digitSum(int number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int findMaxDigitSumRow(int** matrix, int M, int N) {
    int maxRow = 0;
    int maxSum = 0;
    for (int j = 0; j < N; j++) {
        maxSum += digitSum(matrix[0][j]);
    }
    for (int i = 1; i < M; i++) {
        int rowSum = 0;
        for (int j = 0; j < N; j++) {
            rowSum += digitSum(matrix[i][j]);
        }
        if (rowSum > maxSum) {
            maxSum = rowSum;
            maxRow = i;
        }
    }
    return maxRow;
}