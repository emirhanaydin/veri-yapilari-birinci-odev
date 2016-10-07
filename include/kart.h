#ifndef KART_H
#define KART_H

#include "sembol.h"

class Kart {
private:
    Sembol *kartSembolu;
public:
    Kart();

    ~Kart();

    Sembol *alSembol();
};

#endif