/**
* @file sembol.h
* @description İçerisinde sembol karakteri ve renk verisi barındırır.
* @course 2A
* @assignment 1
* @date 5.10.2016
* @author Emirhan Aydın (g141210018@sakarya.edu.tr)
*/

#ifndef SEMBOL_H
#define SEMBOL_H

class Sembol {
private:
    char karakter;
    int renk;
public:
    Sembol();

    int alRenk();

    char alKarakter();
};

#endif