#include <stdio.h>
#include <stdlib.h>
#include "ListPoint.h"
#include "ListPoint.c"

int main(){
    ListObjek L;
    MakeListObjek(&L);
    printf("%d\n",NObjek(L));
    InsertListObjek(&L,'C',2,1);
    printf("%d\n",NObjek(L));
    printf("%c\n",Simbol(L,0));
    printf("%d\n",Absis(Point(L,0)));
    printf("%d\n",Ordinat(Point(L,0)));
}