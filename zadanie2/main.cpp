#include "aes.h"

int main(){
    int vibor{};
    string text;
    cout << "AES128 CBC" << endl;
    cout << "1 - Ввести текст с консоли" << endl;
    cout << "2 - Прочитать текст из файла" << endl;
    cout << "выбор: ";
    cin >> vibor;
    cin.ignore();
    if (vibor == 1){
        text = readTextFromConsole();
    } else {
        string filename;
        cout << "Введите имя файла: ";
        getline(cin, filename);
        text = readTextFromFile(filename);
    }
    vector<Byte> textBytes = stringToBytes(text);
    vector<Byte> key = generateRandomBytes(16);
    vector<Byte> iv = generateRandomBytes(16);
    vector<vector<Byte>> roundKeys = expandKey(key);
    saveBytesToFile(key, "key.txt");
    saveBytesToFile(iv, "iv.txt");
    cout << endl;
    printBytesHex(key, "Сгенерированный ключ");
    printBytesHex(iv, "Вектор инициализации IV");
    cout << endl << "Раундовые ключи:" << endl;
    printRoundKeys(roundKeys);
    cout << endl << "Шифрование:" << endl;
    vector<Byte> encrypted = encryptCBC(textBytes, key, iv);
    string encryptedHex = bytesToHex(encrypted);
    writeTextToFile("encrypted.txt", encryptedHex);
    cout << endl;
    cout << "Зашифрованный текст HEX: " << encryptedHex << endl;
    cout << endl << "Расшифрование:" << endl;
    vector<Byte> decrypted = decryptCBC(encrypted, key, iv);
    string decryptedText = bytesToString(decrypted);
    writeTextToFile("decrypted.txt", decryptedText);
    cout << "Расшифрованный текст: " << decryptedText << endl;
    cout << "Расшифрованный текст записан в файл decrypted.txt" << endl;
    return 0;
}
