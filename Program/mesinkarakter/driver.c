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
    int angka,angka2;
    char B;
    UnionKata(kalimat);
    printf("%s\n",kalimat);
    BacaAngka(&angka);
    printf("%d\n",angka);
    UnionKata(kalimat);
    printf("%s\n",kalimat);
    BacaAngka(&angka);
    printf("%d\n",angka);
    BacaKarakter(&B);
    printf("%c\n",B);
    UnionKata(kalimat);
    printf("%s\n",kalimat);
    BacaAngka(&angka2);
    printf("%d\n",angka2);


    printf("%d\n",EndKata);
    printf("%c\n",CC);

    char* str;
    str = kalimat;
    printf("%s\n",str);
    return 0;
}