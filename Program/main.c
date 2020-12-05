#include "./boolean/boolean.h"
#include "./point/point.h"
#include "./array_statis(listofpoint)/ListPoint.h"
#include "./array_dinamis(komponen)/arrayKomponen.h"
#include "./array_dinamis(inventory)/arrayInventory.h"
#include "./array_dinamis(delivery)/arrayDelivery.h"
#include "./mesinkarakter-kata/mesinkar.h"
#include "./mesinkarakter-kata/mesinkata.h"
#include "./queue/circular_queue.h"
#include "./stack/stack.h"
#include "./matriks/matriks.h"
#include "./graf/graf.h"

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

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void LOGO(){
    printf("\n");
    printf("\x1b[1m"); //bold
	printf("                              ____    _    __  _  _______  ____\n");
	printf("                             |  __|  / \\  |  \\| ||__   __||    |\n");
	printf("                             |____  / _ \\ | |\\  |   | |   | || |\n");
	printf("                              |___|/_/ \\_\\|_| \\_|   |_|   |____|\n");
	printf("                                                 \x1b[4m--T.Y.C.O.O.N--\n");
    printf("\x1b[0m");
	printf("\n");
}

void MENU(int *inputmenu){
    printf("                                    Selamat datang di game\n");
    printf("                                         SANTO TYCOON\n");
    printf("                                         1. NEW GAME\n");
    printf("                                         2. LOAD GAME\n");
    printf("                                         > ");
    printf("\x1b[1m"); //bold
    InputAngka(inputmenu);
    printf("\x1b[0m");
    while (*inputmenu!=1 && *inputmenu!=2){
        printf("                    Input tidak terdefinisi, silahkan masukan angka menu\n");
        printf("                                         > ");
        printf("\x1b[1m"); //bold
        InputAngka(inputmenu);
        printf("\x1b[0m");
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

void KonfigurasiLoadGame(char *path){
    int bool;

    int NInventory;
    char InventNama[200];
    int InventJumlah;
    char InventJenis[20];
    Element InventEl;

    int OrNumP; int MaxQ;
    int NPesanan;
    int QHead,QTail;
    int QPemesan;
    int QNilai;
    char QDetail[8][200];
    Order QOrder;

    int NBuild;
    char BuildNama[200];
    infotype BuildInfo;

    int NDelivery;
    int DelNoPesanan;
    int DelPemesan;
    int DelInvoice;
    DelBuild Deliver;

    STARTKATA(path);
    //uang
    BacaAngka(&uang);
    //lokasi player
    BacaAngka(&Absis(LokasiPlayer)); BacaAngka(&Ordinat(LokasiPlayer));
    //startbuild
    BacaAngka(&bool);
    if (bool==1){
        startbuild = true;
    } else {
        startbuild = false;
    }
    //inventory (arrayinventory)
    BacaAngka(&NInventory);
    Inventory = MakeArrayInventory();
    if (NInventory!=0){
        for (int i = 0; i < NInventory; i++)
        {
            UnionKata(InventNama);
            BacaAngka(&InventJumlah);
            UnionKata(InventJenis);
            InventEl = ArrangeElement(InventNama,InventJumlah,InventJenis);
            ArrayInventoryInsertLast(&Inventory,InventEl);
        }  
    }
    //pesanan (queue)
    BacaAngka(&OrNumP); BacaAngka(&MaxQ);
    BacaAngka(&NPesanan);
    Pesanan = CreateQueue(MaxQ);
    Pesanan.OrderNum = OrNumP;
    if (NPesanan!=0){
        for (int i = 0; i < NPesanan; i++)
        {
            BacaAngka(&QPemesan);
            BacaAngka(&QNilai);
            for (int j = 0; j < 8; ++j)
            {
                UnionKata(QDetail[j]);
            }
            QOrder = ArrangeOrder(QPemesan,QNilai,QDetail);
            PushQueue(&Pesanan,QOrder);
        }
    }
    //build (stack)
    BacaAngka(&NBuild);
    CreateEmptyStack(&Build);
    if(NBuild!=0){
        for (int i = 0; i < NBuild; i++)
        {
            UnionKata(BuildNama);
            BuildInfo = Arrangeinfotype(BuildNama);
            Push(&Build,BuildInfo);
        }
    }
    //delivery (arraydelivey)
    BacaAngka(&NDelivery);
    Delivery = MakeArrayDelivery();
    if (NDelivery!=0){
        for (int i = 0; i < NDelivery; i++)
        {
            BacaAngka(&DelNoPesanan);
            BacaAngka(&DelPemesan);
            BacaAngka(&DelInvoice);
            Deliver = ArrangeDelBuild(DelNoPesanan,DelPemesan,DelInvoice);
            ArrayDeliveryInsertLast(&Delivery,Deliver);
        }
    }
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
    printf("\x1b[1m"); //bold
    scanf("%d", &tujuan);
    printf("\x1b[0m");

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
    if (startbuild){
        printf("Selesaikan pesanan %d untuk Pelanggan %d terlebih dulu!\n",Pesanan.OrderNum,Pesanan.Tab[Pesanan.HEAD].Pemesan);
    } else {
        startbuild = true;
        CreateEmptyStack(&Build);
        printf("Kamu telah memulai pesanan %d untuk Pelanggan %d.\n", Pesanan.OrderNum, Pesanan.Tab[Pesanan.HEAD].Pemesan); 
    }
}

void ADDCOMPONENT(){ 
    int x;
    infotype KompBuild;
    char NamaLok[100];

    TulisBangunanLok(Bangunan,LokasiPlayer,NamaLok);
    if (!IsStrEqual("Base",NamaLok) && !startbuild){
        printf("Anda belum berada di Base dan memulai Build!\n");
    } else if (!IsStrEqual("Base",NamaLok) && startbuild){
        printf("Anda belum berada di Base\n");
    } else if (IsStrEqual("Base",NamaLok) && !startbuild){
        printf("Anda belum memulai Build\n");
    } else {
        printf("Komponen yang telah terpasang:\n");
        if (IsStackEmpty(Build)){
            printf("\n");
        } else {
            for(int i=0;i<TOP(Build);i++){
            printf("%d. %s\n", (i+1), Build.T[i].NamaKomp);
            }
        }
        printf("Komponen yang tersedia:\n");
        if (CountKomponen(Inventory)==0){
            printf("\n");
            printf("Inventory komponen Anda kosong!\n");
        } else {
            int k = 1;
            for(int i=0;i<Inventory.Neff;i++){
                if (IsStrEqual("Komponen",Inventory.A[i].Jenis)){
                    printf("%d. %s\n", k, Inventory.A[i].Nama);
                    k++;
                }
            }

            printf("Komponen yang ingin dipasang: ");
            printf("\x1b[1m"); //bold
            scanf("%d", &x);
            printf("\x1b[0m");
            if (x>=1 && x <= Inventory.Neff){
                if (!IsStackFull(Build)){
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
                } else {
                    printf("Komponen Build Anda sudah penuh!\n");
                } 
            }
            else{
                printf("Komponen tidak tersedia!\n");
            }
        } 
    }  
}

void REMOVECOMPONENT(){
    infotype infocopot;
    char copot[200];
    Element simpan;

    if (IsStackEmpty(Build)){
        printf("Belum ada komponen yang terpasang!\n");
    } else {
        Pop(&Build,&infocopot);
        CopyStr(infocopot.NamaKomp,copot);
        simpan = ArrangeElement(copot,1,"Komponen");
        InsertInventory(&Inventory,simpan);
        printf("Komponen %s berhasil dicopot!\n",copot);
    }
}

void FINISHBUILD(){
    boolean benar=true;
    int i = 0;

    if (IsStackEmpty(Build)){
        printf("Belum ada komponen yang terpasang!\n");
    } else {
        while (benar && i < MaxElS){
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
            printf("Komponen yang dipasangkan belum sesuai dengan pesanan, build belum dapat diselesaikan!\n");
        }
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
        printf("Pesanan #%d berhasil diantarkan kepada pelanggan %d!",Delivered.NoPesanan,Delivered.Pemesan);
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
        printf("\x1b[1m"); //bold
	    scanf("%d", &pilawal);
         printf("\x1b[0m");
	    if (pilawal == 1){
		    for (int i=0;i<All.Neff;i++)
		    {
			    printf("%d. %s $%d\n" , i+1,All.A[i].Nama,All.A[i].Harga);
		    }
		    printf("Komponen yang ingin dibeli: ");
            printf("\x1b[1m"); //bold
		    scanf("%d", &pilkom);
            printf("\x1b[0m");
		    printf("Masukkan jumlah yang ingin dibeli: ");
            printf("\x1b[1m"); //bold
		    scanf("%d", &jumlah);
            printf("\x1b[0m");
            printf("\n");

            if (1>pilkom && pilkom>All.Neff || jumlah<1){
                goto endshop;
            }

		    if ((All.A[pilkom-1].Harga * jumlah) <= uang){
			    printf("Kompenen berhasil dibeli!");
			    uang = uang - (All.A[pilkom-1].Harga * jumlah);
                Beli = ArrangeElement(All.A[pilkom-1].Nama,jumlah,"Komponen");
                InsertInventory(&Inventory,Beli);
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
            printf("\x1b[1m"); //bold
            scanf("%d", &pil);
            printf("\x1b[0m");
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
                X = CopyArrayKomponen(Storage);
            } else if (pil == 8) {
                X = CopyArrayKomponen(PSU);
            } else {
                goto endshop;
            }
            for (int i=0;i<X.Neff;i++){
                printf("%d. %s $%d\n" , i+1,X.A[i].Nama,X.A[i].Harga);
            }
            printf("Komponen yang ingin dibeli: ");
            printf("\x1b[1m"); //bold
            scanf("%d", &pilkom);
            printf("\x1b[0m");
            printf("Masukkan jumlah yang ingin dibeli: ");
            printf("\x1b[1m"); //bold
            scanf("%d", &jumlah);
            printf("\x1b[0m");

            if (1>pilkom && pilkom>All.Neff || jumlah<1){
                goto endshop;
            }

            if ((X.A[pilkom-1].Harga * jumlah) <= uang){
                printf("Kompenen berhasil dibeli!");
			    uang = uang - (X.A[pilkom-1].Harga * jumlah);
                Beli = ArrangeElement(X.A[pilkom-1].Nama,jumlah,"Komponen");
                InsertInventory(&Inventory,Beli);
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

void SAVE(){
    char str[200];
    printf("Lokasi save file: ");
    printf("\x1b[1m"); //bold
    scanf("%s",str);
    printf("\x1b[0m");

    STARTWRITE(str);
    //uang
    WRITEINT(uang); WRITENEWLINE();
    //lokasi player
    WRITEINT(Absis(LokasiPlayer)); WRITEBLANK(); WRITEINT(Ordinat(LokasiPlayer)); WRITENEWLINE();
    //starbuild
    if (startbuild){
        WRITEINT(1); WRITENEWLINE();
    } else {
        WRITEINT(0); WRITENEWLINE();
    }
    //inventory (arrayinventory)
    WRITEINT(Inventory.Neff); WRITENEWLINE();
    for (int i = 0; i < Inventory.Neff; i++)
    {
        WRITESTRING(Inventory.A[i].Nama);
        WRITEDELIMITER();
        WRITEINT(Inventory.A[i].Jumlah);
        WRITEDELIMITER();
        WRITESTRING(Inventory.A[i].Jenis);
        WRITEDELIMITER();
        WRITENEWLINE();
    }

    //pesanan (queue)
    WRITEINT(Pesanan.OrderNum); WRITEBLANK(); WRITEINT(Pesanan.MaxEl); WRITENEWLINE();
    WRITEINT(LengthQueue(Pesanan)); WRITENEWLINE();
    for (int i = 0; i < LengthQueue(Pesanan); i++)
    {
        WRITEINT(Pesanan.Tab[i].Pemesan); 
        WRITEBLANK();
        WRITEINT(Pesanan.Tab[i].Nilai);
        WRITENEWLINE();
        for (int j = 0; j < 8; ++j)
        {
            WRITESTRING(Pesanan.Tab[i].Detail[j]);
            WRITEDELIMITER();
            WRITENEWLINE();
        }
    }

    //build (stack)
    WRITEINT(TOP(Build)); WRITENEWLINE();
    for (int i = 0; i < TOP(Build); i++)
    {
        WRITESTRING(Build.T[i].NamaKomp);
        WRITEDELIMITER();
        WRITENEWLINE();
    }
    
    //delivery (arraydelivey)
    WRITEINT(Delivery.Neff); WRITENEWLINE();
    for (int i = 0; i < Delivery.Neff; i++)
    {
        WRITEINT(Delivery.A[i].NoPesanan);
        WRITEBLANK();
        WRITEINT(Delivery.A[i].Pemesan);
        WRITEBLANK();
        WRITEINT(Delivery.A[i].Invoice);
        WRITENEWLINE();
    }

    WRITEMARK();
    FINISHWRITE();
    printf("Game berhasil di save!\n");
}

void COMMAND()
/* Menginput COMMAND, mengecek commandnya, serta menjalankan commandnya */
{
    boolean exit = false;
    while (!exit){
        printf("ENTER COMMAND: ");
        printf("\x1b[1m"); //bold
        InputUSER();
        printf("\x1b[0m");
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
            SAVE();
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
    clear();
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
        uang = 100000; // inisialisasi uang
        Pesanan = CreateQueue(99);
        END_DAY();
        Pesanan.OrderNum = 1;

        //Delivery Awal
        Delivery = MakeArrayDelivery();

        //COMMAND
        clear();
        LOGO();
        COMMAND();
    } else {
        char directory[200];
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

        //Load file
        printf("Directory file: ");
        printf("\x1b[1m"); //bold
        scanf("%s",directory);
        printf("\x1b[0m");

        if (cfileexists(directory)){
            KonfigurasiLoadGame(directory);
            printf("File berhasil diload!\n");
            printf("\n");
            //COMMAND
            COMMAND();
        } else {
            printf("File gagal diload!\n");
            printf("\n");
        }
    }
}