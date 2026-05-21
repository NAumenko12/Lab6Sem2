#include "aes.h"

void saveBytesToFile(const vector<Byte>& data, const string& filename){
    ofstream file(filename);
    if (file.is_open()){
        file << bytesToHex(data);
        file.close();
    } else {
        cout << "Не удалось записать файл: " << filename << endl;
    }
}

vector<Byte> readBytesFromFile(const string& filename){
    ifstream file(filename);
    string hexText;
    if (file.is_open()){
        file >> hexText;
        file.close();
    } else {
        cout << "Не удалось открыть файл " << filename << endl;
    }
    return hexToBytes(hexText);
}

string readTextFromFile(const string& filename){
    ifstream file(filename);
    string text;
    if (file.is_open()){
        stringstream buffer;
        buffer << file.rdbuf();
        text = buffer.str();
        file.close();
    } else {
        cout << "Не удалось открыть файл: " << filename << endl;
    }
    return text;
}

void writeTextToFile(const string& filename, const string& text){
    ofstream file(filename);
    if (file.is_open()){
        file << text;
        file.close();
    } else {
        cout << "Не удалось записать файл: " << filename << endl;
    }
}
