#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "point.c"
#include "ListPoint.h"
#include "ListPoint.c"

int main(){
    ListObjek L;
    MakeListObjek(&L);
    printf("%d\n",NObjek(L));
    int j = 1;

    InsertListObjek(&L,'C',2,1);
    printf("%d\n",NObjek(L));
    printf("%c\n",Simbol(L,1));
    printf("%d\n",Absis(Point(L,1)));
    printf("%d\n",Ordinat(Point(L,1)));
    printf("\n");
    POINT P;
    P = MakePOINT(2,1);
    printf("%d\n",Absis(P));
    printf("%d\n",Ordinat(P));
    printf("\n");
    char coba[100];
    TulisBangunanLok(L,P,coba);
    printf("Anda ada di %s\n",coba);
    printf("%d\n",SearchIndeks(L,P));
    InsertListObjek(&L,'S',3,2);
    TulisBangunanInd(L,2,coba);
    printf("%d. %s\n",j,coba);


}