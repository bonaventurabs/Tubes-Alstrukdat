#include "../boolean/boolean.h"

#ifndef stack_H
#define stack_H
#include <stdio.h>

/* MODUL STACK
Deklarasi stack yang diimplementasi dengan tabel kontigu alokasi statik
dan ukuran sama
TOP adalah alamat elemen puncak*/

#define NilS 0
#define MaxElS 8

typedef struct {
    char NamaKomp[200];
} infotype;
typedef int address;

typedef struct
{
    infotype T[MaxElS];
    address TOP;
} Stack;

#define TOP(S) (S).TOP

/* Definisi stack S kosong : S.TOP = NilS */
/* S.TOP = jumlah element stack */
/* S.T[S.TOP-1] = element paling atas */

/* ********* Prototype ********* */

/* *** Konstruktor/Kreator *** */
void CreateEmptyStack(Stack *S);
/* I.S. Sembarang */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxElS */
/* Ciri stack kosong : TOP bernilai NilS */

/* ********* Predikat Untuk test keadaan KOLEKSI ********* */
boolean IsStackEmpty(Stack S);
/* Mengirim true jika Stack kosong*/
/* Ciri stack kosong : TOP bernilai NilS */
boolean IsStackFull(Stack S);
/* Mengirim true jika stack S penuh */
/* Ciri stack penuh : TOP bernilai MaxElS */

/* ********** Operator Dasar Stack ********* */
void Push(Stack *S, infotype X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, S tidak penuh */
/* F.S. X menjadi element TOP yang baru, TOP bertambah 1 */
void Pop(Stack *S, infotype *X);
/* Menghapus X dari Stack S. */
/* I.S. S tidak kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

/* ********** Operator Tambahan ********* */
void ForcePush(Stack *S, infotype X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, S mungkin penuh */
/* F.S. X menjadi element TOP yang baru, TOP bertambah 1
        Apabila S penuh, buang element paling bawah dari S dan masukkan X sebagai TOP
        Contoh: S berisi a b c d e f g h i j, setelah melakukan ForcePush(S, "k")
        S berisi b c d e f g h i j k */

infotype Arrangeinfotype(char Komponen[]);
/* Membentuk infotype sesuai parameter Komponen */

#endif
