#include <stdio.h>
#include <stdlib.h>
#include "circular_queue.h"
#include "circular_queue.c"

int main(){
    Queue P = CreateQueue(99);
    char or[8][200] = {
        "cpu",
        "mikro",
        "jerry",
        "jerry",
        "cekq",
        "jerry",
        "tutu",
        "jerry"
        };
    Order Det;
    Det = ArrangeOrder(1,1000,or);
    printf("%d\n",Det.Pemesan);
    printf("%s\n",Det.Detail[4]);

    PushQueue(&P,Det);
    printf("%d. %s\n",1 , P.Tab[P.HEAD].Detail[0]);
}