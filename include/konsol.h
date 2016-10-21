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
    /**
    * Konsol genişliğinin kaç karakter boyutunda olduğunu belirler.
    * @return Karakter sayısını döndürür.
    */
    static int alKonsolGenisligi();

    /**
    * İmleci konsol penceresinde gösterilmesini veya gizlenmesini sağlar.
    * @param gorunur İmlecin gösterilip gösterilmeyeceğini belirtir.
    */
    static void imleciGoster(bool = true);

    /**
    * İmleci verilen konuma taşır.
    * @param x İmlecin yataydaki konumu.
    * @param y İmlecin dikeydeki konumu.
    */
    static void imleciTasi(int, int);

    static int alImlecX();

    static int alImlecY();

    /**
    * Konsolun metin rengini ayarlamaya yarar.
    * @param renk Atanacak olan rengin tam sayı kodu. (Varsayılan = 7, gri renk)
    */
    static void yaziRengi(int = 7);

    /**
    * İmlecin şu anki yatay pozisyonundan satır sonuna kadar aynı karakteri basar.
    * @param karakter Basılacak olan karakter.
    * @param x Başlangıçtaki yatay konum. Eğer verilmezse o anki konumdan başlar.
    * @param y Gidilecek olan dikey konum. Eğer verilmezse o anki konum kabul edilir.
    * @param geriyeDon Satır doldurulduktan sonra tekrar başlangıç pozisyonuna dönülsün mü?
    * @param uzunluk Kaç adet karakter basılacağını belirtir. Varsayılan değerinde bırakılırsa satır sonuna kadar basılır.
    */
    static void satiriDoldur(char, int = -1, int = -1, bool = true, int = -1);
};

#endif