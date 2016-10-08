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

    static void satiriDoldur(char, int = -1);
};

#endif