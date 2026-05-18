#include "coin.h"

int** createMatrix(int n, int m){
    int** a = new int*[n];
    for (int i = 0; i < n; i++){
        a[i] = new int[m];
    }
    return a;
}

void deleteMatrix(int** a, int n){
    for (int i = 0; i < n; i++){
        delete[] a[i];
    }
    delete[] a;
}

void zapolitMatrix(int** a, int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
}

void printMatrix(int** a, int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int rastMinHodov(int stroka1, int stolb1, int stroka2, int stolb2){
    int raznostStrok = stroka1 - stroka2;
    int raznostStolb = stolb1 - stolb2;
    if (raznostStrok < 0){
        raznostStrok = -raznostStrok;
    }
    if (raznostStolb < 0){
        raznostStolb = -raznostStolb;
    }
    return raznostStrok + raznostStolb;
}

int findNepravilnieKletki(int** a, int n, int m, int verh, int* stroki, int* stolbci){
    int count{};
    int niz = 1 - verh;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            int nado{};
            if (i < n / 2) {
                nado = verh;
            } else {
                nado = niz;
            }
            if (a[i][j] != nado){
                stroki[count] = i;
                stolbci[count] = j;
                count++;
            }
        }
    }
    return count;
}

int findFirstFalseEl(int* used, int count){
    int indOfEl = -1;
    for (int i = 0; i < count; i++){
        if (used[i] == 0 && indOfEl == -1){
            indOfEl = i;
        }
    }
    return indOfEl;
}

int podborPar(int* stroki, int* stolbci, int* used, int count){
    int first = findFirstFalseEl(used, count);
    int best {};
    if (first != -1){
        used[first] = 1;
        bool isVariant = false;
        for (int i = 0; i < count; i++){
            if (used[i] == 0) {
                used[i] = 1;
                int cena = rastMinHodov(stroki[first], stolbci[first], stroki[i], stolbci[i]);
                int tek = cena + podborPar(stroki, stolbci, used, count);
                if (!isVariant || tek < best) {
                    best = tek;
                    isVariant = true;
                }
                used[i] = 0;
            }
        }
        used[first] = 0;
    }
    return best;
}

int minHodovRisunka(int** a, int n, int m, int verh){
    int* stroki = new int[n * m];
    int* stolbci = new int[n * m];
    int count = findNepravilnieKletki(a, n, m, verh, stroki, stolbci);
    int otvet {-1};
    if (count % 2 == 0){
        int* used = new int[count];
        for (int i = 0; i < count; i++){
            used[i] = 0;
        }
        otvet = podborPar(stroki, stolbci, used, count);
        delete[] used;
    }
    delete[] stroki;
    delete[] stolbci;
    return otvet;
}

int minHodovDoPolovini(int** a, int n, int m){
    int otvet1 = minHodovRisunka(a, n, m, 0);
    int otvet2 = minHodovRisunka(a, n, m, 1);
    int otvet = -1;
    if (otvet1 != -1 && otvet2 != -1){
        otvet = min(otvet1, otvet2);
    } else if (otvet1 != -1){
        otvet = otvet1;
    } else if (otvet2 != -1){
        otvet = otvet2;
    }
    return otvet;
}

int findBestVerh(int** a, int n, int m){
    int otvet1 = minHodovRisunka(a, n, m, 0);
    int otvet2 = minHodovRisunka(a, n, m, 1);
    int verh = -1;
    if (otvet1 != -1 && otvet2 != -1){
        if (otvet1 <= otvet2){
            verh = 0;
        } else {
            verh = 1;
        }
    } else if (otvet1 != -1){
        verh = 0;
    } else if (otvet2 != -1){
        verh = 1;
    }

    return verh;
}

void printItogMatrix(int n, int m, int verh){
    int niz = 1 - verh;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (i < n / 2){
                cout << verh << " ";
            } else {
                cout << niz << " ";
            }
        }
        cout << endl;
    }
}
