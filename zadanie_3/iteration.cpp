#include "gaus.h"

double rowQ(double** a, int row, int diagCol, int n){
    if (fabs(a[row][diagCol]) < 1e-12){
        return 1e100;
    }
    double sum = 0.0;
    for (int j = 0; j < n; j++){
        if (j != diagCol){
            sum += fabs(a[row][j] / a[row][diagCol]);
        }
    }
    return sum;
}

void findBestPermutationRec(double** a, int n, int col, int* perm, int* used, int* bestPerm, double& bestQ){
    if (col == n){
        double q = 0.0;
        for (int i = 0; i < n; i++){
            double current = rowQ(a, perm[i], i, n);
            if (current > q){
                q = current;
            }
        }
        if (q < bestQ){
            bestQ = q;
            for (int i = 0; i < n; i++){
                bestPerm[i] = perm[i];
            }
        }
        return;
    }
    for (int row = 0; row < n; row++){
        if (used[row] == 0){
            used[row] = 1;
            perm[col] = row;
            findBestPermutationRec(a, n, col + 1, perm, used, bestPerm, bestQ);
            used[row] = 0;
        }
    }
}

void findBestPermutation(double** a, int n, int* bestPerm, double& bestQ){
    int* perm = new int[n];
    int* used = new int[n];
    for (int i = 0; i < n; i++){
        perm[i] = 0;
        used[i] = 0;
        bestPerm[i] = i;
    }
    bestQ = 1e100;
    findBestPermutationRec(a, n, 0, perm, used, bestPerm, bestQ);
    delete[] perm;
    delete[] used;
}

void makeCanonical(double** a, double* b, double** c, double* f, int* perm, int n){
    for (int i = 0; i < n; i++){
        int row = perm[i];
        f[i] = b[row] / a[row][i];
        for (int j = 0; j < n; j++){
            if (i == j){
                c[i][j] = 0.0;
            } else {
                c[i][j] = -a[row][j] / a[row][i];
            }
        }
    }
}

double normMatrix(double** c, int n){
    double q = 0.0;
    for (int i = 0; i < n; i++){
        double sum = 0.0;
        for (int j = 0; j < n; j++){
            sum += fabs(c[i][j]);
        }
        if (sum > q){
            q = sum;
        }
    }
    return q;
}

double maxRaznost(double* x1, double* x2, int n){
    double maxDiff = 0.0;
    for (int i = 0; i < n; i++){
        double diff = fabs(x1[i] - x2[i]);
        if (diff > maxDiff){
            maxDiff = diff;
        }
    }
    return maxDiff;
}

void printCanonical(double** c, double* f, int n){
    cout << "\nКанонический вид x = Cx + f" << endl;
    cout << "Матрица C:" << endl;
    printSistem(c, f, n);
}
void printIterationHeader(int n){
    cout << "\nТаблица итераций:" << endl;
    cout << setw(6) << "N";
    for (int i = 0; i < n; i++){
        cout << setw(14) << ("X" + to_string(i + 1));
    }
    cout << setw(16) << "eps_n" << endl;
}
void simpleIteration(double** a, double* b, int n, double eps){
    cout << "\nМетод простой итерации" << endl;
    int* perm = new int[n];
    double bestQ {};
    findBestPermutation(a, n, perm, bestQ);
    double** c = createMatrix(n);
    double* f = createMassive(n);
    makeCanonical(a, b, c, f, perm, n);
    double q = normMatrix(c, n);
    printCanonical(c, f, n);
    cout << "\nНорма C = " << fixed << setprecision(6) << q << endl;
    if (q < 1.0){
        cout << "Условие сходимости выполнено: C < 1" << endl;
    } else {
        cout << "Условие сходимости не выполнено: C >= 1" << endl;
        cout << "Итерации могут не сходиться для выбранных параметров." << endl;
    }
    double* xOld = createMassive(n);
    double* xNew = createMassive(n);
    for (int i = 0; i < n; i++){
        xOld[i] = f[i];
    }
    printIterationHeader(n);
    cout << setw(6) << 0;
    for (int i = 0; i < n; i++){
        cout << setw(14) << fixed << setprecision(6) << xOld[i];
    }
    cout << setw(16) << "-" << endl;
    int k = 0;
    double pogreshnost = eps + 1.0;
    const int maxIterations = 1000;
    while (pogreshnost > eps && k < maxIterations){
        for (int i = 0; i < n; i++){
            double sum = f[i];
            for (int j = 0; j < n; j++){
                sum += c[i][j] * xOld[j];
            }
            xNew[i] = sum;
        }
        pogreshnost = maxRaznost(xNew, xOld, n);
        k++;
        cout << setw(6) << k;
        for (int i = 0; i < n; i++){
            cout << setw(14) << fixed << setprecision(6) << xNew[i];
        }
        cout << setw(16) << fixed << setprecision(6) << pogreshnost << endl;
        for (int i = 0; i < n; i++){
            xOld[i] = xNew[i];
        }
    }
    cout << "\nРешение методом простой итерации" << endl;
    printKorni(xOld, n);
    cout << "Количество итераций: " << k << endl;
    if (k == maxIterations && pogreshnost > eps){
        cout << "Достигнут предел итераций, требуемая точность не получена." << endl;
    }
    delete[] perm;
    deleteMatrix(c, n);
    delete[] f;
    delete[] xOld;
    delete[] xNew;
}
