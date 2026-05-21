#include "aes.h"

string readTextFromConsole(){
    string text;
    cout << "Введите текст: ";
    getline(cin, text);
    return text;
}
