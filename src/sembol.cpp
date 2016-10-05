#include "sembol.h"
#include <windows.h>
#include <time.h>

Sembol::Sembol() {
    static bool randBesleme = false;
    static const char karakterler[] = {'a', 'b', 'c', 'd'};
    static const int renkler[] = {14, 4, 5, 2};

    if(!randBesleme) {
        randBesleme = true;
        srand(time(0));
    }

    karakter = karakterler[rand() % 4];
    renk = renkler[rand() % 4];
}

char Sembol::alKarakter() {
    return karakter;
}

int Sembol::alRenk() {
    return renk;
}