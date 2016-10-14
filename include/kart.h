#ifndef KART_H
#define KART_H

#include "sembol.h"

class Kart {
private:
    Sembol *kartSembolu;
public:
    Kart();

    ~Kart();

    Kart &operator=(const Kart &);

    Sembol *alSembol();

    void serbestBirak();
};

#endif