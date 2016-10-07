#include "kart.h"

Kart::Kart() {
    kartSembolu = new Sembol();
}

Kart::~Kart() {
    delete kartSembolu;
};

Sembol *Kart::alSembol() {
    return kartSembolu;
}