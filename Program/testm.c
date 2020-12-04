#include "./boolean/boolean.h"
#include "./point/point.h"
#include "./point/ListPoint.h"
#include "./arrayKomponen/arrayKomponen.h"
#include "./arrayInventory/arrayInventory.h"
#include "./arrayDelivery/arrayDelivery.h"
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
#include "./arrayDelivery/arrayDelivery.c"
#include "./mesinkarakter/mesinkar.c"
#include "./mesinkarakter/mesinkata.c"
#include "./CircularQueue/circular_queue.c"
#include "./Stack/stack.c"
#include "./matriks/matriks.c"
#include "./graf/graf.c"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NKomponen 8

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
ArrayDelivery Delivery;
int uang;
boolean startbuild = false;

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
    printf("                                         > ");
    InputAngka(inputmenu);
    printf("\n");
    while (*inputmenu!=1 && *inputmenu!=2){
        printf("                    Input tidak terdefinisi, silahkan masukan angka menu");
        printf("                                     > ");
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
    int countC = 0;
    char count;
    int X,Y;
    int ElmtM;
    adrNode P;

    STARTKATA(path);
    BacaAngka(&NBaris);
    BacaAngka(&NKolom);
    MakeMATRIKS(NBaris,NKolom,Map);
    InsertKosong(Map);
    BacaAngka(&NObjek);
    MakeListObjek(Objek);

    for (int i = 1; i <= NObjek; i++){
        BacaKarakter(&Simbol);
        BacaAngka(&X);
        BacaAngka(&Y);
        InsertListObjek(Objek,Simbol,X,Y);
        if (Simbol=='C'){
            countC++;
            count = '0' + countC;
            BacaMAP(Map,count,X,Y);
        } else {
            BacaMAP(Map,Simbol,X,Y);
        }
        if (Simbol=='B'){
            *LokPlayer = MakePOINT(X,Y);
        }
    }
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
    FINISH();
}

void MOVE(){
    char NamaLokPlayer[100];
    char NamaLokasi[100];
    char NamaLokasiTujuan[100];
    int id;
    adrNode NodeLokasiPlayer;
    adrSuccNode DaftarLokasi,NodeLokTujuan;
    int j = 1;
    int tujuan;

    TulisBangunanLok(Bangunan,LokasiPlayer,NamaLokPlayer);
    id = SearchIndeks(Bangunan,LokasiPlayer);
    NodeLokasiPlayer=SearchNode(GrafBangunan,id);

    printf("Kamu berada pada %s \n",NamaLokPlayer);
    printf("Daftar lokasi yang dapat dicapai:\n");
    DaftarLokasi = Trail(NodeLokasiPlayer);
    while (DaftarLokasi!=Nil){
        TulisBangunanInd(Bangunan,Id(Succ(DaftarLokasi)),NamaLokasi);
        printf("%d. %s\n",j,NamaLokasi);

        DaftarLokasi = NextG(DaftarLokasi);
        j++;
    }

    printf("Nomor tujuan: ");
    scanf("%d", &tujuan);

    if (1 <= tujuan && tujuan < j){
        int k=1;
        NodeLokTujuan=Trail(NodeLokasiPlayer);
        while (k!=tujuan){
            NodeLokTujuan=NextG(NodeLokTujuan);
            k++;    
        }
        infograph IdTujuan= Id(Succ(NodeLokTujuan));
        POINT LokasiTujuan=Point(Bangunan,IdTujuan);
        
        LokasiPlayer = MakePOINT(Absis(LokasiTujuan),Ordinat(LokasiTujuan));

        TulisBangunanLok(Bangunan,LokasiTujuan,NamaLokasiTujuan);
        printf("Kamu telah mencapai lokasi %s\n", NamaLokasiTujuan);
    }
    else{
        printf("Tempat tersebut tidak bisa dituju. Harap pindah ke tempat terdekat telebih dahulu!\n");
    }
}

void STATUS(){
    char NamaLokPlayer[100];
    TulisBangunanLok(Bangunan,LokasiPlayer,NamaLokPlayer);
    printf("Uang tersisa: $%d\n", uang);
    printf("Build yang sedang dikerjakan: ");
    if (startbuild){
        printf("pesanan %d untuk Pelanggan %d.\n", Pesanan.OrderNum, Pesanan.Tab[Pesanan.HEAD].Pemesan);
    } else {
        printf("-\n");
    }
    printf("Lokasi: pemain sedang berada pada %s.\n", NamaLokPlayer);
    printf("Inventory anda:\n");
    if (Inventory.Neff>0){
        for(int i=0;i<Inventory.Neff;i++){
            printf("%d. %s (%d)\n",(i+1), Inventory.A[i].Nama, Inventory.A[i].Jumlah);
        }
    }
}

