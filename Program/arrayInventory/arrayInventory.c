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

/**
/* I.S. list terdefinisi, tidak kosong,  
/* F.S. Elemen list sesuai indeks logic dihapus dari list. 
*/
void ArrayInventoryDeleteAt (ArrayInventory *list, Element *el, IdxType i){
    
    IdxType j;
    if (!IsArrayInventoryEmpty(*list)){
        *el = list->A[i];
        if (i!=list->Neff-1){
            for (j=i; i<list->Neff-1;j++){
                list->A[j] = list->A[j+1];
            }
        }
        list->Neff--;
        if (list->Neff<list->Capacity/4){
            list->Capacity = list->Capacity/2;
            list->A = (Element*) realloc (list->A,list->Capacity*sizeof(Element));
        }
    }
}

/**
 * Fungsi untuk mendapatkan indeks dari Elemen sesuai NoPesanan
 * Prekondisi: terdapat build yang tersimpan di inventory.
 */
IdxType IndeksInventPesanan(ArrayInventory list, int NoPesanan){
    boolean found = false;
    int i = 0;
    int Nomor;

    while (!found && i < list.Neff){
        if(IsStrEqual(list.A[i].Jenis,"Build")){
            sscanf(list.A[i].Nama,"Build untuk Pesanan #%d",&Nomor);
            if (Nomor==NoPesanan){
                found = true;
            } else {
                i++;
            } 
        } else {
            i++;
        }
    }
    if (found){
        return i;
    } else {
        return -99;
    }
}

/**
 * Fungsi untuk membentuk Element.
 * Prekondisi: Nama dan Jumlah terdefinisi
 */
Element ArrangeElement(char Nama[],int Jumlah, char Jenis[]){
    Element Elemen;
    int i;
    
    for (i = 0; Nama[i] != '\0'; ++i) {
        Elemen.Nama[i] = Nama[i];
    }
    Elemen.Nama[i] = '\0';

    Elemen.Jumlah = Jumlah;

    for (i = 0; Jenis[i] != '\0'; ++i) {
        Elemen.Jenis[i] = Jenis[i];
    }
    Elemen.Jenis[i] = '\0';
    return Elemen;
}
