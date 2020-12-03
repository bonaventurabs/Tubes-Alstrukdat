#ifndef LISTPOINT_H
#define LISTPOINT_H

#include "point.h"
#include "../boolean/boolean.h"

/* ********** LIST OBJEK SANTO TYCOON ********** */
/* Definisi elemen dan koleksi objek */
#define MaxObj 99

typedef struct {
   char Simbol;
   POINT Loc;
} Objek;

typedef struct {
   Objek TabObjek[MaxObj+1]; 
   int NObj;  
} ListObjek;

#define NObjek(L) (L).NObj
#define Simbol(L,i) (L).TabObjek[(i)].Simbol
#define Point(L,i) (L).TabObjek[(i)].Loc

void MakeListObjek(ListObjek *L);
/* I.S. sembarang */
/* F.S. Terbentuk ListObjek L kosong dengan kapasitas MaxObj */

void InsertListObjek (ListObjek *L, char S, int X, int Y);
/* I.S. L terdefinisi, mungkin kosong. */
/* F.S. S dan (X,Y)  menjadi elemen terakhir L. */

int SearchIndeks (ListObjek L, POINT Lokasi);
/* Mengembalikan indeks(1..NObjek(L)) elemen dari L yang berada di-Lokasi, NULL bila tidak ada */

void TulisBangunanLok (ListObjek L, POINT Lokasi, char **str);
/* I.S. L terdefinisi, tidak kosong. */
/* F.S. Menyimpan nama bangunan yang terletak di (X,Y). */

void TulisBangunanInd (ListObjek L, int indeks, char **str);
/* I.S. L terdefinisi, tidak kosong. */
/* F.S. Menyimpan nama bangunan yang terletak berdasarkan indeks list pada str. */

#endif
