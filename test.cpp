#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;

int main() {
    fstream AAA;
    AAA.open("FILE_ne.txt", ios::out);
    if (AAA.is_open()) {
        AAA << "Hello file world!" << endl;
        cout << "File created successfully!\n";
        cout << "Current Path: " << filesystem::current_path() << endl;
    } else {
        cout << "Cannot open file.\n";
    }
    AAA.close();
    return 0;
}