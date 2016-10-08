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

void anaMenuYazdir(string secenekler[], int secenekSayisi, int secenek);

void anaMenuSecimi(string[], int, int &);

int main() {
    int kartAdedi;
    Kart *kartlar;

    const int secenekSayisi = 3;
    string secenekler[secenekSayisi] = {"Kartlarin Yerlerini Degistir",
                                        "Kartlari Ters Cevir",
                                        "Cikis"};
    int secenek = 0;

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

    int secim;

    do { // Ana menü
        system("CLS");
        cout << setw(kartAdedi * 4 - 6) << " " << "[ KARTLAR ]" << endl;

        for (int i = 0; i < kartAdedi; i++) {
            cout << "[  " << left << setw(2) << i + 1 << "  ]";
        }
        cout << endl;
        Sembol *sembol;
        for (int i = 0; i < kartAdedi; i++) {
            sembol = kartlar[i].alSembol();
            Konsol::yaziRengi(sembol->alRenk());
            cout << "  |" << sembol->alKarakter() << setw(4) << "|";
        }
        Konsol::yaziRengi();
        cout << endl << endl;

//        Ana menü seçenekleri yazdırılır.
        anaMenuYazdir(secenekler, secenekSayisi, secenek);

//        Ana menü fonksiyonları üzerinde dinamik olarak seçim yapabilmeyi sağlayan fonksiyon.
        anaMenuSecimi(secenekler, secenekSayisi, secenek);

    } while (secenek != 2); // Ana menü sonu

    delete[] kartlar;
    Konsol::imleciGoster();
    return 0;
}

void anaMenuYazdir(string secenekler[], int secenekSayisi, int secenek) {
//    Gönderilen seçenek değerinin gereken aralıkta olup olmadığı denetlenir.
    if (secenek < 0) secenek = 0;
    else if (secenek >= secenekSayisi) secenek = secenekSayisi - 1;
//    İlk olarak menü seçenekleri yazdırılır.
    for (int i = 0; i < secenekSayisi; i++) {
        if (i == secenek) {
            Konsol::yaziRengi(15);
            cout << "> " << secenekler[i] << (i < secenekSayisi - 1 ? "\n" : "");
            Konsol::yaziRengi();
            continue;
        }
        cout << "  " << secenekler[i] << (i < secenekSayisi - 1 ? "\n" : "");
    }
}

/**
 * Ana menü seçim fonksiyonu.
 * @param secenekler Seçenekleri barındıran metin dizisi.
 * @param secenekSayisi Toplam seçenek sayısı.
 * @param secenek Seçilmiş olan seçeneği döndürmek için kullanılan referans.
 */
void anaMenuSecimi(string secenekler[], int secenekSayisi, int &secenek) {
    int imlecY = Konsol::alImlecY() - (secenekSayisi - secenek - 1);
    char secim;
    int fark;
    bool cikis = false;

    Konsol::imleciTasi(0, imlecY);
    do { // Seçim döngüsü
        secim = getch();
        fark = 0;

        switch (secim) {
            case 72: // Yukarı ok tuşu
                if (secenek > 0)
                    fark = -1;
                break;
            case 80: // Aşağı ok tuşu
                if (secenek < secenekSayisi - 1)
                    fark = 1;
                break;
            case 13: // CR karakteri, Enter tuşunu yakalamak için.
                cikis = true;
                break;
        }
        if (cikis) break;
        if (fark == 0) continue;
        secenek += fark;

//        İmleci bir önceki seçeneğin başına taşı.
        Konsol::imleciTasi(0, imlecY);
//        Satırda yer alan seçeneği boş karakteri satır boyunca doldurarak sil.
        Konsol::satiriDoldur(' ', 0);
//        İmleci tekrar satır başına al.
        Konsol::imleciTasi(0, imlecY);
//        Yazma rengi varsayılan olarak ayarlanır.
        Konsol::yaziRengi();
//        Önceki seçenek işaret karakteri, '>' olmadan ve varsayılan renkte tekrar yazdırılır.
        cout << "  " << secenekler[secenek - fark];

//        İmleç konumu olarak sonraki, yeni seçeneğin konumu alınır.
        imlecY += fark;
//        İmleci yeni atanan konuma taşı.
        Konsol::imleciTasi(0, imlecY);
//        Satırda yer alan seçeneği boş karakteri satır boyunca doldurarak sil.
        Konsol::satiriDoldur(' ', 0);
//        İmleci tekrar satır başına al.
        Konsol::imleciTasi(0, imlecY);
//        Yazma rengini beyaz olarak ayarla, aktif seçenek görünümü için.
        Konsol::yaziRengi(15);
//        Mevcut seçenek işaret karakteri, '>' ile yazdırılır.
        cout << "> " << secenekler[secenek];
//        Yazma rengi tekrardan varsayılan renge ayarlanır.
        Konsol::yaziRengi();
    } while (true); // Seçim döngüsü sonu
}