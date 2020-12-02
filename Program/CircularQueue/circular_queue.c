#include<stdlib.h>
#include "circular_queue.h"

/* ********* Prototype ********* */
boolean IsQueueEmpty (Queue Q) {
    return Q.HEAD == NIL && Q.TAIL == NIL;
}
boolean IsQueueFull (Queue Q) {
    return LengthQueue(Q) == Q.MaxEl;
}
int LengthQueue (Queue Q) {
    if (IsQueueEmpty(Q))
        return 0;
    else if (Q.HEAD >= Q.TAIL)
        return Q.MaxEl + Q.TAIL - Q.HEAD;
    else
        return Q.TAIL - Q.HEAD;
}
int MaxLength (Queue Q) {
    return Q.MaxEl;
}

/* *** Kreator *** */
Queue CreateQueue (int Max) {
    Queue Q;
    Q.Tab = (Order *) malloc (Max * sizeof(Order));
    Q.HEAD = NIL;
    Q.TAIL = NIL;
    Q.MaxEl = Max;
    return Q;
}

/* *** Destruktor *** */
void DeleteQueue (Queue * Q) {
    Q->MaxEl = 0;
    free(Q->Tab);
}

/* *** Primitif Add/Delete *** */
void PushQueue (Queue * Q, Order X) {
    if (IsQueueEmpty(*Q)) {
        Q->HEAD = 0;
        Q->TAIL = 0;
    }
    Q->Tab[Q->TAIL] = X;
    Q->TAIL++;
    if (Q->TAIL == Q->MaxEl) {
        Q->TAIL = 0;
    }
}
Order PopQueue (Queue * Q) {
    Order ret = Q->Tab[Q->HEAD];
    Q->HEAD++;
    if (Q->HEAD == Q->MaxEl) {
        Q->HEAD = 0;
    }
    if (Q->HEAD == Q->TAIL) {
        Q->HEAD = NIL;
        Q->TAIL = NIL;
    }
    return ret;
}
Order Front (Queue Q) {
    return Q.Tab[Q.HEAD];
}

/* *** Utilitas *** */
Queue CopyQueue (Queue Q) {
    Queue new = CreateQueue(Q.MaxEl);
    if (!IsQueueEmpty(Q)) {
        int tail = Q.HEAD;
        while (LengthQueue(new) != LengthQueue(Q)) {
            PushQueue(&new, Q.Tab[tail]);
            tail = (tail + 1) % Q.MaxEl;
        }
    }
    return new;
}