void CHECKORDER(){
    if (IsQueueEmpty(Pesanan)){
        printf("Tidak ada pesanan!\n");
    } else {
        printf("Nomor Order: %d\n", Pesanan.OrderNum);
        printf("Pemesan: Pelanggan %d\n", Pesanan.Tab[Pesanan.HEAD].Pemesan);
        printf("Invoice: $%d\n", Pesanan.Tab[Pesanan.HEAD].Nilai);
        printf("Komponen:\n");
        for (int i = 0; i < 8; i++)
        {
            printf("%d. %s\n",i+1 , Pesanan.Tab[Pesanan.HEAD].Detail[i]);
        } 
    }     
}

void STARTBUILD(){
    startbuild = true;
    CreateEmptyStack(&Build);
    printf("Kamu telah memulai pesanan %d untuk Pelanggan %d.\n", Pesanan.OrderNum, Pesanan.Tab[Pesanan.HEAD].Pemesan); 
}

void ADDCOMPONENT(){ 
    int x;
    infotype KompBuild;
    printf("Komponen yang telah terpasang:\n");
    if (IsStackEmpty(Build)){
        printf("\n");
    } else {
        for(int i=0;i<TOP(Build);i++){
           printf("%d. %s\n", (i+1), Build.T[i].NamaKomp);
        }
    }
    printf("Komponen yang tersedia\n");
    for(int i=0;i<Inventory.Neff;i++){
        if (IsStrEqual("Komponen",Inventory.A[i].Jenis)){
            printf("&d. %s\n", (i+1), Inventory.A[i].Nama);
        }
    }

    printf("Komponen yang ingin dipasang: \n");
    scanf("%d", &x);
    if (x>=1 && x <= Inventory.Neff){
        KompBuild = Arrangeinfotype(Inventory.A[x-1].Nama); 
        Push(&Build, KompBuild);
        Inventory.A[x-1].Jumlah--;
        if (Inventory.A[x-1].Jumlah==0){
            if ((x-1)!=Inventory.Neff-1){
                for(int i=x-1;i<(Inventory.Neff-1) ;i++){
                    Inventory.A[i]=Inventory.A[i+1];
                }
            }
            Inventory.Neff--;
        }
        printf("Komponen berhasil dipasang! \n");
    }
    else{
        printf("Komponen tidak tersedia!");
    }   
}

void REMOVECOMPONENT(){
    infotype infocopot;
    char copot[200];
    Element simpan;
    boolean found = false;
    int i = 0;

    Pop(&Build,&infocopot);
    CopyStr(infocopot.NamaKomp,copot);
    while (!found && i<Inventory.Neff){
        if (IsStrEqual(copot,Inventory.A[i].Nama)){
            Inventory.A[i].Jumlah++;
            found = true;
        } else {
            i++;
        }
    }
    if (!found){
        simpan = ArrangeElement(copot,1,"Komponen");
        ArrayInventoryInsertLast(&Inventory,simpan);
    }
    printf("Komponen %d\n", &copot, " berhasil dicopot!");
}

void FINISHBUILD(){
    boolean benar=true;
    int i = 0;
    while (benar && i < 8){
        if (!IsStrEqual(Build.T[i].NamaKomp,Pesanan.Tab[Pesanan.HEAD].Detail[i])){
            benar = false;
        } else {
            i++;
        }
    }
      
    if(benar){
        Element Komputer;
        char KomputerF [100];
        DelBuild DelKomputer;
        Order OrderFinish;

        OrderFinish = PopQueue(&Pesanan);
         
        printf("Pesanan %d telah selesai. Silahkan antar ke Pelanggan %d\n", Pesanan.OrderNum-1, OrderFinish.Pemesan);
        
        sprintf(KomputerF,"Build untuk Pesanan #%d",Pesanan.OrderNum-1);
        Komputer = ArrangeElement(KomputerF,1,"Build");
        ArrayInventoryInsertLast(&Inventory,Komputer);

        DelKomputer = ArrangeDelBuild(Pesanan.OrderNum-1,OrderFinish.Pemesan,OrderFinish.Nilai);
        ArrayDeliveryInsertLast(&Delivery,DelKomputer);
        
        startbuild = false;
    }
    else{
        printf("Komponen yang dipasangkan belum sesuai dengan pesanan, build belum dapat diselesaikan");
    }
}

