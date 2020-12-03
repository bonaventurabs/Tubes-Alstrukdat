#include "mesinkar.h"
#include "mesinkata.h"
#include "mesinkar.c"
#include "mesinkata.c"

#include <stdio.h>
#include <stdlib.h>

int main(){
    STARTKATA("test2.txt");
    int ElmtM;
    for (int i = 1; i <= 9; i++){
        for (int j = 1; j <= 9; j++){
            BacaAngka(&ElmtM);
            printf("%d ",ElmtM);

        }
        printf("\n");
    }
    return 0;
}