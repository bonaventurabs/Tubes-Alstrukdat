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
    while (*inputmenu!=1 || *inputmenu!=2){
        printf("                    Input tidak terdefinisi, silahkan masukan angka menu")
        printf("                                     >");
        InputAngka(inputmenu);
    }
}

void KonfigurasiItem(char *path, ArrayKomponen *Komponen){
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
    }
}

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

void CHECKORDER(){
    printf("Nomor Order: %s\n", pesanan);
    printf("Pemesan: %d\n", pelanggan);
    printf("Invoice: %s\n", harga);
    printf("Komponen:\n");
    for(int i=1;i<Komponen.neff;i++){
        printf("%d. %s\n", i, (Komponen.Nama[i]));
    }
}

void STARTBUILD(){
    printf("Kami telah memulai %d untuk %s\n.", pesanan, pelanggan); 
}

void ADDCOMPONENT(ArrayInventory Inventory, Stack S){
    int x;
    printf("komponen yang telah terpasang:\n");
    for(int i=1;i<Top(S);i++){
        printf("%d. %s\n", i, (InfoTop(S)));
    }
    printf("Komponen yang tersedia\n");
    for(int i=1;i<Inventory.neff;i++){
        printf("&d. %s\n", i, (Inventory.Nama[i-1]));
    }

    printf("Komponen yang ingin dipasang: \n");
    scanf("%d", &x);
    if (x == i){ /*masih gatau gimana caranya ngilangin komponen yang tersedia kalo dipilih buat dipasang */
        Push(S, Inventory.Nama[i]);
        printf("Komponen berhasil dipasang! \n");
    }
    else{
        printf("Komponen tidak tersedia!");
    }   
}

void REMOVECOMPONENT(){
    printf("Komponen %d\n", &InfoTop(S), "berhasil dicopot!");
    Pop(S);
}

void FINISHBUILD(){
    if(){ /*Masih belum tau if conditionalnya gimana */
        printf("%d", pesanan, "telah selesai. Silahkan antar ke %s\n", pelanggan);
    }
    else{
        printf("Komponen yang dipasangkan belum sesuai dengan pesanan, build belum dapat diselesaikan")
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
    /* Variabel */
    int *inputmenu;

    LOGO();
    MENU(inputmenu);
    if (*inputmenu==1){

    } else {

    }
    COMMAND();
}
