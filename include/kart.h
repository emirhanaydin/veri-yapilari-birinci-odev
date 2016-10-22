/**
* @file kart.h
* @description Her bir kart içerisinde bir adet sembol nesnesinin adresini tutar. Bu sembol üzerinden sembolün karakter
 * ve renk verilerini kullanıcıya döndürür.
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

    /**
     * Parametre olarak gönderilen Kart nesnesine ait Sembol nesnesi yerel Sembol göstericisine atanır.
     */
    Kart(const Kart &);

    ~Kart();

    /**
     * Kopyalayıcı kurucu ile aynı işlemi gerçekleştirir.
     * @return Değer atanan nesneyi döndürür.
     */
    Kart &operator=(const Kart &); // Kopyalayıcı kurucu ile aynı işlemi gerçekleştirir.

    char alKarakter() const;

    int alRenk() const;

    /**
     * Mevcut nesnenin Sembol göstericisine NULL değeri atanır. Kart silindiği esnada, başka bir Kart nesnesi ile ortak
     * olarak gösterilen Sembol nesnesinin de silinmesini önlemek için kullanılır.
     */
    void semboluBirak();
};

#endif