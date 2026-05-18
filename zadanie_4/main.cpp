#include "coin.h"

int main() {
    int n{};
    int m{};
    cout << "Введите N ";
    cin >> n;
    cout << "Введите M ";
    cin >> m;
    int** a = createMatrix(n, m);
    cout << "Введите матрицу из 0 и 1:" << endl;
    zapolitMatrix(a, n, m);
    cout << endl << "Исходная матрица" << endl;
    printMatrix(a, n, m);
    int verh = findBestVerh(a, n, m);
    cout << "Результат: " << minHodovDoPolovini(a, n, m) << endl;
    cout << "Итоговая матрица:" << endl;
    printItogMatrix(n, m, verh);
    deleteMatrix(a, n);
    return 0;
}
