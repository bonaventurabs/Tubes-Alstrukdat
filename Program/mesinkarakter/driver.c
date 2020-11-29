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
    int angka;
    BacaAngka(&angka);
    printf("%d\n",angka);

    return 0;
}