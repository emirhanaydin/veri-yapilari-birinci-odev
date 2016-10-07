#ifndef KONSOL_H
#define KONSOL_H

class Konsol {
private:
    static HANDLE konsol;
public:
    static int alKonsolGenisligi();

    static void imleciGoster(bool);

    static void imleciTasi(int, int);

    static int alImlecX();

    static int alImlecY();
};

#endif