/* File: mesinkar.h */
/* Definisi Mesin Karakter */

#ifndef __MESIN_KAR_H_
#define __MESIN_KAR_H_

#include "../boolean/boolean.h"

#define MARK '.'
#define MARKNL '\n'
#define MARKC ','
/* State Mesin */
extern char CC;
extern boolean EOP;

void START(char *path);
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita
          Jika CC != MARK maka EOP akan padam (false)
          Jika CC = MARK maka EOP akan menyala (true) */

void ADV();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama,
          CC mungkin = MARK
          Jika  CC = MARK maka EOP akan menyala (true) */

void STARTWRITE(char *path);
/* Menulis atau membuat file (jika belum ada) sesuai path */

void WRITEINT(int in);
/* Menulis tipe int pada file savepita */

void WRITECHAR(char in);
/* Menulis tipe char pada file savepita */

void WRITEBLANK();
/* Menulis blank ' ' pada file savepita (spasi) */

void WRITENEWLINE();
/* Mengganti baris pada penulisan file savepita (enter) */

void FINISHWRITE();
/* Menutup file yang sudah ditulis */

void InputAngka(int *angka);
/* Membaca input angka dari user */

void InputKarakter(char *ch);
/* Membaca input karakter dari user */

#endif