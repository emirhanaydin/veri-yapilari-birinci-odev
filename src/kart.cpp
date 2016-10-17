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

Kart::~Kart() {
    delete kartSembolu;
};

Kart &Kart::operator=(const Kart &kart) {
    kartSembolu = kart.kartSembolu;

    return *this;
}

Sembol *Kart::alSembol() {
    return kartSembolu;
}

void Kart::serbestBirak() {
    kartSembolu = 0;
}