#include "arrayDelivery.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Konstruktor
 * I.S. sembarang
 * F.S. Terbentuk List kosong dengan ukuran InitialSizeDelivery
 */
ArrayDelivery MakeArrayDelivery() {
    ArrayDelivery list;
    list.A = (DelBuild *) malloc(InitialSizeDelivery * sizeof(DelBuild));
    list.Capacity = InitialSizeDelivery;
    list.Neff = 0;
    return list;
}

void DeallocateArrayDelivery(ArrayDelivery *list) {
    free(list->A);
}

/**
 * Fungsi untuk mengetahui apakah suatu list kosong.
 * Prekondisi: list terdefinisi
 */
boolean IsArrayDeliveryEmpty(ArrayDelivery list) {
    return list.Neff == 0;
}

/**
 * Fungsi untuk mendapatkan banyaknya elemen efektif list, 0 jika tabel kosong.
 * Prekondisi: list terdefinisi
 */
int ArrayDeliveryLength(ArrayDelivery list) {
    return list.Neff;
}

/**
 * Mengembalikan elemen list L yang ke-I (indeks lojik).
 * Prekondisi: list tidak kosong, i di antara 0..Length(list).
 */
DelBuild ArrayDeliveryGet(ArrayDelivery list, IdxType i) {
    return list.A[i];
}

/**
 * Fungsi untuk mendapatkan kapasitas yang tersedia.
 * Prekondisi: list terdefinisi
 */
int ArrayDeliveryGetCapacity(ArrayDelivery list) {
    return list.Capacity;
}

/**
 * Fungsi untuk menambahkan elemen baru di index ke-i
 * Prekondisi: list terdefinisi, i di antara 0..Length(list).
 */
void ArrayDeliveryInsertAt(ArrayDelivery *list, DelBuild el, IdxType i) {
    int length = ArrayDeliveryLength(*list);
    int capacity = ArrayDeliveryGetCapacity(*list);

    if (length == capacity) {
        int desiredCapacity = capacity + InitialSizeDelivery;
        DelBuild *array = (DelBuild *) malloc(desiredCapacity * sizeof(DelBuild));
        for (int a = 0; a < length; a++) {
            array[a] = ArrayDeliveryGet(*list, a);
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
void ArrayDeliveryInsertLast(ArrayDelivery *list, DelBuild el) {
    int insertAt = ArrayDeliveryLength(*list);
    ArrayDeliveryInsertAt(list, el, insertAt);
}

/**
 * Fungsi untuk menambahkan elemen baru di awal list.
 * Prekondisi: list terdefinisi
 */
void ArrayDeliveryInsertFirst(ArrayDelivery *list, DelBuild el) {
    ArrayDeliveryInsertAt(list, el, 0);
}

/**
/* I.S. list terdefinisi, tidak kosong,  
/* F.S. Elemen list sesuai indeks logic dihapus dari list. 
*/
void ArrayDeliveyDeleteAt (ArrayDelivery *list, DelBuild *el, IdxType i){
    
    IdxType j;
    if (!IsArrayDeliveryEmpty(*list)){
        *el = list->A[i];
        if (i!=list->Neff-1){
            for (j=i; i<list->Neff-1;j++){
                list->A[j] = list->A[j+1];
            }
        }
        list->Neff--;
        if (list->Neff<list->Capacity/4){
            list->Capacity = list->Capacity/2;
            list->A = (DelBuild*) realloc (list->A,list->Capacity*sizeof(DelBuild));
        }
    }
}

/**
/* I.S. list terdefinisi.
/* F.S. true jika terdapat Element dengan NoPesanan. 
*/
boolean IsNoPesananAda (ArrayDelivery list, int NoPesanan)
{
    boolean found = false;
    int i = 0;
    if (!IsArrayDeliveryEmpty(list)){
        while (!found && i<list.Neff){
            if (list.A[i].NoPesanan==NoPesanan){
                found = true;
            } else {
                i++;
            }
        }
    }
    return found;
}

/**
/* I.S. list terdefinisi, NoPesanan ada di list.
/* F.S. indeks logic dari Elemet list NoPesanan di return 
*/
IdxType IndeksNoPesanan (ArrayDelivery list, int NoPesanan)
{
    boolean found = false;
    int i = 0;
    if (!IsArrayDeliveryEmpty(list)){
        while (!found && i<list.Neff){
            if (list.A[i].NoPesanan==NoPesanan){
                found = true;
            } else {
                i++;
            }
        }
    }
    return i; 
}

/**
/* I.S. list terdefinisi.
/* F.S. true jika terdapat Element dengan Pemesan. 
*/
boolean IsPemesanAda (ArrayDelivery list, int Pemesan)
{
    boolean found = false;
    int i = 0;
    if (!IsArrayDeliveryEmpty(list)){
        while (!found && i<list.Neff){
            if (list.A[i].Pemesan=Pemesan){
                found = true;
            } else {
                i++;
            }
        }
    }
    return found;
}

/**
/* I.S. list terdefinisi, NoPesanan ada di list.
/* F.S. indeks logic dari Elemet list Pemesan di return 
*/
IdxType IndeksPemesan (ArrayDelivery list, int Pemesan)
{
    boolean found = false;
    int i = 0;
    if (!IsArrayDeliveryEmpty(list)){
        while (!found && i<list.Neff){
            if (list.A[i].Pemesan==Pemesan){
                found = true;
            } else {
                i++;
            }
        }
    }
    return i; 
}


/* ********** OPERASI GAME SANTO TYCOON ********** */
/**
 * Fungsi untuk membentuk DelBuild.
 * Prekondisi: NoPesanan, Pemesan, dan Invoice terdefinisi
 */
DelBuild ArrangeDelBuild(int NoPesanan,int Pemesan, int Invoice)
{
    DelBuild DelBuild;
    
    DelBuild.NoPesanan = NoPesanan;
    DelBuild.Pemesan = Pemesan;
    DelBuild.Invoice = Invoice;
    return DelBuild;
}
