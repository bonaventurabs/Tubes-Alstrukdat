#ifndef __DYNAMIC_LIST__
#define __DYNAMIC_LIST__
#include "../boolean/boolean.h"

#define InitialSize 10

typedef int IdxType;
typedef int ElType;
typedef struct {
    ElType *A;
    int Capacity;
    int Neff;
} DynamicList;

/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSize
 */
DynamicList MakeList();

/**
 * Destruktor
 * I.S. List terdefinisi
 * F.S. list->A terdealokasi
 */
void DeallocateList(DynamicList *list);

/**
 * Fungsi untuk mengetahui apakah suatu list kosong.
 * Prekondisi: list terdefinisi
 */
boolean IsEmpty(DynamicList list);

/**
 * Fungsi untuk mendapatkan banyaknya elemen efektif list, 0 jika tabel kosong.
 * Prekondisi: list terdefinisi
 */
int Length(DynamicList list);

/**
 * Mengembalikan elemen list L yang ke-I (indeks lojik).
 * Prekondisi: list tidak kosong, i di antara 0..Length(list).
 */
ElType Get(DynamicList list, IdxType i);

/**
 * Fungsi untuk mendapatkan kapasitas yang tersedia.
 * Prekondisi: list terdefinisi
 */
int GetCapacity(DynamicList list);

/**
 * Fungsi untuk menambahkan elemen baru di index ke-i
 * Prekondisi: list terdefinisi, i di antara 0..Length(list).
 */
void InsertAt(DynamicList *list, ElType el, IdxType i);

/**
 * Fungsi untuk menambahkan elemen baru di akhir list.
 * Prekondisi: list terdefinisi
 */
void InsertLast(DynamicList *list, ElType el);

/**
 * Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void InsertFirst(DynamicList *list, ElType el);

#endif	
