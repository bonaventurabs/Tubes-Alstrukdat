lse if (IsKataREMOVECOMPONENT(CKata)){
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
