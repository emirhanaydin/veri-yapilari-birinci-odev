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
#include <conio.h>
#include "kart.h"
#include "konsol.h"

using namespace std;

int main() {
    int kartAdedi;
    Kart *kartlar;

    Konsol::imleciGoster(0);

    int genislik; // Konsol penceresinin genişliğinin 8'de biri değerini tutar. Döngü içinde değer atanır.
    bool hataliAdet = false;
    do { // Kart adedi al
        genislik = Konsol::alKonsolGenisligi() / 8;
//        Konsol genişliği değerinin alınması esnasında bir hata meydana gelmişse program sonlandırılır.
        if (genislik < 0) {
            cerr << "Konsol penceresinin genisligi alinamiyor. Program sonlandirilacak.";
            return EXIT_FAILURE;
        }
        system("CLS");
        if (hataliAdet) cout << "Kart adedi 2 ile " << genislik << " araliginda olmalidir." << endl;
        cout << "Kart adedi: ";
        cin >> kartAdedi;
//        Eğer kart adedi gereken aralıkta değilse döngü başa sarılır.
        hataliAdet = kartAdedi < 2 || kartAdedi > genislik;
    } while (hataliAdet); // Kart adedi al sonu

    kartlar = new Kart[kartAdedi];

    char secim;

    do { // Ana menü
        system("CLS");
        cout << setw(kartAdedi * 4 + 2) << "[ KARTLAR ]" << endl;

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
        cout << "> 1. Kart Degistir" << endl;
        cout << "  2. Ters Cevir" << endl;
        cout << "  3. Cikis" << endl;
        secim = getch();
    } while (secim != 'c'); // Ana menü sonu

    delete[] kartlar;
    return 0;
}