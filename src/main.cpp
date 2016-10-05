/**
* @file Main.cpp
* @description Programınızın açıklaması ne yaptığına dair.
* @course 2A
* @assignment 1
* @date 5.10.2016
* @author Emirhan Aydın (g141210018@sakarya.edu.tr)
*/

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <time.h>
#include "kart.h"

using namespace std;

int konsolGenisligi();

int main() {
    int kartAdedi;
    Kart *kartlar;

    system("CLS");
    cout << "Kart adedi: ";
    cin >> kartAdedi;
    system("CLS");

    cout << setw(kartAdedi * 4 + 2) << "[ KARTLAR ]" << endl;
    if (kartAdedi < 2 || kartAdedi > konsolGenisligi() / 8) {
        return 0;
    }
    kartlar = new Kart[kartAdedi];

    for (int i = 0; i < kartAdedi; i++) {
        cout << i + 1 << "\t";
    }
    cout << endl;
    Sembol *sembol;
    for (int i = 0; i < kartAdedi; i++) {
        sembol = kartlar[i].alSembol();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), sembol->alRenk());
        cout << sembol->alKarakter() << "\t";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << endl << endl;
    cout << "Islemler:" << endl;
    cout << "1. Kart Degistir" << endl;
    cout << "2. Ters Cevir" << endl;
    cout << "3. Cikis" << endl;

    delete[] kartlar;
    return 0;
}

int konsolGenisligi() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return -1;
    } else {
        return csbi.srWindow.Right - csbi.srWindow.Left;
    }
}