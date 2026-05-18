#include "aes.h"

string readTextFromConsole(){
    string text;
    cout << "Введите текст: ";
    getline(cin, text);
    return text;
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

vector<Byte> stringToBytes(const string& text){
    vector<Byte> bytes;
    for (int i = 0; i < (int)text.size(); i++){
        bytes.push_back((Byte)text[i]);
    }
    return bytes;
}

string bytesToString(const vector<Byte>& data){
    string text;
    for (int i = 0; i < (int)data.size(); i++){
        text += (char)data[i];
    }
    return text;
}

string bytesToHex(const vector<Byte>& data){
    stringstream ss;
    ss << hex << setfill('0');
    for (int i = 0; i < (int)data.size(); i++){
        ss << setw(2) << (int)data[i];
    }
    return ss.str();
}

vector<Byte> hexToBytes(const string& hexText){
    vector<Byte> bytes;
    for (int i = 0; i + 1 < (int)hexText.size(); i += 2){
        string part = hexText.substr(i, 2);
        int value = stoi(part, nullptr, 16);
        bytes.push_back((Byte)value);
    }
    return bytes;
}

void printBytesHex(const vector<Byte>& data, const string& title){
    cout << title << ": " << bytesToHex(data) << endl;
}
