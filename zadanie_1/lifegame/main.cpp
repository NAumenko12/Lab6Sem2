#include "life.h"

int main() {
    srand(time(0));
    int m = 15;
    int n = 30;
    int pokoleniya = 10;
    int pauza = 700;
    int** pole = createPole(m, n);
    Block(pole, 5, 10);
    cout << "Block" << endl;
    zapuskAnim(pole, m, n, pokoleniya, pauza);
    pole = createPole(m, n);
    Beehive(pole, 5, 10);
    cout << "Beehive" << endl;
    zapuskAnim(pole, m, n, pokoleniya, pauza);
    pole = createPole(m, n);
    Loaf(pole, 5, 10);
    cout << "Loaf" << endl;
    zapuskAnim(pole, m, n, pokoleniya, pauza);
    pole = createPole(m, n);
    Boat(pole, 5, 10);
    cout << "Boat" << endl;
    zapuskAnim(pole, m, n, pokoleniya, pauza);
    pole = createPole(m, n);
    Glider(pole, 1, 1);
    cout << "Glider" << endl;
    zapuskAnim(pole, m, n, 25, pauza);
    pole = createPole(m, n);
    zapolnitRandom(pole, m, n);
    cout << "Random" << endl;
    zapuskAnim(pole, m, n, 30, pauza);
    return 0;
}
