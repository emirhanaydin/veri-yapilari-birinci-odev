/**
* @file Main.cpp
* @description Programınızın açıklaması ne yaptığına dair.
* @course 2A
* @assignment 1
* @date 5.10.2016
* @author Emirhan Aydın (g141210018@sakarya.edu.tr)
*/

#include <iostream>
#include <iomanip> // setw fonksiyonu.
#include <windows.h> // system fonksiyonu
#include <conio.h> // getch fonksiyonu
#include "kart.h"
#include "konsol.h"

using namespace std;

int main() {
    int kartAdedi;
    Kart *kartlar;

    const int secenekSay = 3;
    string secenekler[secenekSay] = {"Kartlarin Yerlerini Degistir",
                                     "Kartlari Ters Cevir",
                                     "Cikis"};
    int seciliSecenek = 0;

    Konsol::imleciGoster(0);

    int genislik; // Konsol penceresinin genişliğinin 8'de biri değerini tutar. Döngü içinde değer atanır.
    bool hataliAdet = false;
    do { // Kart adedi al
        genislik = Konsol::alKonsolGenisligi() / 8;
//        Konsol genişliği değerinin alınması esnasında bir hata meydana gelmişse program sonlandırılır.
        if (genislik < 0) {
            cerr << "Konsol penceresinin genisligi alinamiyor. Program sonlandirilacak.";
            return 1;
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
            Konsol::yaziRengi(sembol->alRenk());
            cout << sembol->alKarakter() << "\t";
        }
        Konsol::yaziRengi();
        cout << endl << endl;

//        Menü seçenekleri yazdırılır.
        for (int i = 0; i < secenekSay; i++) {
            if (i == seciliSecenek) {
                Konsol::yaziRengi(15);
                cout << "> " << secenekler[i] << (i < secenekSay - 1 ? "\n" : "");
                Konsol::yaziRengi();
                continue;
            }
            cout << "  " << secenekler[i] << (i < secenekSay - 1 ? "\n" : "");
        }

        secim = getch();
        if (secim == 'd' && seciliSecenek < secenekSay - 1) seciliSecenek++;
        else if (secim == 'a' && seciliSecenek > 0) seciliSecenek--;
    } while (secim != 'c'); // Ana menü sonu

    delete[] kartlar;
    Konsol::imleciGoster();
    return 0;
}