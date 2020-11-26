#include "./boolean/boolean.h"
#include "./point/point.h"
#include "./arrayDinamik/listDinamik.h"
#include "./mesinkarakter/mesinkar.h"
#include "./mesinkarakter/mesinkata.h"
#include "./CircularQueue/circular_queue.h"
#include "./Stack/stack.h"
#include "./matriks/matriks.h"
#include "./graf/graf.h"

#include <stdio.h>
#include <stdlib.h>

void COMMAND()
/* Menginput COMMAND, mengecek commandnya, serta menjalankan commandnya */
{
    boolean exit = false;
    while (!exit){
        printf("ENTER COMMAND: ");
        InputUSER();
        if (IsKataMOVE(CKata)){

        } else if (IsKataSTATUS(CKata)){

        } else if (IsKataCHECKORDER(CKata)){

        } else if (IsKataSTARTBUILD(CKata)){

        } else if (IsKataFINISHBUILD(CKata)){

        } else if (IsKataADDCOMPONENT(CKata)){

        } else if (IsKataREMOVECOMPONENT(CKata)){

        } else if (IsKataSHOP(CKata)){

        } else if (IsKataDELIVER(CKata)){

        } else if (IsKataEND_DAY(CKata)){

        } else if (IsKataMAP(CKata)){

        } else if (IsKataEXIT(CKata)){
            exit = true;
        } else if (IsKataSAVE(CKata)){

        } else {
        
        }
        /*IsKataMOVE(CKata);
        IsKataSTATUS(CKata);
        IsKataCHECKORDER(CKata);
        IsKataSTARTBUILD(CKata);
        IsKataFINISHBUILD(CKata);
        IsKataADDCOMPONENT(CKata);
        IsKataREMOVECOMPONENT(CKata);
        IsKataSHOP(CKata);
        IsKataDELIVER(CKata);
        IsKataEND_DAY(CKata);
        IsKataMAP(CKata);
        IsKataEXIT(CKata);
        IsKataSAVE(CKata);*/
    }
}

int main(){
    printf("\n");
	printf("                               ____    _    __  _  _______  ____\n");
	printf("                              |  __|  / \\  |  \\| ||__   __||    |\n");
	printf("                              |____  / _ \\ | |\\  |   | |   | || |\n");
	printf("                               |___|/_/ \\_\\|_| \\_|   |_|   |____|\n");
	printf("                              --T.Y.C.O.O.N--  \n");
	printf("\n");

    printf("                                    Selamat datang di game\n");
	printf("                                         SANTO TYCOON\n");
    printf("                                         1. NEW GAME\n");
    printf("                                         2. LOAD GAME\n");
    COMMAND();
}