/* File: mesinkata.c */
/* Implementasi Mesin Kata */

#include "mesinkata.h"
#include <stdio.h>

/* State Mesin Kata */
boolean EndKata;
Kata CKata;

void IgnoreBlank()
{
    /* Mengabaikan satu atau beberapa BLANK
    I.S. : CC sembarang
    F.S. : CC ≠ MARKNL dan CC ≠ BLANK atau CC = MARK */
    int i = 0;
    while ((CC == MARKNL) || (CC == BLANK) && (CC != MARK) && (i<NMax))
    {
        ADV();
        i++;
    }
    if (i==NMax){
        FINISH();
        CC = MARK;
    }
}

void IgnoreDelimiter()
/* Mengabaikan satu atau beberapa BLANK dan batas pembeda (DELIMITER) 
    I.S. : CKata sembarang
    F.S. : CKata.TabKata[1] ≠ DELIMITER atau CKata.Length ≠ 1 */
{
    if (IsDelimiter(CKata))
    {
        ADVKATA();
    }
}

boolean IsDelimiter (Kata K)
/* Menghasilkan true jika Kata K adalah DELIMITER */
{
    Kata Delimiter;
    Delimiter.Length = 1;
    Delimiter.TabKata[1] = DELIMITER;

    return IsKataSama(Delimiter,K);
}