void DELIVER(){
    int NoPelanggan;
    int indeksDel;
    int indeksInvent;
    int NoPesanan;
    DelBuild Delivered;
    Element Invent;

    NoPelanggan = TulisNoPelangganLok(Bangunan,LokasiPlayer);
    if (NoPelanggan!= 0 && IsPemesanAda(Delivery,NoPelanggan)){
        indeksDel = IndeksPemesan(Delivery,NoPelanggan);
        ArrayDeliveyDeleteAt(&Delivery,&Delivered,indeksDel);

        indeksInvent = IndeksInventPesanan(Inventory,Delivered.NoPesanan);
        ArrayInventoryDeleteAt(&Inventory,&Invent,indeksInvent);

        uang += Delivered.Invoice;
    } else {
        printf("Anda belum berada di lokasi pemesan atau tidak ada pesanan yang harus diantar!\n");
    }
}

void SHOP(){
    int pil, pilkom, jumlah, pilawal;
	ArrayKomponen X;
    char NamaLok[100];
    Element Beli;

    TulisBangunanLok(Bangunan,LokasiPlayer,NamaLok);
    if (!IsStrEqual("Shop",NamaLok)){
        printf("Anda belum berada di Shop!");
    } else {
        printf("1. Tampilkan semua komponen\n");
	    printf("2. Tampilkan komponen berdasarkan tipe\n");
	    printf("Masukkan pilihan: ");
	    scanf("%d", &pilawal);
	    if (pilawal == 1){
		    for (int i=0;i<All.Neff;i++)
		    {
			    printf("%d. %s $%d\n" , i+1,All.A[i].Nama,All.A[i].Harga);
		    }
		    printf("Komponen yang ingin dibeli: ");
		    scanf("%d", &pilkom);
		    printf("Masukkan jumlah yang ingin dibeli: ");
		    scanf("%d", &jumlah);
            printf("\n");

            if (1>pilkom && pilkom>All.Neff || jumlah<1){
                goto endshop;
            }

		    if ((All.A[pilkom-1].Harga * jumlah) <= uang){
			    printf("Kompenen berhasil dibeli!");
			    uang = uang - (All.A[pilkom-1].Harga * jumlah);
                Beli = ArrangeElement(All.A[pilkom-1].Nama,jumlah,"Komponen");
                ArrayInventoryInsertLast(&Inventory, Beli);
		    } else {
			    printf("Uang tidak cukup!");
		    }
	    } else if (pilawal==2) {
            printf("Tipe komponen:\n");
            printf("1. Motherboard\n");
            printf("2. CPU\n");
            printf("3. Memory\n");
            printf("4. CPU Cooler\n");
            printf("5. Case\n");
            printf("6. GPU\n");
            printf("7. Storage\n");
            printf("8. PSU\n");
            printf("Masukkan pilihan: ");
            scanf("%d", &pil);
            if (pil == 1){
                X = CopyArrayKomponen(Motherboard);
            } else if (pil == 2) {
                X = CopyArrayKomponen(CPU);
            } else if (pil == 3) {
                X = CopyArrayKomponen(Memory);
            } else if (pil == 4) {
                X = CopyArrayKomponen(CPUCool);
            } else if (pil == 5) {
                X = CopyArrayKomponen(Case);
            } else if (pil == 6) {
                X = CopyArrayKomponen(GPU);
            } else if (pil == 7) {
                X = CopyArrayKomponen(CPUCool);
            } else if (pil == 8) {
                X = CopyArrayKomponen(CPUCool);
            } else {
                goto endshop;
            }
            for (int i=0;i<X.Neff;i++){
                printf("%d. %s $%d\n" , i+1,X.A[i].Nama,X.A[i].Harga);
            }
            printf("Komponen yang ingin dibeli: ");
            scanf("%d", &pilkom);
            printf("Masukkan jumlah yang ingin dibeli: ");
            scanf("%d", &jumlah);
            printf("\n");

            if (1>pilkom && pilkom>All.Neff || jumlah<1){
                goto endshop;
            }

            if ((X.A[pilkom-1].Harga * jumlah) <= uang){
                printf("Kompenen berhasil dibeli!");
			    uang = uang - (X.A[pilkom-1].Harga * jumlah);
                Beli = ArrangeElement(X.A[pilkom-1].Nama,jumlah,"Komponen");
                ArrayInventoryInsertLast(&Inventory, Beli);
            } else {
                printf("Uang tidak cukup!");
            }
        } else {
            goto endshop;
        }
    }
    goto jump;
    endshop:
    printf("Pilihan tidak tersedia!");
    jump:
    printf("\n");
}

int Random(int lower, int upper){
    srand(time(NULL));

    return(rand() % (upper-lower+1)+lower);    
}

