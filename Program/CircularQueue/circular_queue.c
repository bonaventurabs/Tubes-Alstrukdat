#include<stdlib.h>
#include "circular_queue.h"

/* ********* Prototype ********* */
boolean IsEmpty (Queue Q) {
    return Q.HEAD == NIL && Q.TAIL == NIL;
}
boolean IsFull (Queue Q) {
    return Length(Q) == Q.MaxEl;
}
int Length (Queue Q) {
    if (IsEmpty(Q))
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
    Q.Tab = (ElType *) malloc (Max * sizeof(ElType));
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
void Push (Queue * Q, ElType X) {
    if (IsEmpty(*Q)) {
        Q->HEAD = 0;
        Q->TAIL = 0;
    }
    Q->Tab[Q->TAIL] = X;
    Q->TAIL++;
    if (Q->TAIL == Q->MaxEl) {
        Q->TAIL = 0;
    }
}
ElType Pop (Queue * Q) {
    ElType ret = Q->Tab[Q->HEAD];
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
ElType Front (Queue Q) {
    return Q.Tab[Q.HEAD];
}

/* *** Utilitas *** */
Queue CopyQueue (Queue Q) {
    Queue new = CreateQueue(Q.MaxEl);
    if (!IsEmpty(Q)) {
        int tail = Q.HEAD;
        while (Length(new) != Length(Q)) {
            Push(&new, Q.Tab[tail]);
            tail = (tail + 1) % Q.MaxEl;
        }
    }
    return new;
}
