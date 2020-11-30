#ifndef __DYNAMIC_LIST__
#define __DYNAMIC_LIST__
#include "../boolean/boolean.h"

#define InitialSize 10

typedef int IdxType;
typedef struct {
    char Nama[100];
    int Harga;
    char Kategori[20];
} ElType;
typedef struct {
    ElType *A;
    int Capacity;
    int Neff;
} ArrayKomponen;

/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSize
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
ElType ArrayKomponenGet(ArrayKomponen list, IdxType i);

/**
 * Fungsi untuk mendapatkan kapasitas yang tersedia.
 * Prekondisi: list terdefinisi
 */
int ArrayKomponenGetCapacity(ArrayKomponen list);

/**
 * Fungsi untuk menambahkan elemen baru di index ke-i
 * Prekondisi: list terdefinisi, i di antara 0..Length(list).
 */
void ArrayKomponenInsertAt(ArrayKomponen *list, ElType el, IdxType i);

/**
 * Fungsi untuk menambahkan elemen baru di akhir list.
 * Prekondisi: list terdefinisi
 */
void ArrayKomponenInsertLast(ArrayKomponen *list, ElType el);

/**
 * Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void ArrayKomponenInsertFirst(ArrayKomponen *list, ElType el);

#endif	