void END_DAY(){
    int pemesan;
    int K1, K2, K3, K4, K5, K6, K7, K8, sumK, tagihan;
    int K1H, K2H, K3H, K4H, K5H, K6H, K7H, K8H;
    char DetailOrder[8][200];
    Order PSN; 
    pemesan = Random(1,MaxPelanggan(Bangunan));
        
    K1 = (Random(0,35)%Motherboard.Neff);
    K1H = Motherboard.A[K1].Harga;
    CopyStr(Motherboard.A[K1].Nama,DetailOrder[0]);

    K2 = (Random(21,65)%CPU.Neff);
    K2H = CPU.A[K2].Harga;
    CopyStr(CPU.A[K2].Nama,DetailOrder[1]);

    K3 = (Random(85,150)%Memory.Neff);
    K3H = Memory.A[K3].Harga;
    CopyStr(Memory.A[K3].Nama,DetailOrder[2]);

    K4 = (Random(78, 98)%CPUCool.Neff);
    K4H = CPUCool.A[K4].Harga;
    CopyStr(CPUCool.A[K4].Nama,DetailOrder[3]);

    K5 = (Random(101, 111)%Case.Neff);
    K5H = Case.A[K5].Harga;
    CopyStr(Case.A[K5].Nama,DetailOrder[4]);

    K6 = (Random(212, 232)%GPU.Neff);
    K6H = GPU.A[K6].Harga;
    CopyStr(GPU.A[K6].Nama,DetailOrder[5]);

    K7 = (Random(9, 79)%Storage.Neff);
    K7H = Storage.A[K7].Harga;
    CopyStr(Storage.A[K7].Nama,DetailOrder[6]);

    K8 = (Random(20, 86)%PSU.Neff);
    K8H = PSU.A[K8].Harga;
    CopyStr(PSU.A[K7].Nama,DetailOrder[7]);

    sumK = K1H+K2H+K3H+K4H+K5H+K6H+K7H+K8H;
    tagihan = sumK * 1.5;

    PSN = ArrangeOrder(pemesan,tagihan,DetailOrder);

    PushQueue(&Pesanan, PSN);
}

void MAP(){
    TulisMAP(Map, Absis(LokasiPlayer), Ordinat(LokasiPlayer));
}

void COMMAND()
/* Menginput COMMAND, mengecek commandnya, serta menjalankan commandnya */
{
    boolean exit = false;
    while (!exit){
        printf("ENTER COMMAND: ");
        InputUSER();
        if (IsKataMOVE(CKata)){
            MOVE();
        } else if (IsKataSTATUS(CKata)){
            STATUS();
        } else if (IsKataCHECKORDER(CKata)){
            CHECKORDER();
        } else if (IsKataSTARTBUILD(CKata)){
            STARTBUILD();
        } else if (IsKataFINISHBUILD(CKata)){
            FINISHBUILD();
        } else if (IsKataADDCOMPONENT(CKata)){
            ADDCOMPONENT();
        } else if (IsKataREMOVECOMPONENT(CKata)){
            REMOVECOMPONENT();
        } else if (IsKataSHOP(CKata)){
            SHOP();
        } else if (IsKataDELIVER(CKata)){
            DELIVER();
        } else if (IsKataEND_DAY(CKata)){
            END_DAY();
        } else if (IsKataMAP(CKata)){
            MAP();
        } else if (IsKataEXIT(CKata)){
            exit = true;
        } else if (IsKataSAVE(CKata)){

        } else {
            printf("COMMAND tidak terdefinisi. Silahkan input COMMAND lain!\n");
        }
        printf("\n");
    }
}

int main(){
    /* Variabel */
    int inputmenu;
    All = MakeArrayKomponen();

    /* Program */
    LOGO();
    MENU(&inputmenu);
    if (inputmenu==1){
        //Konfigurasi File Eksternal (Komponen/Item, Map, Objek)
        KonfigurasiItem("./File eksternal/Motherboard.txt", &Motherboard, &All);
        KonfigurasiItem("./File eksternal/CPU.txt", &CPU, &All);
        KonfigurasiItem("./File eksternal/Memory.txt", &Memory, &All);
        KonfigurasiItem("./File eksternal/CPU Cooler.txt", &CPUCool, &All);
        KonfigurasiItem("./File eksternal/Case.txt", &Case, &All);
        KonfigurasiItem("./File eksternal/GPU.txt", &GPU, &All);
        KonfigurasiItem("./File eksternal/Storage.txt", &Storage, &All);
        KonfigurasiItem("./File eksternal/PSU.txt", &PSU, &All);
        KonfigurasiMap("./File eksternal/Map.txt", &Map, &Bangunan, &LokasiPlayer, &GrafBangunan);

        //Inventory Awal
        Inventory = MakeArrayInventory();

        //Order Pesanan Awal
        uang = 10000; // inisialisasi uang
        Pesanan = CreateQueue(99);
        END_DAY();
        Pesanan.OrderNum = 1;

        //Delivery Awal
        Delivery = MakeArrayDelivery();

        //COMMAND
        COMMAND();
    } else {

    }
    
}
