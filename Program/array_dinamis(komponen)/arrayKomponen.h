#ifndef __DYNAMIC_LIST__
#define __DYNAMIC_LIST__
#include "../boolean/boolean.h"

#include <stdio.h>
#include <stdlib.h>

#define InitialSizeKomponen 10

typedef int IdxType;
typedef struct {
    char Nama[200];
    int Harga;
    char Kategori[20];
} Item;
typedef struct {
    Item *A;
    int Capacity;
    int Neff;
} ArrayKomponen;

/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSizeKomponen
 */
ArrayKomponen MakeArrayKomponen();

/**
 * Destruktor
 * I.S. List terdefinisi
 * F.S. list->A terdealokasi
 */
void DeallocateArrayKomponen(ArrayKomponen *list);

/**
 * Fungsi untuk mengetahui apakah suatu list kosong.
 * Prekondisi: list terdefinisi
 */
boolean IsArrayKomponenEmpty(ArrayKomponen list);

/**
 * Fungsi untuk mendapatkan banyaknya elemen efektif list, 0 jika tabel kosong.
 * Prekondisi: list terdefinisi
 */
int ArrayKomponenLength(ArrayKomponen list);

/**
 * Mengembalikan elemen list L yang ke-I (indeks lojik).
 * Prekondisi: list tidak kosong, i di antara 0..Length(list).
 */
Item ArrayKomponenGet(ArrayKomponen list, IdxType i);

/**
 * Fungsi untuk mendapatkan kapasitas yang tersedia.
 * Prekondisi: list terdefinisi
 */
int ArrayKomponenGetCapacity(ArrayKomponen list);

/**
 * Fungsi untuk menambahkan elemen baru di index ke-i
 * Prekondisi: list terdefinisi, i di antara 0..Length(list).
 */
void ArrayKomponenInsertAt(ArrayKomponen *list, Item el, IdxType i);

/**
 * Fungsi untuk menambahkan elemen baru di akhir list.
 * Prekondisi: list terdefinisi
 */
void ArrayKomponenInsertLast(ArrayKomponen *list, Item el);

/**
 * Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void ArrayKomponenInsertFirst(ArrayKomponen *list, Item el);

/**
 * Fungsi untuk mengcopy seluruh elemen list.
 * Prekondisi: list terdefinisi
 */
ArrayKomponen CopyArrayKomponen(ArrayKomponen list);

/* ********** OPERASI GAME SANTO TYCOON ********** */
/**
 * Fungsi untuk membentuk Item.
 * Prekondisi: Nama, Harga, dan Kategori terdefinisi
 */
Item ArrangeItem(char Nama[],int Harga, char Kategori[]);

#endif	
