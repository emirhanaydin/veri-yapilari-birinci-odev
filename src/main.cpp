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

void dikeySecim(string[], int, int &);

bool onayMenusu();

void kartYerDegistir(Kart[], int);

void kartlariTersCevir(Kart[], int);

int main() {
    system("color 7"); // Konsol rengini siyah arkaplan üzerine beyaz olacak şekilde ayarlar.

    int kartAdedi;

    { // Kart adedi alma bloğu
        string hata;
        kartAdediAl(kartAdedi, hata);
        if (hata != "") { // Eğer hata değeri varsa program sonlandırılır.
            cerr << hata;
            return 1;
        }
    } // Kart adedi alma bloğu sonu

    Kart *kartlar = new Kart[kartAdedi];

    const int secenekSayisi = 3;
    string secenekler[secenekSayisi] = {"Kartlarin Yerlerini Degistir",
                                        "Kartlari Ters Cevir",
                                        "Cikis"};

    int secenek = 0;

    Konsol::imleciGoster(0);

    do { // Ana menü
        secenek = 0;
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
        dikeySecim(secenekler, secenekSayisi, secenek);

        if (secenek == 0) kartYerDegistir(kartlar, kartAdedi); // Kartların yerini değiştir
        else if (secenek == 1) kartlariTersCevir(kartlar, kartAdedi); // Kartları ters çevir
        else if (secenek == 2) { // Çıkış
            Konsol::imleciTasi(0, -1);
            cout << "  ";
            Konsol::imleciTasi(2, 9);
            cout << "Programdan cikmak istediginizden emin misiniz?";
            Konsol::imleciTasi(2, 12);
            if (onayMenusu()) {
                system("CLS");
                break;
            }
        }
    } while (true); // Ana menü sonu

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

int yonTuslariSecimi(int secenek, int secenekSayisi, char geriye = 72, char ileriye = 80, char onay = 13) {
    int fark = 0;
    char secim = _getch();

    if (secim == geriye) { // Yukarı ok tuşu
        if (secenek > 0)
            fark = -1;
    } else if (secim == ileriye) { // Aşağı ok tuşu
        if (secenek < secenekSayisi - 1)
            fark = 1;
    } else if (secim == onay) // CR karakteri, Enter tuşunu yakalamak için.
        fark = 2;

    return fark;
}

/**
 * Dikeyde ok tuşları ile seçenekler arasında seçim yapılmasını sağlayan fonksiyon.
 * @param secenekler Seçenekleri barındıran metin dizisi.
 * @param secenekSayisi Toplam seçenek sayısı.
 * @param secenek Seçilmiş olan seçeneği döndürmek için kullanılan referans.
 */
void dikeySecim(string secenekler[], int secenekSayisi, int &secenek) {
    int imlecY = Konsol::alImlecY() - (secenekSayisi - secenek - 1);
    int fark = 0;
    secenek = 0;

    Konsol::imleciTasi(0, imlecY);
    for (int i = 0; i < secenekSayisi; i++) {
        if (i == secenek) {
            Konsol::yaziRengi(15);
            cout << "> " << secenekler[i];
            Konsol::yaziRengi();
        } else
            cout << "  " << secenekler[i];
        if (i < secenekSayisi - 1) cout << endl;
    }

    Konsol::imleciTasi(0, imlecY);
    do { // Seçim döngüsü
        fark = yonTuslariSecimi(secenek, secenekSayisi);
        if (fark == 2) break;
        if (fark == 0) continue;
        secenek += fark;

//        İmleci bir önceki seçeneğin başına taşır, satırı boş karakter ile doldurur ve tekrar satır başına alır.
        Konsol::satiriDoldur(' ', 0, imlecY, true);
//        Yazma rengi varsayılan olarak ayarlanır.
        Konsol::yaziRengi();
//        Önceki seçenek işaret karakteri, '>' olmadan ve varsayılan renkte tekrar yazdırılır.
        cout << "  " << secenekler[secenek - fark];

//        İmleç konumu olarak sonraki, yeni seçeneğin konumu alınır.
        imlecY += fark;
        Konsol::satiriDoldur(' ', 0, imlecY, true);
//        Yazma rengini beyaz olarak ayarla, aktif seçenek görünümü için.
        Konsol::yaziRengi(15);
//        Mevcut seçenek işaret karakteri, '>' ile yazdırılır.
        cout << "> " << secenekler[secenek];
//        Yazma rengi tekrardan varsayılan renge ayarlanır.
        Konsol::yaziRengi();
    } while (true); // Seçim döngüsü sonu
}

/**
 * Kart yer değiştirme fonksiyonunun içinden çağrılır. O anki kartın başlığının ve altındaki gösterici karakterinin
 * renginin değiştirilerek belirginleştirilmesini sağlar.
 * @param konumX Seçim işaretçisinin yatay konumunu.
 * @param konumY Seçim işaretçisinin dikey konumu.
 * @param renk Belirginleştirme rengi.
 * @param secimKar İşaretçi yerine basılacak olan karakter, silmek için boş karakter gönderilmeilir.
 */
void kartBelirginlestir(int konumX, int konumY, int renk, char secimKar) {
    Konsol::yaziRengi(renk);
//    İmleç kart karakterinin hemen altına, kart işaretçi karakteri konumuna götürülür.
    Konsol::imleciTasi(konumX, konumY);
    cout << secimKar;

//    Kart başlığı köşeli parantezinin solundan itibaren 8 adet boşluk basılır ve tekrar 8 birim geriye gidilir.
    Konsol::satiriDoldur(' ', konumX - 3, konumY - 2, true, 8);
//    for (int i = 0; i < 8; i++) cout << char(8);
    cout << "[  " << left << setw(2) << (konumX - 3) / 8 + 1 << "  ]";
}

void kartYeriSec(Kart kartlar[], int kartAdedi, int &ilkSecim, int oncekiSecim = -1) {
    int secenekY = Konsol::alImlecY();
    char secimKar = 94;
    int konum = 0; // Gösterici karakter tarafından hangi kartın gösterildiğini belirtir.
    int isaretciY = 3; // Konum değerinden elde edilen o anki kartın yatay konumunu belirl
    int isaretciX = 3;
    int oncekiSecimX = 3 + 8 * oncekiSecim;
    int aktifRenk = 15, oncekiSecimRenk = 11, ikinciSecim = 14, kesisimRengi = 4;

    Konsol::imleciTasi(0, secenekY);
    cout << "  ";

    if (oncekiSecim >= 0) { // Eğer önceden bir seçim yapılmışsa
        kartBelirginlestir(isaretciX, isaretciY, 7, ' ');
        kartBelirginlestir(oncekiSecimX, isaretciY, kesisimRengi, secimKar);
        konum = (oncekiSecimX - 3) / 8;
        isaretciX = oncekiSecimX;
    } else
        kartBelirginlestir(isaretciX, isaretciY, aktifRenk, secimKar);

    int fark = 0;
    char secim;
    do {
        fark = yonTuslariSecimi(konum, kartAdedi, 75, 77);
        if (fark == 2) {
            if (konum == oncekiSecim) fark = 0;
            else break;
        }
        if (fark == 0) continue;
        kartBelirginlestir(isaretciX, isaretciY, 7, ' ');

        konum += fark;
        isaretciX += fark * 8;
        if (isaretciX == oncekiSecimX) // Eğer önceki seçim ile şu anki seçim göstericisi üst üste gelirse
//            Kesişim için farklı bir renk ile belirtilir.
            kartBelirginlestir(isaretciX, isaretciY, kesisimRengi, secimKar);
        else { // Eğer gösterici önceki seçimden farklı bir konumda ise
            if (isaretciX - fark * 8 == oncekiSecimX) // Eğer gösterici önceki seçim karakterinin üzerinden ayrılmışsa
//                Önceki seçim kartı yeniden kendi rengine döndürülür.
                kartBelirginlestir(oncekiSecimX, isaretciY, oncekiSecimRenk, secimKar);
            kartBelirginlestir(isaretciX, isaretciY, aktifRenk, secimKar);
        }
    } while (true);
    if (oncekiSecim >= 0) {
        kartBelirginlestir(isaretciX, isaretciY, 14, secimKar);
    }

    Konsol::yaziRengi();
    ilkSecim = konum;
}

bool onayMenusu() {
    string secenekler[] = {"Evet", "Hayir"};
    int secenek = 0;
    dikeySecim(secenekler, 2, secenek);
    return secenek == 0;
}

void kartYerDegistir(Kart kartlar[], int kartAdedi) {
    int ilkSecim, ikinciSecim;

    kartYeriSec(kartlar, kartAdedi, ilkSecim);
    Konsol::imleciTasi(0, 10);
    cout << "  " << ilkSecim + 1 << ". karti sectiniz. Yer degistirmek istediginiz karti seciniz.";
    kartYeriSec(kartlar, kartAdedi, ikinciSecim, ilkSecim);
    Konsol::satiriDoldur(' ', 0, 10, true);
    cout << "  " << ilkSecim + 1 << ". kart ile " << ikinciSecim + 1
         << ". kartin yerlerini degistirmek istiyor musunuz?";

    cout << endl << endl << endl;
    if (!onayMenusu())
        return;

    Kart *gecici = new Kart();
    *gecici = kartlar[ilkSecim];
    kartlar[ilkSecim] = kartlar[ikinciSecim];
    kartlar[ikinciSecim] = *gecici;
    gecici->serbestBirak();
    delete gecici;
}

/**
 * Gönderilen Kart dizisini tersler.
 * @param kartlar Terslenecek olan Kart dizisi.
 * @param kartAdedi Kart dizisi uzunluğu.
 */
void kartlariTersCevir(Kart kartlar[], int kartAdedi) {
    Konsol::imleciTasi(0, -1);
    cout << "  ";
    Konsol::imleciTasi(2, 9);
    cout << "Kart dizisini tersine cevirmek istiyor musunuz?";
    cout << endl << endl << endl;
    if (!onayMenusu())
        return;

    Kart *gecici = new Kart(); // O anki konumdaki kartın bilgilerini tutmak için oluşturulmuş geçici nesne.
//    Oluşturulan geçici Kart nesnesi kullanılarak basit bir tersleme algoritması ile dizi terslenir.
//    Dizide adres değişimi yapılmamıştır, yalnızca nesnelerin verileri geçici nesne tarafından tutularak diğerine
//    aktarılır.
    for (int i = 0, j = kartAdedi - 1, bitis = kartAdedi / 2; i < bitis; i++, j--) {
        *gecici = kartlar[i];
        kartlar[i] = kartlar[j];
        kartlar[j] = *gecici;
    }
//    Geçici kart nesnesinin gösterdiği veriler dizide en son okunan kart nesnesinin verileri olacağından
//    kart silinmeden önce bu veriler ile bağlantısı kesilir. Bu sayede kart silinirken gösterdiği alanlar da silinmez.
    gecici->serbestBirak();
    delete gecici;
}