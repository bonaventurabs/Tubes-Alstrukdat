#ifndef __DYNAMIC_LISTDELIVERY__
#define __DYNAMIC_LISTDELIVERY__
#include "../boolean/boolean.h"

#include <stdio.h>
#include <stdlib.h>

#define InitialSizeDelivery 10

typedef int IdxType;
typedef struct {
    int NoPesanan;
    int Pemesan;
    int Invoice;
} DelBuild;
typedef struct {
    DelBuild *A;
    int Capacity;
    int Neff;
} ArrayDelivery;

/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSizeDelivery
 */
ArrayDelivery MakeArrayDelivery();

/**
 * Destruktor
 * I.S. List terdefinisi
 * F.S. list->A terdealokasi
 */
void DeallocateArrayDelivery(ArrayDelivery *list);

/**
 * Fungsi untuk mengetahui apakah suatu list kosong.
 * Prekondisi: list terdefinisi
 */
boolean IsArrayDeliveryEmpty(ArrayDelivery list);

/**
 * Fungsi untuk mendapatkan banyaknya elemen efektif list, 0 jika tabel kosong.
 * Prekondisi: list terdefinisi
 */
int ArrayDeliveryLength(ArrayDelivery list);

/**
 * Mengembalikan elemen list L yang ke-I (indeks lojik).
 * Prekondisi: list tidak kosong, i di antara 0..Length(list).
 */
DelBuild ArrayDeliveryGet(ArrayDelivery list, IdxType i);

/**
 * Fungsi untuk mendapatkan kapasitas yang tersedia.
 * Prekondisi: list terdefinisi
 */
int ArrayDeliveryGetCapacity(ArrayDelivery list);

/**
 * Fungsi untuk menambahkan elemen baru di index ke-i
 * Prekondisi: list terdefinisi, i di antara 0..Length(list).
 */
void ArrayDeliveryInsertAt(ArrayDelivery *list, DelBuild el, IdxType i);

/**
 * Fungsi untuk menambahkan elemen baru di akhir list.
 * Prekondisi: list terdefinisi
 */
void ArrayDeliveryInsertLast(ArrayDelivery *list, DelBuild el);

/**
 * Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void ArrayDeliveryInsertFirst(ArrayDelivery *list, DelBuild el);

/**
/* I.S. L terdefinisi, tidak kosong,  
/* F.S. Elemen list sesuai indeks logic dihapus dari list. 
*/
void ArrayDeliveyDeleteAt (ArrayDelivery *list, DelBuild *el, IdxType i);

/**
/* I.S. list terdefinisi.
/* F.S. true jika terdapat Element dengan NoPesanan. 
*/
boolean IsNoPesananAda (ArrayDelivery list, int NoPesanan);

/**
/* I.S. list terdefinisi, NoPesanan ada di list.
/* F.S. indeks logic dari Elemet list NoPesanan di return 
*/
IdxType IndeksNoPesanan (ArrayDelivery list, int NoPesanan);

/**
/* I.S. list terdefinisi.
/* F.S. true jika terdapat Element dengan Pemesan. 
*/
boolean IsPemesanAda (ArrayDelivery list, int Pemesan);

/**
/* I.S. list terdefinisi, NoPesanan ada di list.
/* F.S. indeks logic dari Elemet list Pemesan di return 
*/
IdxType IndeksPemesan (ArrayDelivery list, int Pemesan);

/* ********** OPERASI GAME SANTO TYCOON ********** */
/**
 * Fungsi untuk membentuk DelBuild.
 * Prekondisi: NoPesanan, Pemesan, dan Invoice terdefinisi
 */
DelBuild ArrangeDelBuild(int NoPesanan,int Pemesan, int Invoice);

#endif	
