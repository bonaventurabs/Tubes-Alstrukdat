#include "arrayKomponen.h"


/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSize
 */
ArrayKomponen MakeArrayKomponen() {
    ArrayKomponen list;
    list.A = (ElType *) malloc(InitialSize * sizeof(ElType));
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
ElType ArrayKomponenGet(ArrayKomponen list, IdxType i) {
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
void ArrayKomponenInsertAt(ArrayKomponen *list, ElType el, IdxType i) {
    int length = ArrayKomponenLength(*list);
    int capacity = ArrayKomponenGetCapacity(*list);

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
void ArrayKomponenInsertLast(ArrayKomponen *list, ElType el) {
    int insertAt = Length(*list);
    ArrayKomponenInsertAt(list, el, insertAt);
}

/**
 * Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void ArrayKomponenInsertFirst(ArrayKomponen *list, ElType el) {
    ArrayKomponenInsertAt(list, el, 0);
}
