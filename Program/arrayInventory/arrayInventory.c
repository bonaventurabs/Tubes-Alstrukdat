#include "arrayInventory.h"

/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSize
 */
ArrayInventory MakeList() {
    ArrayInventory list;
    list.A = (ElType *) malloc(InitialSize * sizeof(ElType));
    list.Capacity = InitialSize;
    list.Neff = 0;
    return list;
}

void DeallocateList(ArrayInventory *list) {
    free(list->A);
}

/**
 * Fungsi untuk mengetahui apakah suatu list kosong.
 * Prekondisi: list terdefinisi
 */
boolean IsEmpty(ArrayInventory list) {
    return list.Neff == 0;
}

/**
 * Fungsi untuk mendapatkan banyaknya elemen efektif list, 0 jika tabel kosong.
 * Prekondisi: list terdefinisi
 */
int Length(ArrayInventory list) {
    return list.Neff;
}

/**
 * Mengembalikan elemen list L yang ke-I (indeks lojik).
 * Prekondisi: list tidak kosong, i di antara 0..Length(list).
 */
ElType Get(ArrayInventory list, IdxType i) {
    return list.A[i];
}

/**
 * Fungsi untuk mendapatkan kapasitas yang tersedia.
 * Prekondisi: list terdefinisi
 */
int GetCapacity(ArrayInventory list) {
    return list.Capacity;
}

/**
 * Fungsi untuk menambahkan elemen baru di index ke-i
 * Prekondisi: list terdefinisi, i di antara 0..Length(list).
 */
void InsertAt(ArrayInventory *list, ElType el, IdxType i) {
    int length = Length(*list);
    int capacity = GetCapacity(*list);

    if (length == capacity) {
        int desiredCapacity = capacity + InitialSize;
        ElType *array = (ElType *) malloc(desiredCapacity * sizeof(ElType));
        for (int a = 0; a < length; a++) {
            array[a] = Get(*list, a);
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
void InsertLast(ArrayInventory *list, ElType el) {
    int insertAt = Length(*list);
    InsertAt(list, el, insertAt);
}

/**
 * Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void InsertFirst(ArrayInventory *list, ElType el) {
    InsertAt(list, el, 0);
}
