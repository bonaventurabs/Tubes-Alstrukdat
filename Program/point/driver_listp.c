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
    char *coba;
    TulisBangunan(L,P,&coba);
    printf("%s\n",coba);
}