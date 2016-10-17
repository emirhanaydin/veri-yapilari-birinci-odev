/**
* @file konsol.h
* @description Konsol işlemlerini gerçekleştiren metotları barındırır. Bunlar imlecin konumunu, rengini değiştirmek
 * gibi işlevler olabilir.
* @course 2A
* @assignment 1
* @date 7.10.2016
* @author Emirhan Aydın (g141210018@sakarya.edu.tr)
*/

#ifndef KONSOL_H
#define KONSOL_H

class Konsol {
private:
    static HANDLE konsol;
public:
    static int alKonsolGenisligi();

    static void imleciGoster(bool = true);

    static void imleciTasi(int, int);

    static int alImlecX();

    static int alImlecY();

    static void yaziRengi(int = 7);

    static void satiriDoldur(char, int = -1, int = -1, bool = true, int = -1);
};

#endif