#include "gaus.h"

int main(){
    const int n = 4;
    double m {};
    double nPar {};
    double p {};
    double eps {};
    cout << "Vvedite M: ";
    cin >> m;
    cout << "Vvedite N: ";
    cin >> nPar;
    cout << "Vvedite P: ";
    cin >> p;
    cout << "Vvedite epsilon: ";
    cin >> eps;
    double** a = createMatrix(n);
    double** iterA = createMatrix(n);
    double* b = createMassive(n);
    double* iterB = createMassive(n);
    double* x = createMassive(n);
    zapolnitSistem(a, b, m, nPar, p);
    copySistem(a, b, iterA, iterB, n);
    cout << "\nIshodnaya sistema:" << endl;
    printSistem(a, b, n);
    gauss(a, b, x, n);
    simpleIteration(iterA, iterB, n, eps);
    deleteMatrix(a, n);
    deleteMatrix(iterA, n);
    delete[] b;
    delete[] iterB;
    delete[] x;
    return 0;
}
