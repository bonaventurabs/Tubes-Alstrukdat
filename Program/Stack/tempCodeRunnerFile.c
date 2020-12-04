infotype Arrangeinfotype(char Komponen[]){
    infotype Komp;
    int i;

    for (i = 0; Komponen[i]!='\0'; ++i){
        Komp.NamaKomp[i] = Komponen[i];
    }
    Komponen[i] = '\0';
    return Komp;
}