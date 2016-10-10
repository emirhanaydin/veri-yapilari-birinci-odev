#include "kart.h"

Kart::Kart() {
    kartSembolu = new Sembol();
}

Kart::~Kart() {
    delete kartSembolu;
};

Kart & Kart::operator=(const Kart &kart) {
    kartSembolu = kart.kartSembolu;

    return *this;
}

Sembol *Kart::alSembol() {
    return kartSembolu;
}

void Kart::semboluBirak() {
    kartSembolu = 0;
}