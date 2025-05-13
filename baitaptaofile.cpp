#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct people {
    string name;
    int age;
};

int main() {
    int n;
    cout << "Nhap so luong nguoi muon tao: ";
    cin >> n;
    vector<people> person(n);

    // Nhap thong tin
    for (int i = 0; i < person.size(); i++) {
        cout << "Nhap ten nguoi thu " << i + 1 << ": ";
        cin.ignore();
        getline(cin, person[i].name);
        cout << "Nhap tuoi nguoi thu " << i + 1 << ": ";
        cin >> person[i].age;
    }

    // Mo file va ghi
    ofstream outFile("people.txt");
    if (!outFile) {
        cout << "Khong mo duoc file de ghi!";
        return 1;
    }

    outFile << left << setw(30) << "Ten" << "\t" << "Tuoi" << endl;
    for (int i = 0; i < person.size(); i++) {
        outFile << left << setw(30) << person[i].name << "\t" << person[i].age << endl;
    }
    outFile.close();

    //Mo file va doc
    ifstream inFile("people.txt");
    if(!inFile){
        cout << "Khong mo duoc file de doc!";
        return 1;
    }
    string _name;
    int _age;
    //Bo qua Ten va Tuoi
    getline(inFile, _name);
    cout << "Danh sach nguoi co trong file: " << endl;
    cout << left << setw(30) << "Ten" << "\t" << "Tuoi" << endl;
    int count = 0;
    int sum = 0;
    while(getline(inFile,_name)){
        string personName = _name.substr(0,30);
        int personAge = stoi(_name.substr(31));
        cout << personName << "\t" << personAge << endl;
        sum+= personAge;
        count++;
    }
    inFile.close();
    if(count > 0){
    double TB = (double) sum / count;
    cout << "Tuoi trung binh moi nguoi la: " << TB;
    }
    else cout << "Khong co du lieu de tinh diem trung binh!";
    return 0;
}