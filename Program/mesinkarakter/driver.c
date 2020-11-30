#include "mesinkar.h"
#include "mesinkata.h"
#include "mesinkar.c"
#include "mesinkata.c"

#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("ENTER COMMAND: ");
    InputUSER();
    printf("%d\n", IsKataMOVE(CKata));

    STARTKATA("test.txt");
    char kalimat[100];
    char kal[100];
    char kall[100];
    int angka;
    UnionKata(kalimat);
    BacaAngka(&angka);
    UnionKata(kal);
    UnionKata(kall);

    printf("%s\n",kalimat);
    printf("%d\n",angka);
    printf("%s\n",kal);
    printf("%s\n",kall);

    printf("%d\n",EndKata);
    printf("%c\n",CC);

    return 0;
}