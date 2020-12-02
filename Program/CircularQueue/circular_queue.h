/* MODUL CIRCULAR QUEUE */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Implementasi Queue menggunakan circular buffer (Alternatif III) */

#ifndef __circular_queue_h__
#define __circular_queue_h__

#include "../boolean/boolean.h"

/* Nilai untuk indeks yang tidak terdefinisi */
#define NIL -999

/* Definisi tipe elemen dan indeks pada Queue */
typedef int IdxType;

typedef struct { int Pemesan;
                 int Nilai;
                 char *Motherboard;
                 char *CPU;
                 char *Memory;
                 char *CPU_Cooler;
                 char *Case;
                 char *GPU;
                 char *Storage;
                 char *PSU;
               } Pesan;

typedef struct { Pesan *Tab;  /* tabel penyimpan elemen */
                 IdxType HEAD;  /* indeks elemen paling awal (terdepan) */
                 IdxType TAIL;  /* indeks tempat menambah elemen baru */
                 int MaxEl;     /* kapasitas jumlah elemen */
               } Queue;
/* Definisi Queue kosong: HEAD=NIL; TAIL=NIL. */

/* ********* Prototype ********* */
boolean IsQueueEmpty (Queue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsQueueFull (Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int LengthQueue (Queue Q);
/* Mengirimkan banyaknya elemen Q, 0 jika kosong */
int MaxLength (Queue Q);
/* Mengirimkan kapasitas jumlah elemen Q */

/* *** Kreator *** */
Queue CreateQueue (int Max);
/* Proses : Melakukan alokasi memori, membuat sebuah Q kosong */
/* I.S. sembarang */
/* F.S. mengembalikan Q kosong dengan kondisi sbb: */
/*   Jika alokasi berhasil, Tab dialokasi berukuran Max */
/*   Jika alokasi gagal, Q kosong dengan MaxEl=0 */

/* *** Destruktor *** */
void DeleteQueue (Queue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. membebaskan memori Tab, Q.MaxEl di-set 0 */

/* *** Primitif Add/Delete *** */
void PushQueue (Queue * Q, ElType X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru,
        TAIL "maju" dengan mekanisme circular buffer
        Jika Q kosong, HEAD dimulai dari 0 */
ElType PopQueue (Queue * Q);
/* Proses: Menghapus indeks HEAD pada Q dengan aturan FIFO, lalu mengembalikan nilainya */
/* I.S. Q tidak mungkin kosong */
/* F.S. mengembalikan nilai Q pada indeks HEAD;
        HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
ElType Front (Queue Q);
/* Proses: Mengembalikan nilai Q pada indeks HEAD tanpa penghapusan */
/* I.S. Q tidak mungkin kosong */
/* F.S. mengembalikan nilai Q pada indeks HEAD;
        Q pasti tetap tidak kosong */

/* *** Utilitas *** */
Queue CopyQueue (Queue Q);
/* Proses: Mengembalikan Queue baru dengan isi antrean sama seperti Q */
/* I.S. Q pernah dialokasi */
/* F.S. Queue baru dengan nilai isi antrean sama seperti Q;
        HEAD pada Queue baru dimulai dari 0 */

#endif
