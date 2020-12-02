#include <stdio.h>
#include <stdlib.h>

#include "arrayInventory.h"

/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSizeInventory
 */
ArrayInventory MakeArrayInventory() {
    ArrayInventory list;
    list.A = (Element *) malloc(InitialSizeInventory * sizeof(Element));
    list.Capacity = InitialSizeInventory;
    list.Neff = 0;
    return list;
}

void DeallocateArrayInventory(ArrayInventory *list) {
    free(list->A);
}

/**
 * Fungsi untuk mengetahui apakah suatu list kosong.
 * Prekondisi: list terdefinisi
 */
boolean IsArrayInventoryEmpty(ArrayInventory list) {
    return list.Neff == 0;
}

/**
 * Fungsi untuk mendapatkan banyaknya elemen efektif list, 0 jika tabel kosong.
 * Prekondisi: list terdefinisi
 */
int ArrayInventoryLength(ArrayInventory list) {
    return list.Neff;
}

/**
 * Mengembalikan elemen list L yang ke-I (indeks lojik).
 * Prekondisi: list tidak kosong, i di antara 0..Length(list).
 */
Element ArrayInventoryGet(ArrayInventory list, IdxType i) {
    return list.A[i];
}

/**
 * Fungsi untuk mendapatkan kapasitas yang tersedia.
 * Prekondisi: list terdefinisi
 */
int ArrayInventoryGetCapacity(ArrayInventory list) {
    return list.Capacity;
}

/**
 * Fungsi untuk menambahkan elemen baru di index ke-i
 * Prekondisi: list terdefinisi, i di antara 0..Length(list).
 */
void ArrayInventoryInsertAt(ArrayInventory *list, Element el, IdxType i) {
    int length = ArrayInventoryLength(*list);
    int capacity = ArrayInventoryGetCapacity(*list);

    if (length == capacity) {
        int desiredCapacity = capacity + InitialSizeInventory;
        Element *array = (Element *) malloc(desiredCapacity * sizeof(Element));
        for (int a = 0; a < length; a++) {
            array[a] = ArrayInventoryGet(*list, a);
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
void ArrayInventoryInsertLast(ArrayInventory *list, Element el) {
    int insertAt = ArrayInventoryLength(*list);
    ArrayInventoryInsertAt(list, el, insertAt);
}

/**
 * Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void ArrayInventoryInsertFirst(ArrayInventory *list, Element el) {
    ArrayInventoryInsertAt(list, el, 0);
}
