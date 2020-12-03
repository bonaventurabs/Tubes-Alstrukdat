#include "./boolean/boolean.h"
#include "./point/point.h"
#include "./point/ListPoint.h"
#include "./arrayKomponen/arrayKomponen.h"
#include "./arrayInventory/arrayInventory.h"
#include "./mesinkarakter/mesinkar.h"
#include "./mesinkarakter/mesinkata.h"
#include "./CircularQueue/circular_queue.h"
#include "./Stack/stack.h"
#include "./matriks/matriks.h"
#include "./graf/graf.h"

#include "./point/point.c"
#include "./point/ListPoint.c"
#include "./arrayKomponen/arrayKomponen.c"
#include "./arrayInventory/arrayInventory.c"
#include "./mesinkarakter/mesinkar.c"
#include "./mesinkarakter/mesinkata.c"
#include "./CircularQueue/circular_queue.c"
#include "./Stack/stack.c"
#include "./matriks/matriks.c"
#include "./graf/graf.c"

#include <stdio.h>
#include <stdlib.h>

// Variabel Global
ArrayKomponen Motherboard,CPU,Memory,CPUCool,Case,GPU,Storage,PSU;
ArrayKomponen All; //gabungan dari seluruh komponen
ListObjek Bangunan; //list menyimpan bangunan dan lokasinya
POINT LokasiPlayer; //lokasi player
ArrayInventory Inventory; //inventory player
MATRIKS Map; //peta game
Graph GrafBangunan; //graf bangunan
Queue Pesanan;
Stack Build;
int uang;
int CurrPelanggan;
int CurrPesanan=0;

void LOGO(){
    printf("\n");
	printf("                               ____    _    __  _  _______  ____\n");
	printf("                              |  __|  / \\  |  \\| ||__   __||    |\n");
	printf("                              |____  / _ \\ | |\\  |   | |   | || |\n");
	printf("                               |___|/_/ \\_\\|_| \\_|   |_|   |____|\n");
	printf("                              --T.Y.C.O.O.N--  \n");
	printf("\n");
}

void MENU(int *inputmenu){
    printf("                                    Selamat datang di game\n");
    printf("                                         SANTO TYCOON\n");
    printf("                                         1. NEW GAME\n");
    printf("                                         2. LOAD GAME\n");
    printf("                                         >");
    InputAngka(inputmenu);
    printf("\n");
    while (*inputmenu!=1 && *inputmenu!=2){
        printf("                    Input tidak terdefinisi, silahkan masukan angka menu");
        printf("                                     >");
        InputAngka(inputmenu);
    }
}

void KonfigurasiItem(char *path, ArrayKomponen *Komponen, ArrayKomponen *All){
    /* Mengonfigurasi file eksternal komponen ke dalam variabel2 Komponen */
    char Nama[200];
    int Harga;
    char Kategori[20];
    Item Insert;

    *Komponen = MakeArrayKomponen();
    STARTKATA(path);
    ADVKATA();
    while (!EndKata){
        UnionKata(Nama);
        BacaAngka(&Harga);
        UnionKata(Kategori);
        Insert = ArrangeItem(Nama,Harga,Kategori);
        ArrayKomponenInsertLast(Komponen,Insert);
        ArrayKomponenInsertLast(All,Insert);
    }
}

void KonfigurasiMap(char *path,MATRIKS *Map,ListObjek *Objek,POINT *LokPlayer,Graph *GrafB){
    int NBaris;
    int NKolom;
    int NObjek;
    char Simbol;
    int X,Y;
    int ElmtM;
    adrNode P;

    STARTKATA(path);
    BacaAngka(&NBaris);
    printf("%d\n",NBaris);
    BacaAngka(&NKolom);
    printf("%d\n",NKolom);
    MakeMATRIKS(NBaris,NKolom,Map);
    InsertKosong(Map);
    BacaAngka(&NObjek);
    printf("%d\n",NObjek);
    MakeListObjek(Objek);

    for (int i = 1; i <= NObjek; i++){
        BacaKarakter(&Simbol);
        printf("%c",Simbol);
        BacaAngka(&X);
        printf("%d",X);
        BacaAngka(&Y);
        printf("%d\n",Y);
        InsertListObjek(Objek,Simbol,X,Y);
        BacaMAP(Map,Simbol,X,Y);
        if (Simbol=='B'){
            *LokPlayer = MakePOINT(X,Y);
        }
    }
    printf("%d\n",Absis(Point(*Objek,9)));
    TulisMAP(*Map,1,1);
    printf("\n");
    CreateEmptyGraph(GrafB);

    for (int i = 1; i <= NObjek(*Objek); i++)
    {
        InsertNode(GrafB,i,&P);
    }
    
    for (int i = 1; i <= NObjek(*Objek); i++){
        for (int j = 1; j <= NObjek(*Objek); j++){
            BacaAngka(&ElmtM);
            if (ElmtM==1){
                InsertEdge(GrafB,i,j);
            }
        }
    }
    printf("oke");
    FINISH();
}

int main(){
    KonfigurasiMap("./File eksternal/Map.txt", &Map, &Bangunan, &LokasiPlayer, &GrafBangunan);
    printf("oke");

        
    
}
