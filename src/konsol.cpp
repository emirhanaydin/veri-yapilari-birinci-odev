/**
* @file konsol.cpp
* @description Açıklama ilgili başlık dosyasında yapılmıştır.
* @course 2A
* @assignment 1
* @date 7.10.2016
* @author Emirhan Aydın (g141210018@sakarya.edu.tr)
*/

#include <iostream>
#include <windows.h>
#include "konsol.h"

HANDLE Konsol::konsol = GetStdHandle(STD_OUTPUT_HANDLE);

int Konsol::alKonsolGenisligi() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (!GetConsoleScreenBufferInfo(konsol, &csbi)) {
        return -1;
    } else {
//        Konsol penceresinin sol ve sağ karakterleri arasındaki fark, karakter sayısı olarak genişliği verir.
        return csbi.srWindow.Right - csbi.srWindow.Left;
    }
}

void Konsol::imleciGoster(bool gorunur) {
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = gorunur;
//    Varsayılan imleç boyutu değeri, 10.
    cci.dwSize = 10;
    SetConsoleCursorInfo(konsol, &cci);
}

void Konsol::imleciTasi(int x, int y) {
    int konumX = x < 0 ? Konsol::alImlecX() : x;
    int konumY = y < 0 ? Konsol::alImlecY() : y;

    COORD coord;
    coord.X = konumX;
    coord.Y = konumY;
    SetConsoleCursorPosition(konsol, coord);
}

int Konsol::alImlecX() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(konsol, &csbi))
        return -1;
    return csbi.dwCursorPosition.X;
}

int Konsol::alImlecY() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(konsol, &csbi))
        return -1;
    return csbi.dwCursorPosition.Y;
}

void Konsol::yaziRengi(int renk) {
    SetConsoleTextAttribute(konsol, renk);
}

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