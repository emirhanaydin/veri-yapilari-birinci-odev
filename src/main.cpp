/**
* @file Main.cpp
* @description Programınızın açıklaması ne yaptığına dair.
* @course 2A
* @assignment 1
* @date 5.10.2016
* @author Emirhan Aydın (g141210018@sakarya.edu.tr)
*/

#include <iostream>
#include <clocale>
#include "kart.h"

using namespace std;

int main() {
    int kartAdedi;
    Kart *kartlar;

    cout << "Kart adedi: ";
    cin >> kartAdedi;
    kartlar = new Kart[kartAdedi];

    for (int i = 0; i < kartAdedi; i++) {
        cout << i + 1 << "\t";
    }

    cout << endl << endl;
    cout << "Islemler:" << endl;
    cout << "1. Kart Degistir" << endl;
    cout << "2. Ters Cevir" << endl;
    cout << "3. Cikis" << endl;

    delete[] kartlar;
    return 0;
}