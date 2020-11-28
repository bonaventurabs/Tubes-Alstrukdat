#include "./boolean/boolean.h"
#include "./point/point.h"
#include "./arrayKomponen/arrayKomponen.h"
#include "./arrayInventory/arrayInventory.h"
#include "./mesinkarakter/mesinkar.h"
#include "./mesinkarakter/mesinkata.h"
#include "./CircularQueue/circular_queue.h"
#include "./Stack/stack.h"
#include "./matriks/matriks.h"
#include "./graf/graf.h"

#include <stdio.h>
#include <stdlib.h>

void COMMAND()
/* Menginput COMMAND, mengecek commandnya, serta menjalankan commandnya */
{
    boolean exit = false;
    while (!exit){
        printf("ENTER COMMAND: ");
        InputUSER();
        if (IsKataMOVE(CKata)){

        } else if (IsKataSTATUS(CKata)){

        } else if (IsKataCHECKORDER(CKata)){

        } else if (IsKataSTARTBUILD(CKata)){

        } else if (IsKataFINISHBUILD(CKata)){

        } else if (IsKataADDCOMPONENT(CKata)){

        } else if (IsKataREMOVECOMPONENT(CKata)){

        } else if (IsKataSHOP(CKata)){

        } else if (IsKataDELIVER(CKata)){

        } else if (IsKataEND_DAY(CKata)){

        } else if (IsKataMAP(CKata)){

        } else if (IsKataEXIT(CKata)){
            exit = true;
        } else if (IsKataSAVE(CKata)){

        } else {
        
        }
        /*IsKataMOVE(CKata);
        IsKataSTATUS(CKata);
        IsKataCHECKORDER(CKata);
        IsKataSTARTBUILD(CKata);
        IsKataFINISHBUILD(CKata);
        IsKataADDCOMPONENT(CKata);
        IsKataREMOVECOMPONENT(CKata);
        IsKataSHOP(CKata);
        IsKataDELIVER(CKata);
        IsKataEND_DAY(CKata);
        IsKataMAP(CKata);
        IsKataEXIT(CKata);
        IsKataSAVE(CKata);*/
    }
}

void MOVE(){
    printf("Kamu berada pada %s\n", &posisi);
    printf("Lokasi: pemain sedang berada pada %s.\n", &posisi);
    printf("Daftar lokasi yang dapat dicapai:\n");
    for(int i=1;i<Graph;i++){ /***harus tau ADT graphnya dulu inii***/
      printf(i,". %s\n", &(Graph[i]));
    }
    int tujuan;
    printf("Nomor tujuan: ");
    scanf("%d", &tujuan);
    if (tujuan in graph){
        posisi=tujuan;
        printf("Kamu telah mencapai lokasi %s", %Graph.Nama);
    }
    else{
        printf("Tempat tersebut tidak bisa dituju. Harap pindah ke tempat terdekat telebih dahulu. Gunakan command MAP untuk detail lebih lanjut");
    }
}

void STATUS(){
    printf("Uang tersisa: $%d\n", &uang);
    printf("Build yang sedang dikerjakan: pesanan %d untuk %s.\n", &pesanan, &pelanggan);
    printf("Lokasi: pemain sedang berada pada %s.\n", &posisi);
    printf("Inventory anda:\n");
    for(int i=1;i<Inventory.neff;i++){
      printf(i,". %s (%d)\n", &(Inventory.Nama[i]), &(Inventory.Jumlah[i]));
    }
}

void DELIVER(){
    if (posisi==pelanggan.posisi){
        printf("Pesanan #%d berhasil diantarkan kepada %s!\n", &pesanan, &pelanggan);    
    }
    else{
        printf("Posisi anda belum berada di rumah %s. Harap pindah ke rumah %s terlebih dahulu!\n", &pelanggan, &pelanggan);
    }
}
int main(){
    printf("\n");
	printf("                               ____    _    __  _  _______  ____\n");
	printf("                              |  __|  / \\  |  \\| ||__   __||    |\n");
	printf("                              |____  / _ \\ | |\\  |   | |   | || |\n");
	printf("                               |___|/_/ \\_\\|_| \\_|   |_|   |____|\n");
	printf("                              --T.Y.C.O.O.N--  \n");
	printf("\n");

    printf("                                    Selamat datang di game\n");
	printf("                                         SANTO TYCOON\n");
    printf("                                         1. NEW GAME\n");
    printf("                                         2. LOAD GAME\n");
    COMMAND();
}