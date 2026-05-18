#include "gaus.h"

int main(){
    const int n = 4;
    double m {};
    double nPar {};
    double p {};
    cout << "Vvedite M: ";
    cin >> m;
    cout << "Vvedite N: ";
    cin >> nPar;
    cout << "Vvedite P: ";
    cin >> p;
    double** a = createMatrix(n);
    double* b = createMassive(n);
    double* x = createMassive(n);
    zapolnitSistem(a, b, m, nPar, p);
    cout << "\nIshodnaya sistema:" << endl;
    printSistem(a, b, n);
    gauss(a, b, x, n);
    deleteMatrix(a, n);
    delete[] b;
    delete[] x;
    return 0;
}
