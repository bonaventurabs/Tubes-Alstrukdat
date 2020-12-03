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

void TulisBangunan (ListObjek L, POINT Lokasi, char **str)
/* I.S. L terdefinisi, tidak kosong. */
/* F.S. Menyimpan nama bangunan yang terletak di (X,Y). */
{
    boolean found = false;
    int countpelanggan = 0;
    int i = 1;
    char *copy;

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