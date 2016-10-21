/**
* @file kart.cpp
* @description Her bir kart içerisinde bir adet sembol nesnesinin adresini tutar.
* @course 2A
* @assignment 1
* @date 5.10.2016
* @author Emirhan Aydın (g141210018@sakarya.edu.tr)
*/

#include "kart.h"

Kart::Kart() {
    kartSembolu = new Sembol();
}

Kart::Kart(const Kart &kart) {
    kartSembolu = kart.kartSembolu;
}

Kart::~Kart() {
    delete kartSembolu;
};

Kart &Kart::operator=(const Kart &kart) {
    kartSembolu = kart.kartSembolu;

    return *this;
}

char Kart::alKarakter() const {
    return kartSembolu->alKarakter();
}

int Kart::alRenk() const {
    return kartSembolu->alRenk();
}

void Kart::semboluBirak() {
    kartSembolu = 0;
}