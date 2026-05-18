#include "gaus.h"

double** createMatrix(int n) {
    double** a = new double*[n];
    for (int i = 0; i < n; i++){
        a[i] = new double[n];
    }
    return a;
}

double* createMassive(int n) {
    return new double[n];
}

void deleteMatrix(double** a, int n){
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
}

void zapolnitSistem(double** a, double* b, double m, double nPar, double p) {
    double koef[4][4] = {
        {m,     -0.04,  0.21, -1.16},
        {0.25,  -1.23,  nPar, -0.09},
        {-0.21, nPar,   0.8,  -0.13},
        {0.15,  -1.31,  0.06,  p}
    };
    double svob[4] = {-1.24, p, 2.56, m};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            a[i][j] = koef[i][j];
        }
        b[i] = svob[i];
    }
}

void printSistem(double** a, double* b, int n){
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << setw(12) << a[i][j] << " ";
        }
        cout << " | " << setw(12) << b[i] << endl;
    }
}

void printKorni(double* x, int n){
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }
}

int findGlavStroku(double** a, int n, int k){
    int maxStr = k;
    for (int i = k + 1; i < n; i++){
        if (fabs(a[i][k]) > fabs(a[maxStr][k])){
            maxStr = i;
        }
    }
    return maxStr;
}

void swapStroki(double** a, double* b, int str1, int str2){
    double* vremStr = a[str1];
    a[str1] = a[str2];
    a[str2] = vremStr;
    double vrem = b[str1];
    b[str1] = b[str2];
    b[str2] = vrem;
}

void pryamoiHod(double** a, double* b, int n, double& det){
    int per {};
    det = 1.0;
    cout << "\n Прямой ход" << endl;
    for (int k = 0; k < n - 1; k++){
        int maxStr = findGlavStroku(a, n, k);
        if (maxStr != k){
            swapStroki(a, b, k, maxStr);
            per++;
        }
        for (int i = k + 1; i < n; i++){
            double q = a[i][k] / a[k][k];
            for (int j = k; j < n; j++){
                a[i][j] -= q * a[k][j];
            }
            b[i] -= q * b[k];
        }
        cout << "\n После шага " << k + 1 << ":" << endl;
        printSistem(a, b, n);
    }
    for (int i = 0; i < n; i++){
        det *= a[i][i];
    }
    if (per % 2 != 0){
        det = -det;
    }
}

void obratniyHod(double** a, double* b, double* x, int n){
    cout << "\n Обратный ход" << endl;
    for (int i = n - 1; i >= 0; i--){
        double sum = 0.0;
        for (int j = i + 1; j < n; j++){
            sum += a[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / a[i][i];
        cout << "x" << i + 1 << " = " << fixed << setprecision(6) << x[i] << endl;
    }
}

void gauss(double** a, double* b, double* x, int n){
    double det = 1.0;
    pryamoiHod(a, b, n, det);
    obratniyHod(a, b, x, n);
    cout << "\nРешение системы" << endl;
    printKorni(x, n);
    cout << "\nОпределитель " << det << endl;
}
