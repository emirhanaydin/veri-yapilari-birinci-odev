/**
* @file kart.h
* @description Her bir kart içerisinde bir adet sembol nesnesinin adresini tutar.
* @course 2A
* @assignment 1
* @date 5.10.2016
* @author Emirhan Aydın (g141210018@sakarya.edu.tr)
*/

#ifndef KART_H
#define KART_H

#include "sembol.h"

class Kart {
private:
    Sembol *kartSembolu;
public:
    Kart();

    Kart(const Kart&);

    ~Kart();

    Kart &operator=(const Kart &);

    char alKarakter() const;

    int alRenk() const;

    void semboluBirak();
};

#endif