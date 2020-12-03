#include <stdio.h>
#include <stdio.h>
#include "arrayKomponen.h"
#include "arrayKomponen.c"

int main(){
    char *Nama;
    Nama = "Intel";
    char *Kategori2 = "CPU";
    char *Kategori1 = "Memory";
    int Harga = 20;
    Item P,A;

    char Nama2[100] = "AMD";

    P = ArrangeItem(Nama,Harga,Kategori1);
    printf("%s\n",P.Nama);
    printf("%s\n",P.Kategori);
    

    A = ArrangeItem(Nama2,Harga,Kategori2);
    printf("%s\n",A.Nama);
    printf("%s\n",A.Kategori);

    return 0;
}