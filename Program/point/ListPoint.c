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
    Simbol(*L,NObjek(*L)) = S;
    
    NObjek(*L)++;
    Absis(Point(*L,NObjek(*L))) = X;
    Ordinat(Point(*L,NObjek(*L))) = Y;
}