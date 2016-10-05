#include "sembol.h"
#include <windows.h>
#include <time.h>

Sembol::Sembol() {
    static const char karakterler[] = {'a', 'b', 'c', 'd'};
    static const int renkler[] = {14, 4, 5, 2};

    srand(time(NULL));

    karakter = karakterler[rand() % 4];
    renk = renkler[rand() % 4];
}

Sembol::alKarakter() {
    return karakter;
}

Sembol::alRenk() {
    return renk;
}