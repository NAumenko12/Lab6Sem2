#include "life.h"

int chetSosed(int** pole, int m, int n, int stroka, int stolb){
    int count {};
    for (int i = stroka - 1; i <= stroka + 1; i++){
        for (int j = stolb - 1; j <= stolb + 1; j++){
            if ((i != stroka || j != stolb) && i >= 0 && i < m && j >= 0 && j < n && pole[i][j] == ALIVE){
                count++;
            }
        }
    }
    return count;
}

int** nextPokolenie(int** pole, int m, int n) {
    int** newPole = createPole(m, n);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            int sosedi = chetSosed(pole, m, n, i, j);
            if(pole[i][j] == ALIVE){
                if (sosedi == 2 || sosedi == 3){
                    newPole[i][j] = ALIVE;
                } else {
                    newPole[i][j] = DEAD;
                }
            }else{
                if (sosedi == 3){
                    newPole[i][j] = ALIVE;
                } else{
                    newPole[i][j] = DEAD;
                }
            }
        }
    }
    return newPole;
}
