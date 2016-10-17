/**
* @file sembol.cpp
* @description İçerisinde sembol karakteri ve renk verisi barındırır.
* @course 2A
* @assignment 1
* @date 5.10.2016
* @author Emirhan Aydın (g141210018@sakarya.edu.tr)
*/

#include "sembol.h"
#include <windows.h>
#include <time.h>

Sembol::Sembol() {
    static bool randBesleme = false;

    if (!randBesleme) {
        randBesleme = true;
        srand(time(0));
    }

    karakter = rand() % 94 + 33;
    renk = rand() % 15 + 1;
}

char Sembol::alKarakter() {
    return karakter;
}

int Sembol::alRenk() {
    return renk;
}