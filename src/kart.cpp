#include "kart.h"

Kart::Kart() {
    kartSembolu = new Sembol();
}

Kart::~Kart() {
    delete kartSembolu;
};