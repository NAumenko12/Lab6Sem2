#include "coin.h"

int main() {
    int N{};
    int M{};
    cout << "Введите N: ";
    cin >> N;
    cout << "Введите M: ";
    cin >> M;
    int** matrix = createMatrix(N, M);
    cout << "Введите матрицу из 0 и 1:" << endl;
    inputMatrix(matrix, N, M);
    cout << endl << "Исходная матрица:" << endl;
    printMatrix(matrix, N, M);
    int result = minMovesToHalf(matrix, N, M);
    if (result >= 1000000) {
        cout << "Получить нужный рисунок невозможно" << endl;
    } else {
        cout << "Результат: " << result << endl;
    }
    deleteMatrix(matrix, N);
    return 0;
}