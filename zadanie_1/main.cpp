#include <iostream>
#include <vector>
#include "arrays.h"

using namespace std;

int main() {
    // задание 1
    int M{};
    int N{};
    cout << "Введите M: ";
    cin >> M;
    cout << "Введите N: ";
    cin >> N;
    int** matrix1 = createMatrix(M, N);
    fillRandom(matrix1, M, N, 10, 50);
    cout << "\nМатрица 1 до изменения:\n";
    printMatrix(matrix1, M, N);
    matrix1 = switchMinMaxInRows(matrix1, M, N);
    cout << "\nМатрица 1 после изменения:\n";
    printMatrix(matrix1, M, N);
    vector<int> diff = createDiffArray(matrix1, M, N);
    cout << "\nМассив разностей:\n";
    for (int value : diff) {
        cout << value << " ";
    }
    cout << endl;
    int maxDiffRow = findMaxDiffRow(diff);
    cout << "Номер строки с максимальной разностью: "<< maxDiffRow + 1 << endl;
    deleteMatrix(matrix1, M);
    // Задание 2
    int** matrix2 = createMatrix(M, N);
    fillRandom(matrix2, M, N, 100, 200);
    cout << "\nМатрица 2:\n";
    printMatrix(matrix2, M, N);
    int maxDigitSumRow = findMaxDigitSumRow(matrix2, M, N);
    cout << "Номер строки с наибольшей суммой цифр: "<< maxDigitSumRow + 1 << endl;
    deleteMatrix(matrix2, M);
    // Задание 3 
    int rows{};
    int cols{};
    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;
    int** stableField = createField(rows, cols);
    setBlock(stableField, 2, 2);
    setBeehive(stableField, 2, 10);
    setLoaf(stableField, 8, 2);
    setBoat(stableField, 8, 12);
    runAnimation(stableField, rows, cols, 10, 700);
    int** randomField = createField(rows, cols);
    fillRandom(randomField, rows, cols);
    runAnimation(randomField, rows, cols, 100, 300);
    return 0;
}