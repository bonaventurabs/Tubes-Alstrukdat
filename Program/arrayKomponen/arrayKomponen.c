#include "arrayKomponen.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSize
 */
ArrayKomponen MakeArrayKomponen() {
    ArrayKomponen list;
    list.A = (Item *) malloc(InitialSize * sizeof(Item));
    list.Capacity = InitialSize;
    list.Neff = 0;
    return list;
}

void DeallocateArrayKomponen(ArrayKomponen *list) {
    free(list->A);
}

/**
 * Fungsi untuk mengetahui apakah suatu list kosong.
 * Prekondisi: list terdefinisi
 */
boolean IsArrayKomponenEmpty(ArrayKomponen list) {
    return list.Neff == 0;
}

/**
 * Fungsi untuk mendapatkan banyaknya elemen efektif list, 0 jika tabel kosong.
 * Prekondisi: list terdefinisi
 */
int ArrayKomponenLength(ArrayKomponen list) {
    return list.Neff;
}

/**
 * Mengembalikan elemen list L yang ke-I (indeks lojik).
 * Prekondisi: list tidak kosong, i di antara 0..Length(list).
 */
Item ArrayKomponenGet(ArrayKomponen list, IdxType i) {
    return list.A[i];
}

/**
 * Fungsi untuk mendapatkan kapasitas yang tersedia.
 * Prekondisi: list terdefinisi
 */
int ArrayKomponenGetCapacity(ArrayKomponen list) {
    return list.Capacity;
}

/**
 * Fungsi untuk menambahkan elemen baru di index ke-i
 * Prekondisi: list terdefinisi, i di antara 0..Length(list).
 */
void ArrayKomponenInsertAt(ArrayKomponen *list, Item el, IdxType i) {
    int length = ArrayKomponenLength(*list);
    int capacity = ArrayKomponenGetCapacity(*list);

    if (length == capacity) {
        int desiredCapacity = capacity + InitialSize;
        Item *array = (Item *) malloc(desiredCapacity * sizeof(Item));
        for (int a = 0; a < length; a++) {
            array[a] = ArrayKomponenGet(*list, a);
        }
        free(list->A);

        list->A = array;
        list->Capacity = desiredCapacity;
    }

    for (int a = length - 1; a >= i; a--) {
        list->A[a + 1] = list->A[a];
    }

    list->A[i] = el;
    list->Neff++;
}

/**
 * Fungsi untuk menambahkan elemen baru di akhir list.
 * Prekondisi: list terdefinisi
 */
void ArrayKomponenInsertLast(ArrayKomponen *list, Item el) {
    int insertAt = ArrayKomponenLength(*list);
    ArrayKomponenInsertAt(list, el, insertAt);
}

/**
 * Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void ArrayKomponenInsertFirst(ArrayKomponen *list, Item el) {
    ArrayKomponenInsertAt(list, el, 0);
}

/**
 * Fungsi untuk membentuk Item.
 * Prekondisi: Nama, Harga, dan Kategori terdefinisi
 */
Item ArrangeItem(char Nama[],int Harga, char Kategori[]){
    Item Item;
    
    Item.Nama = Nama;
    Item.Harga = Harga;
    Item.Kategori = Kategori;
    return Item;
}
