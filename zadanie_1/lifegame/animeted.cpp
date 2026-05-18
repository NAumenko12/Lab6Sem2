#include "life.h"

void clearKonsol() {
    system("clear");
}
    
void zapuskAnim(int** pole, int m, int n, int pokoleniya, int pauza){
    for (int i = 0; i < pokoleniya; i++) {
        clearKonsol();
        cout << "Pokolenie: " << i + 1 << endl;
        printPole(pole, m, n);
        usleep(pauza * 1000);
        int** newPole = nextPokolenie(pole, m, n);
        deletePole(pole, m);
        pole = newPole;
    }
    deletePole(pole, m);
}