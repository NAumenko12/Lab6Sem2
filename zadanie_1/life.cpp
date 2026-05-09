#include "arrays.h"

using namespace std;

int** createField(int rows, int cols){
    int** field = new int*[rows];
    for (int i = 0; i < rows; i++) {
        field[i] = new int[cols];
    }
    clearField(field, rows, cols);
    return field;
}

void deleteField(int** field, int rows){
    for (int i = 0; i < rows; i++) {
        delete[] field[i];
    }
    delete[] field;
}

void clearField(int** field, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            field[i][j] = 0;
        }
    }
}

void fillRandom(int** field, int rows, int cols) {
    static random_device rd;
    static ranlux24_base gen(rd());
    uniform_int_distribution<int> dist(0, 1);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            field[i][j] = dist(gen);
        }
    }
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printField(int** field, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (field[i][j] == 1) {
                cout << "1 ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int countNeighbors(int** field, int rows, int cols, int row, int col) {
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i == row && j == col) {
                continue;
            }
            if (i >= 0 && i < rows && j >= 0 && j < cols) {
                if (field[i][j] == 1) {
                    count++;
                }
            }
        }
    }
    return count;
}

int** nextGeneration(int** field, int rows, int cols) {
    int** next = createField(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int neighbors = countNeighbors(field, rows, cols, i, j);
            if (field[i][j] == 1 && (neighbors == 2 || neighbors == 3)) {
                next[i][j] = 1;
            } else if (field[i][j] == 0 && neighbors == 3) {
                next[i][j] = 1;
            } else {
                next[i][j] = 0;
            }
        }
    }
    deleteField(field, rows);
    return next;
}

void setBlock(int** field, int row, int col) {
    field[row][col] = 1;
    field[row][col + 1] = 1;
    field[row + 1][col] = 1;
    field[row + 1][col + 1] = 1;
}

void setBeehive(int** field, int row, int col) {
    field[row][col + 1] = 1;
    field[row][col + 2] = 1;
    field[row + 1][col] = 1;
    field[row + 1][col + 3] = 1;
    field[row + 2][col + 1] = 1;
    field[row + 2][col + 2] = 1;
}

void setLoaf(int** field, int row, int col) {
    field[row][col + 1] = 1;
    field[row][col + 2] = 1;
    field[row + 1][col] = 1;
    field[row + 1][col + 3] = 1;
    field[row + 2][col + 1] = 1;
    field[row + 2][col + 3] = 1;
    field[row + 3][col + 2] = 1;
}

void setBoat(int** field, int row, int col) {
    field[row][col] = 1;
    field[row][col + 1] = 1;
    field[row + 1][col] = 1;
    field[row + 1][col + 2] = 1;
    field[row + 2][col + 1] = 1;
}

void runAnimation(int** field, int rows, int cols, int generations, int delayMs) {
    for (int i = 0; i < generations; i++) {
        clearConsole();
        cout << "Поколение: " << i + 1 << endl << endl;
        printField(field, rows, cols);
        field = nextGeneration(field, rows, cols);
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    deleteField(field, rows);
}