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

void kartAdediAl(int &, string &);

void anaMenuYazdir(string[], int, int);

void anaMenuSecimi(string[], int, int &);

void kartlariTersCevir(Kart[], int);

int main() {
    system("color 7"); // Konsol rengini siyah arkaplan üzerine beyaz olacak şekilde ayarlar.

    int kartAdedi;
    string hata;

    kartAdediAl(kartAdedi, hata);
    if (hata != "") {
        cerr << hata;
        return 1;
    }

    Kart *kartlar;
    kartlar = new Kart[kartAdedi];

    const int secenekSayisi = 3;
    string secenekler[secenekSayisi] = {"Kartlarin Yerlerini Degistir",
                                        "Kartlari Ters Cevir",
                                        "Cikis"};

    int secim;
    int secenek = 0;

    Konsol::imleciGoster(0);

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
        cout << endl << endl << endl;

//        Ana menü seçenekleri yazdırılır.
        anaMenuYazdir(secenekler, secenekSayisi, secenek);

//        Ana menü fonksiyonları üzerinde dinamik olarak seçim yapabilmeyi sağlayan fonksiyon.
        anaMenuSecimi(secenekler, secenekSayisi, secenek);

        if (secenek == 1) kartlariTersCevir(kartlar, kartAdedi);

    } while (secenek != 2); // Ana menü sonu

    delete[] kartlar;
    Konsol::imleciGoster();
    return 0;
}

/**
 * Kullanıcıdan basılacak olan kart adedini alır.
 * @param kartAdedi Döndürülecek olan kart adedi.
 * @param hata Hata durumunda döndürülecek olan hata mesajı.
 */
void kartAdediAl(int &kartAdedi, string &hata) {
    hata = "";
    kartAdedi = 0;
    int genislik; // Konsol penceresinin genişliğinin 8'de biri değerini tutar. Döngü içinde değer atanır.
    bool hataliAdet = false;
    do { // Kart adedi al
        genislik = Konsol::alKonsolGenisligi() / 8;
//        Konsol genişliği değerinin alınması esnasında bir hata meydana gelmişse program sonlandırılır.
        if (genislik < 0) {
            hata = "Konsol penceresinin genisligi alinamiyor. Program sonlandirilacak.";
            return;
        }
        system("CLS");
        if (hataliAdet) cout << "Kart adedi 2 ile " << genislik << " araliginda olmalidir." << endl << endl;
        cout << "Kart adedi: ";
//        Aşağıdaki yapı basılan karakteri önce getch ile okumak, daha sonra ekrana yazdırmak ve enter tuşu basıldığında
//        girilen sayının tamamını int değere atamak için yapılmıştır. Burada amaç yalnızca istenilen formatta, sayı
//        karakterleri girilebilmesini sağlamaktır.
        char yazilan; // Getch ile okunan değer buna atanır.
        char sayi[2]; // Girilen karakter sayı ise bu diziye atanır. En fazla 2 haneli olabileceğinden 2 uzunluğundadır.
        int karSayisi = 0; // Diziye adres vermek ve en az 1 adet sayı girildiğinden emin olabilmek için kullanılır.
        do { // Karakter oku
            yazilan = _getch();
            if (karSayisi == 0 && yazilan == '0') continue; // Eğer ilk karakter olarak 0 girilmişse kabul edilmez.
//            Eğer girilen karakter bir sayı ise kabul edilir.
            if (karSayisi < 2 && yazilan >= '0' && yazilan <= '9') {
//                Sayı ekrana yazdırılır ve bu sayede kullanıcı tarafından doğrudan yazdırılmış izlenimi verilir.
                cout << yazilan;
                sayi[karSayisi++] = yazilan;
            }
//            Eğer 8 kodlu karater (BACKSPACE) basılırsa son girilen karakter silinir.
            if (karSayisi > 0 && yazilan == 8) {
                karSayisi--;
                cout << yazilan;
                cout << " ";
                cout << yazilan;
            }
        } while (!(yazilan == 13 && karSayisi > 0)); // Karakter oku sonu
//        Dizide tutulan sayılar, blok sonunda bellekte kalacak olan kart adedi değişkenine atanır.
        kartAdedi = (sayi[0] - '0');
        if (karSayisi > 1) {
            kartAdedi *= 10; // Eğer sayı iki haneliyse ilk girilen onlar basamağı olarak kabul edilir.
            kartAdedi += sayi[1] - '0';
        }
//        Eğer kart adedi gereken aralıkta değilse döngü başa sarılır.
        hataliAdet = kartAdedi < 2 || kartAdedi > genislik;
    } while (hataliAdet); // Kart adedi al sonu
}

/**
 * Ana menü seçeneklerini yazdıran fonksiyon.
 * @param secenekler Seçenekleri barındıran metin dizisi.
 * @param secenekSayisi Toplam seçenek sayısı.
 * @param secenek Seçilmiş olan seçeneği döndürmek için kullanılan referans.
 */
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
        secim = _getch();
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

/**
 * Gönderilen Kart dizisini tersler.
 * @param kartlar Terslenecek olan Kart dizisi.
 * @param kartAdedi Kart dizisi uzunluğu.
 */
void kartlariTersCevir(Kart kartlar[], int kartAdedi) {
    Kart *gecici = new Kart();
//    Oluşturulan geçici Kart nesnesi kullanılarak basit bir tersleme algoritması ile dizi terslenir.
    for (int i = 0, j = kartAdedi - 1, bitis = kartAdedi / 2; i < bitis; i++, j--) {
        *gecici = kartlar[i];
        kartlar[i] = kartlar[j];
        kartlar[j] = *gecici;
    }
//    Geçici kart nesnesinin gösterdiği Sembol nesnesi en dizide en son okunan kart nesnesinin Sembol nesnesi
//    olacağından kart silinmeden önce bu Sembol ile bağlantısı kesilir. Bu sayede kart silinirken bu sembolü de silmez.
    gecici->semboluBirak();
    delete gecici;
}