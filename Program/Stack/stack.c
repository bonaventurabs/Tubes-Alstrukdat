#include "../boolean/boolean.h"
#include "stack.h"

void CreateEmptyStack(Stack *S)
/* I.S. Sembarang */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* Ciri stack kosong : TOP bernilai NilS */
{
    S->TOP = NilS;
}

/* ********* Predikat Untuk test keadaan KOLEKSI ********* */
boolean IsStackEmpty(Stack S)
/* Mengirim true jika Stack kosong*/
/* Ciri stack kosong : TOP bernilai NilS */
{
    return S.TOP == NilS;
}

boolean IsStackFull(Stack S)
/* Mengirim true jika stack S penuh */
/* Ciri stack penuh : TOP bernilai MaxEl */
{
    return S.TOP == MaxEl;
}
/* ********** Operator Dasar Stack ********* */
void Push(Stack *S, infotype X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, S tidak penuh */
/*F.S. X menjadi element TOP yang baru, TOP bertambah 1 */
{
    S->T[S->TOP] = X;
    S->TOP++;
}
void Pop(Stack *S, infotype *X)
/* Menghapus X dari Stack S. */
/* I.S. S tidak kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
    S->TOP--;
    (*X) = S->T[S->TOP];
}

void ForcePush(Stack *S, infotype X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, S mungkin penuh */
/* F.S. X menjadi element TOP yang baru, TOP bertambah 1
        Apabila S penuh, buang element paling bawah dari S dan masukkan X sebagai TOP
        Contoh: S berisi a b c d e f g h i j, setelah melakukan ForcePush(S, "k")
        S berisi b c d e f g h i j k */
{
    int idx;
    if (!IsStackFull(*S))
    {
        Push(S, X);
    }
    else
    {
        for (idx = 0; idx < S->TOP - 1; idx++)
        {
            S->T[idx] = S->T[idx + 1];
        }
        S->T[S->TOP - 1] = X;
    }
}
