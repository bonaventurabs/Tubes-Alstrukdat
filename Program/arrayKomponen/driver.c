#include <stdio.h>
#include <stdio.h>
#include "arrayKomponen.h"
#include "arrayKomponen.c"

int main(){
    char Nama[100] = "Intel";
    char Kategori[20] = "CPU";
    int Harga = 20;
    Item P,A;

    char Nama2[100] = "AMD";

    P = ArrangeItem(Nama,Harga,Kategori);
    printf("%s\n",P.Nama);
    

    A = ArrangeItem(Nama2,Harga,Kategori);
    printf("%s\n",A.Nama);

    return 0;
}