/* File: mesinkar.c */
/* Implementasi Mesin Karakter */

#include "mesinkar.h"
#include <stdio.h>

char CC;
boolean EOP;

static FILE *pita;
static FILE *savepita;
static int retval;

void START(char *path)
{
    /* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    pita = fopen(path, "r");
    ADV();
}

void ADV()
{
    /* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela =
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK.
          Jika  CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    retval = fscanf(pita, "%c", &CC);
    EOP = (CC == MARK);
    if (EOP)
    {
        FINISH();
    }
}

void FINISH()
/* Menutup file pita.
   I.S. : Pita terdefinisi
   F.S. : File pita tertutup */
{
    fclose(pita);
}

void STARTWRITE(char *path)
/* Menulis atau membuat file (jika belum ada) sesuai path */
{
    savepita = fopen(path, "w+");
}

void WRITEINT(int in)
/* Menulis tipe int pada file savepita */
{
    fprintf(savepita, "%d", in);
}

void WRITECHAR(char in)
/* Menulis tipe char pada file savepita */
{
    fprintf(savepita, "%c", in);
}

void WRITEBLANK()
/* Menulis blank ' ' pada file savepita (spasi) */
{
    fprintf(savepita, " ");
}

void WRITENEWLINE()
/* Mengganti baris pada penulisan file savepita (enter) */
{
    fprintf(savepita, "\n");
}

void FINISHWRITE()
/* Menutup file yang sudah ditulis */
{
    fclose(savepita);
}

void InputAngka(int *angka)
/* Membaca input angka dari user */
{
    scanf("%d", angka);
}

void InputKarakter(char *ch)
/* Membaca input karakter dari user */
{
    retval = scanf("%c", ch);
}