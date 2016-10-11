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