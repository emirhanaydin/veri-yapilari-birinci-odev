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
    COORD coord;
    coord.X = x;
    coord.Y = y;
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