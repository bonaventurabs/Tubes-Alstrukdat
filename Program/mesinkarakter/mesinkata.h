/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "../boolean/boolean.h"
#include "mesinkar.h"

#define NMax 50
#define BLANK ' '

typedef struct
{
    char TabKata[NMax + 1]; /* container penyimpan kata, indeks yang dipakai [1..NMax] */
    int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

void IgnoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATA(char *path);
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

int Char2Int(char *ch);
/* Mengkonversi dari karakter menjadi angka */

void BacaAngka();
/* Membaca angka dan mengkonversi dari karakter menjadi int */

void InputUSER();
/* Membaca input dari user secara keseluruhan */

boolean IsKataSama (Kata K1, Kata K2);
/* Menghasilkan true jika K1 = K2 */

boolean IsKataMOVE (Kata K);
/* Menghasilkan true jika Kata K adalah MOVE */

boolean IsKataSTATUS (Kata K);
/* Menghasilkan true jika Kata K adalah STATUS */

boolean IsKataCHECKORDER (Kata K);
/* Menghasilkan true jika Kata K adalah CHECKORDER */

boolean IsKataSTARTBUILD (Kata K);
/* Menghasilkan true jika Kata K adalah STARTBUILD */

boolean IsKataFINISHBUILD (Kata K);
/* Menghasilkan true jika Kata K adalah FINISHBUILD */

boolean IsKataADDCOMPONENT (Kata K);
/* Menghasilkan true jika Kata K adalah ADDCOMPONENT */

boolean IsKataREMOVECOMPONENT (Kata K);
/* Menghasilkan true jika Kata K adalah REMOVECOMPONENT */

boolean IsKataSHOP (Kata K);
/* Menghasilkan true jika Kata K adalah SHOP */

boolean IsKataDELIVER (Kata K);
/* Menghasilkan true jika Kata K adalah DELIVER */

boolean IsKataEND_DAY (Kata K);
/* Menghasilkan true jika Kata K adalah END_DAY */

boolean IsKataMAP (Kata K);
/* Menghasilkan true jika Kata K adalah MAP */

boolean IsKataEXIT (Kata K);
/* Menghasilkan true jika Kata K adalah EXIT */

boolean IsKataSAVE (Kata K);
/* Menghasilkan true jika Kata K adalah SAVE */

void InputCOMMAND();
/* Menginput COMMAND dan mengecek commandnya */

#endif