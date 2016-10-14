#include <iostream>
#include <windows.h>
#include "konsol.h"

HANDLE Konsol::konsol = GetStdHandle(STD_OUTPUT_HANDLE);

/**
 * Konsol genişliğinin kaç karakter boyutunda olduğunu belirler.
 * @return Karakter sayısını döndürür.
 */
int Konsol::alKonsolGenisligi() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (!GetConsoleScreenBufferInfo(konsol, &csbi)) {
        return -1;
    } else {
//        Konsol penceresinin sol ve sağ karakterleri arasındaki fark, karakter sayısı olarak genişliği verir.
        return csbi.srWindow.Right - csbi.srWindow.Left;
    }
}

/**
 * İmleci konsol penceresinde gösterilmesini veya gizlenmesini sağlar.
 * @param gorunur İmlecin gösterilip gösterilmeyeceğini belirtir.
 */
void Konsol::imleciGoster(bool gorunur) {
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = gorunur;
//    Varsayılan imleç boyutu değeri, 10.
    cci.dwSize = 10;
    SetConsoleCursorInfo(konsol, &cci);
}

/**
 * İmleci verilen konuma taşır.
 * @param x İmlecin yataydaki konumu.
 * @param y İmlecin dikeydeki konumu.
 */
void Konsol::imleciTasi(int x, int y) {
    int konumX = x < 0 ? Konsol::alImlecX() : x;
    int konumY = y < 0 ? Konsol::alImlecY() : y;

    COORD coord;
    coord.X = konumX;
    coord.Y = konumY;
    SetConsoleCursorPosition(konsol, coord);
}

/**
 *
 * @return İmlecin yataydaki konumunmu döndürür.
 */
int Konsol::alImlecX() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(konsol, &csbi))
        return -1;
    return csbi.dwCursorPosition.X;
}

/**
 *
 * @return İmlecin dikeydeki konumunu döndürür.
 */
int Konsol::alImlecY() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(konsol, &csbi))
        return -1;
    return csbi.dwCursorPosition.Y;
}

/**
 * Konsolun metin rengini ayarlamaya yarar.
 * @param renk Atanacak olan rengin tam sayı kodu.
 */
void Konsol::yaziRengi(int renk) {
    SetConsoleTextAttribute(konsol, renk);
}

/**
 * İmlecin şu anki yatay pozisyonundan satır sonuna kadar aynı karakteri basar.
 * @param karakter Basılacak olan karakter.
 * @param x Başlangıçtaki yatay konum. Eğer verilmezse o anki konumdan başlar.
 * @param y Gidilecek olan dikey konum. Eğer verilmezse o anki konum kabul edilir.
 * @param geriyeDon Satır doldurulduktan sonra tekrar başlangıç pozisyonuna dönülsün mü?
 * @param uzunluk Kaç adet karakter basılacağını belirtir. Varsayılan değerinde bırakılırsa satır sonuna kadar basılır.
 */
void Konsol::satiriDoldur(char karakter, int x, int y, bool geriyeDon, int uzunluk) {
    int konumX = x < 0 ? Konsol::alImlecX() : x;
    int konumY = y < 0 ? Konsol::alImlecY() : y;

    Konsol::imleciTasi(konumX, konumY);

    int karAdedi = Konsol::alKonsolGenisligi() - konumX;
    if (uzunluk >= 0 && uzunluk < karAdedi)
        karAdedi = uzunluk;
    for (int i = 0; i < karAdedi; i++)
        std::cout << karakter;
    if (geriyeDon) {
        Konsol::imleciTasi(konumX, konumY);
    }
}