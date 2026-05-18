#include <iostream>
#include <vector>
#include "arrays.h"

using namespace std;

int main() {
    // Zadanie 1 предложение 1
    int m {};
    int n {};
    cout << "Введите M: ";
    cin >> m;
    cout << "Введите N: ";
    cin >> n;
    int** matr1 = create(m, n);
    zapolnit(matr1, m, n, 10, 50);
    cout << "\nМатрица 1 до\n";
    print(matr1, m, n);
    pomenyatMinMaxStrok(matr1, m, n);
    cout << "\nМатрица 1 после\n";
    print(matr1, m, n);
    //zad 1 предлож 2

    vector<int> razn = createRaznostei(matr1, m, n);
    cout << "\nМассив разностей:\n";
    for (int elem : razn) {
        cout << elem << " ";
    }
    cout << endl;
    int nomerStr = findStrokMax(razn);
    cout << "Номер строки с максимальной разностью: " << nomerStr + 1 << endl;
    deletee(matr1, m);
    // Zadanie 2
    int** matr2 = create(m, n);
    zapolnit(matr2, m, n, 100, 200);
    cout << "\nМатрица 2:\n";
    print(matr2, m, n);
    int maxSumStr = findMaxSumCifrStrok(matr2, m, n);
    cout << "Номер строки с наибольшей суммой цифр: " << maxSumStr + 1 << endl;
    deletee(matr2, m);
    return 0;
}