void STARTKATA(char *path)
{
    /* 
    I.S. : CC sembarang
    F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata 
    */
    START(path);
    IgnoreBlank();
    if (CC == MARK)
    {
        EndKata = true;
    }
    else
    {
        EndKata = false;
        SalinKata();
    }
}
void ADVKATA()
{
    /* I.S. : CC adalah karakter pertama kata yang akan diakuisisi
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
    IgnoreBlank();
    if (CC == MARK)
    {
        EndKata = true;
    }
    else
    {
        SalinKata();
    }
}
void SalinKata()
{
    /* Mengakuisisi kata, menyimpan dalam CKata
    I.S. : CC adalah karakter pertama dari kata
    F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    int i = 1;
    while ((CC != MARK) && (CC != MARKNL) && (CC != BLANK) && (i <= NMax))
    {
        CKata.TabKata[i] = CC;
        ADV();
        i++;
    }
    CKata.Length = i-1;
}

void BacaKarakter(char *ch)
/* Membaca CKata yang terdiri dari 1 karakter dan mengkonversikannya ke tipe char */
{
    IgnoreDelimiter();
    if (CKata.Length==1){
        *ch = CKata.TabKata[1];
        ADVKATA();
        IgnoreDelimiter();
    }
}

int Char2Int(char ch)
/* Mengkonversi dari karakter menjadi angka */
{
    int angka;
    sscanf(&ch, "%d", &angka);
    return angka;
}

void BacaAngka(int *angka)
/* Membaca angka dan mengkonversi dari karakter menjadi int */
{
    IgnoreDelimiter();
    int sum = 0;
    for (int i = 1; i <= CKata.Length; i++)
    {
        sum = (sum*10) + Char2Int(CKata.TabKata[i]);
    }
    *angka = sum;
    ADVKATA();
    
}

void UnionKata(char string[])
/* Membaca kata dan menggabungkan kata hingga DELIMITER, antar kata dipisahkan dengan ' ' (spasi) */
{
    int i = 0;

    IgnoreDelimiter();
    while (!IsDelimiter(CKata))
    {
        for (int j = 1; j <= CKata.Length; j++)
        {
            string[i] = CKata.TabKata[j];
            i++;
        }
        ADVKATA();
        if (!IsDelimiter(CKata)){
            string[i] = ' ';
            i++;
        } 
    }
    string[i] = '\0';
    ADVKATA();
}

void InputUSER()
/* Membaca input dari user secara keseluruhan */
{
    int i = 1;
    InputKarakter(&CC);
    while (CC==MARKNL || CC==BLANK)
    {
        InputKarakter(&CC);
    }
    
    while ((CC != MARKNL) && (i <= NMax))
    {
        CKata.TabKata[i] = CC;
        InputKarakter(&CC);
        i++;
    }
    CKata.Length = i-1;
}

boolean IsKataSama (Kata K1, Kata K2)
/* Menghasilkan true jika K1 = K2 */
{
    int i = 1;
    boolean same = true;
    if (K1.Length!=K2.Length){
        same = false;
    } else {
        while (same && i<=K1.Length){
            same = (K1.TabKata[i] == K2.TabKata[i]);
            i++;
        }
    }
    return same;
}

boolean IsKataMOVE (Kata K)
/* Menghasilkan true jika Kata K adalah MOVE */
{
    Kata KataMOVE;
    KataMOVE.Length = 4;
    KataMOVE.TabKata[1] = 'M';
    KataMOVE.TabKata[2] = 'O';
    KataMOVE.TabKata[3] = 'V';
    KataMOVE.TabKata[4] = 'E';

    return IsKataSama(KataMOVE,K);
}

boolean IsKataSTATUS (Kata K)
/* Menghasilkan true jika Kata K adalah STATUS */
{
    Kata KataSTATUS;
    KataSTATUS.Length = 6;
    KataSTATUS.TabKata[1] = 'S';
    KataSTATUS.TabKata[2] = 'T';
    KataSTATUS.TabKata[3] = 'A';
    KataSTATUS.TabKata[4] = 'T';
    KataSTATUS.TabKata[5] = 'U';
    KataSTATUS.TabKata[6] = 'S';

    return IsKataSama(KataSTATUS,K);
}

boolean IsKataCHECKORDER (Kata K)
/* Menghasilkan true jika Kata K adalah CHECKORDER */
{
    Kata KataCHECKORDER;
    KataCHECKORDER.Length = 9;
    KataCHECKORDER.TabKata[1] = 'C';
    KataCHECKORDER.TabKata[2] = 'H';
    KataCHECKORDER.TabKata[3] = 'E';
    KataCHECKORDER.TabKata[4] = 'K';
    KataCHECKORDER.TabKata[5] = 'O';
    KataCHECKORDER.TabKata[6] = 'R';
    KataCHECKORDER.TabKata[7] = 'D';
    KataCHECKORDER.TabKata[8] = 'E';
    KataCHECKORDER.TabKata[9] = 'R';

    return IsKataSama(KataCHECKORDER,K);
}

boolean IsKataSTARTBUILD (Kata K)
/* Menghasilkan true jika Kata K adalah STARTBUILD */
{
    Kata KataSTARTBUILD;
    KataSTARTBUILD.Length = 10;
    KataSTARTBUILD.TabKata[1] = 'S';
    KataSTARTBUILD.TabKata[2] = 'T';
    KataSTARTBUILD.TabKata[3] = 'A';
    KataSTARTBUILD.TabKata[4] = 'R';
    KataSTARTBUILD.TabKata[5] = 'T';
    KataSTARTBUILD.TabKata[6] = 'B';
    KataSTARTBUILD.TabKata[7] = 'U';
    KataSTARTBUILD.TabKata[8] = 'I';
    KataSTARTBUILD.TabKata[9] = 'L';
    KataSTARTBUILD.TabKata[10] = 'D';

    return IsKataSama(KataSTARTBUILD,K);
}

boolean IsKataFINISHBUILD (Kata K)
/* Menghasilkan true jika Kata K adalah FINISHBUILD */
{
    Kata KataFINISHBUILD;
    KataFINISHBUILD.Length = 11;
    KataFINISHBUILD.TabKata[1] = 'F';
    KataFINISHBUILD.TabKata[2] = 'I';
    KataFINISHBUILD.TabKata[3] = 'N';
    KataFINISHBUILD.TabKata[4] = 'I';
    KataFINISHBUILD.TabKata[5] = 'S';
    KataFINISHBUILD.TabKata[6] = 'H';
    KataFINISHBUILD.TabKata[7] = 'B';
    KataFINISHBUILD.TabKata[8] = 'U';
    KataFINISHBUILD.TabKata[9] = 'I';
    KataFINISHBUILD.TabKata[10] = 'L';
    KataFINISHBUILD.TabKata[11] = 'D';

    return IsKataSama(KataFINISHBUILD,K);
}

boolean IsKataADDCOMPONENT (Kata K)
/* Menghasilkan true jika Kata K adalah ADDCOMPONENT */
{
    Kata KataADDCOMPONENT;
    KataADDCOMPONENT.Length = 12;
    KataADDCOMPONENT.TabKata[1] = 'A';
    KataADDCOMPONENT.TabKata[2] = 'D';
    KataADDCOMPONENT.TabKata[3] = 'D';
    KataADDCOMPONENT.TabKata[4] = 'C';
    KataADDCOMPONENT.TabKata[5] = 'O';
    KataADDCOMPONENT.TabKata[6] = 'M';
    KataADDCOMPONENT.TabKata[7] = 'P';
    KataADDCOMPONENT.TabKata[8] = 'O';
    KataADDCOMPONENT.TabKata[9] = 'N';
    KataADDCOMPONENT.TabKata[10] = 'E';
    KataADDCOMPONENT.TabKata[11] = 'N';
    KataADDCOMPONENT.TabKata[12] = 'T';

    return IsKataSama(KataADDCOMPONENT,K);
}

boolean IsKataREMOVECOMPONENT (Kata K)
/* Menghasilkan true jika Kata K adalah REMOVECOMPONENT */
{
    Kata KataREMOVECOMPONENT;
    KataREMOVECOMPONENT.Length = 15;
    KataREMOVECOMPONENT.TabKata[1] = 'R';
    KataREMOVECOMPONENT.TabKata[2] = 'E';
    KataREMOVECOMPONENT.TabKata[3] = 'M';
    KataREMOVECOMPONENT.TabKata[4] = 'O';
    KataREMOVECOMPONENT.TabKata[5] = 'V';
    KataREMOVECOMPONENT.TabKata[6] = 'E';
    KataREMOVECOMPONENT.TabKata[7] = 'C';
    KataREMOVECOMPONENT.TabKata[8] = 'O';
    KataREMOVECOMPONENT.TabKata[9] = 'M';
    KataREMOVECOMPONENT.TabKata[10] = 'P';
    KataREMOVECOMPONENT.TabKata[11] = 'O';
    KataREMOVECOMPONENT.TabKata[12] = 'N';
    KataREMOVECOMPONENT.TabKata[13] = 'E';
    KataREMOVECOMPONENT.TabKata[14] = 'N';
    KataREMOVECOMPONENT.TabKata[15] = 'T';

    return IsKataSama(KataREMOVECOMPONENT,K);
}

boolean IsKataSHOP (Kata K)
/* Menghasilkan true jika Kata K adalah SHOP */
{
    Kata KataSHOP;
    KataSHOP.Length = 4;
    KataSHOP.TabKata[1] = 'S';
    KataSHOP.TabKata[2] = 'H';
    KataSHOP.TabKata[3] = 'O';
    KataSHOP.TabKata[4] = 'P';

    return IsKataSama(KataSHOP,K);
}

boolean IsKataDELIVER (Kata K)
/* Menghasilkan true jika Kata K adalah DELIVER */
{
    Kata KataDELIVER;
    KataDELIVER.Length = 7;
    KataDELIVER.TabKata[1] = 'D';
    KataDELIVER.TabKata[2] = 'E';
    KataDELIVER.TabKata[3] = 'L';
    KataDELIVER.TabKata[4] = 'I';
    KataDELIVER.TabKata[5] = 'V';
    KataDELIVER.TabKata[6] = 'E';
    KataDELIVER.TabKata[7] = 'R';

    return IsKataSama(KataDELIVER,K);
}

boolean IsKataEND_DAY (Kata K)
/* Menghasilkan true jika Kata K adalah END_DAY */
{
    Kata KataEND_DAY;
    KataEND_DAY.Length = 7;
    KataEND_DAY.TabKata[1] = 'E';
    KataEND_DAY.TabKata[2] = 'N';
    KataEND_DAY.TabKata[3] = 'D';
    KataEND_DAY.TabKata[4] = '_';
    KataEND_DAY.TabKata[5] = 'D';
    KataEND_DAY.TabKata[6] = 'A';
    KataEND_DAY.TabKata[7] = 'Y';

    return IsKataSama(KataEND_DAY,K);
}

boolean IsKataMAP (Kata K)
/* Menghasilkan true jika Kata K adalah MAP */
{
    Kata KataMAP;
    KataMAP.Length = 3;
    KataMAP.TabKata[1] = 'M';
    KataMAP.TabKata[2] = 'A';
    KataMAP.TabKata[3] = 'P';

    return IsKataSama(KataMAP,K);
}

boolean IsKataEXIT (Kata K)
/* Menghasilkan true jika Kata K adalah EXIT */
{
    Kata KataEXIT;
    KataEXIT.Length = 4;
    KataEXIT.TabKata[1] = 'E';
    KataEXIT.TabKata[2] = 'X';
    KataEXIT.TabKata[3] = 'I';
    KataEXIT.TabKata[4] = 'T';

    return IsKataSama(KataEXIT,K);
}

boolean IsKataSAVE (Kata K)
/* Menghasilkan true jika Kata K adalah SAVE */
{
    Kata KataSAVE;
    KataSAVE.Length = 3;
    KataSAVE.TabKata[1] = 'S';
    KataSAVE.TabKata[2] = 'A';
    KataSAVE.TabKata[3] = 'V';
    KataSAVE.TabKata[4] = 'E';

    return IsKataSama(KataSAVE,K);
}