#include "coin.h"

int** createMatrix(int N, int M) {
    int** matrix = new int*[N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[M];
    }
    return matrix;
}

void deleteMatrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void inputMatrix(int** matrix, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matrix[i][j];
        }
    }
}

void printMatrix(int** matrix, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int distanceCells(pair<int, int> a, pair<int, int> b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int findMinPairing(vector<pair<int, int>>& cells, vector<int>& used) {
    int first = -1;
    for (int i = 0; i < cells.size(); i++) {
        if (!used[i]) {
            first = i;
            break;
        }
    }
    if (first == -1) {
        return 0;
    }
    used[first] = 1;
    int best = 1000000;
    for (int i = 0; i < cells.size(); i++) {
        if (!used[i]) {
            used[i] = 1;
            int current = distanceCells(cells[first], cells[i]) + findMinPairing(cells, used);
            best = min(best, current);
            used[i] = 0;
        }
    }
    used[first] = 0;
    return best;
}

int minMovesForVariant(int** matrix, int N, int M, int topValue) {
    vector<pair<int, int>> cells;
    int bottomValue = 1 - topValue;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int need;
            if (i < N / 2) {
                need = topValue;
            } else {
                need = bottomValue;
            }
            if (matrix[i][j] != need) {
                cells.push_back({i, j});
            }
        }
    }
    if (cells.size() % 2 != 0) {
        return 1000000;
    }
    vector<int> used(cells.size(), 0);
    return findMinPairing(cells, used);
}

int minMovesToHalf(int** matrix, int N, int M) {
    int result1 = minMovesForVariant(matrix, N, M, 0);
    int result2 = minMovesForVariant(matrix, N, M, 1);
    return min(result1, result2);
}