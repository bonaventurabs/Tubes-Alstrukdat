#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "ListPoint.h"
#include "../boolean/boolean.h"

/* ********** LIST OBJEK SANTO TYCOON ********** */

void MakeListObjek(ListObjek *L)
/* I.S. sembarang */
/* F.S. Terbentuk ListObjek L kosong dengan kapasitas MaxObj */
{
    NObjek(*L) = 0;
}

void InsertListObjek (ListObjek *L, char S, int X, int Y)
/* I.S. L terdefinisi, mungkin kosong. */
/* F.S. S dan (X,Y)  menjadi elemen terakhir L. */
{
    NObjek(*L)++;
    Simbol(*L,NObjek(*L)) = S;
    Absis(Point(*L,NObjek(*L))) = X;
    Ordinat(Point(*L,NObjek(*L))) = Y;
}

int SearchIndeks (ListObjek L, POINT Lokasi)
/* Mengembalikan indeks(1..NObjek(L)) elemen dari L yang berada di-Lokasi, 0 bila tidak ada */
{
    boolean found = false;
    int i = 1;

    while (!found && i<=NObjek(L)){
        if (EQPOINT(Lokasi,Point(L,i))){
            found = true;
        }
        else{
            i++;
        }
    }
    if (found){
        return i;
    } else {
        return 0;
    }
}

void TulisBangunanLok (ListObjek L, POINT Lokasi, char **str)
/* I.S. L terdefinisi, tidak kosong. */
/* F.S. Menyimpan nama bangunan yang terletak di (X,Y) pada str. */
{
    boolean found = false;
    int countpelanggan = 0;
    int i = 1;

    while (!found && i<=NObjek(L)){
        if (Simbol(L,i)=='C'){
            countpelanggan++;
        }

        if (EQPOINT(Lokasi,Point(L,i))){
            if (Simbol(L,i)=='B'){
                *str = "Base";
            } else if (Simbol(L,i)=='S'){
                *str = "Shop";
            } else if (Simbol(L,i)=='C'){
                sprintf(*str,"Pelanggan %d",countpelanggan);
            }
            found = true;
        }
        else{
            i++;
        }
    }
}

void TulisBangunanInd (ListObjek L, int indeks, char **str)
/* I.S. L terdefinisi, tidak kosong. */
/* F.S. Menyimpan nama bangunan yang terletak berdasarkan indeks list pada str. */
{
    int countpelanggan = 0;
    int i = 1;

    while (i<=indeks){
        if (Simbol(L,i)=='C'){
            countpelanggan++;
        }
        i++;
    }

    if (Simbol(L,indeks)=='B'){
        *str = "Base";
    } else if (Simbol(L,indeks)=='S'){
        *str = "Shop";
    } else if (Simbol(L,indeks)=='C'){
        sprintf(*str,"Pelanggan %d",countpelanggan);
    }
}