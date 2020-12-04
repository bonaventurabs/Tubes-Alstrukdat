#include "mesinkar.h"
#include "mesinkata.h"
#include "mesinkar.c"
#include "mesinkata.c"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Random(int lower, int upper){
    srand(time(NULL));

    return(rand() % (upper-lower+1)+lower);    
}


int main(){
    char A[8][200];

    char B[10]="abon";
    char C[20]="cai";

    CopyStr(B,A[0]);
    CopyStr(C,A[1]);

    printf("%s\n",A[0]);
    printf("%s\n",A[1]);
    printf("%d\n",Random(10,100));
    
}
