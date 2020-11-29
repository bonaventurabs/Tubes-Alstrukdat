#include <stdio.h>
#include <stdlib.h>

#include "matriks.h"


/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M) 
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
}


/* *** Selektor *** */
//#define NBrsEff(M) (M).NBrsEff
//#define NKolEff(M) (M).NKolEff
//#define Elmt(M,i,j) (M).Mem[(i)][(j)]


/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
    return (i>=BrsMin && i<=BrsMax && j>=KolMin && j<=KolMax);
    
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
    return NBrsEff(M)-1;
}
indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
    return NKolEff(M)-1;
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
    return (i>=GetFirstIdxBrs(M) && i<=GetLastIdxBrs(M) && j>=GetFirstIdxKol(M) && j<=GetLastIdxKol(M));
}
ElType GetElmtDiagonal (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
    return Elmt(M,i,i);
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
    MakeMATRIKS(NBrsEff(MIn),NKolEff(MIn),MHsl);
    for (indeks i = GetFirstIdxBrs(MIn); i <= GetLastIdxBrs(MIn); i++){
        for (indeks j = GetFirstIdxKol(MIn); i <= GetLastIdxKol(MIn); j++){
            Elmt(*MHsl,i,j) = Elmt(MIn,i,j);
        }
        
    }
}

/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MATRIKS * M, int NB, int NK)
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
{
    MakeMATRIKS(NB,NK,M);
    for (indeks i = 0; i < NB; i++){
        for (indeks j = 0; j < NK; j++){
			scanf("%d",&(Elmt(*M,i,j)));
        }
    }
}
void TulisMATRIKS (MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
    for (indeks i = GetFirstIdxBrs(M); i <= GetLastIdxBrs(M); i++){
        for (indeks j = GetFirstIdxKol(M); j < GetLastIdxKol(M); j++){
            printf("%d ", Elmt(M,i,j)); 
        }
        printf("%d\n", Elmt(M,i,GetLastIdxKol(M)));
    }
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */                                  
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */ 
{
    MATRIKS Mp;
    MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&Mp);
    for (indeks i = GetFirstIdxBrs(Mp); i <= GetLastIdxBrs(Mp); i++){
        for (indeks j = GetFirstIdxKol(Mp); j <= GetLastIdxKol(Mp); j++){ 
            Elmt(Mp,i,j) = Elmt(M1,i,j) + Elmt(M2,i,j);       
        }
    }
    return Mp;
}
MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */
{
    MATRIKS Mm;
    MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&Mm);
    for (indeks i = GetFirstIdxBrs(Mm); i <= GetLastIdxBrs(Mm); i++){
        for (indeks j = GetFirstIdxKol(Mm); j <= GetLastIdxKol(Mm); j++){
            Elmt(Mm,i,j) = Elmt(M1,i,j) - Elmt(M2,i,j);        
        }
    }
    return Mm;
} 
MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
{
    MATRIKS Mt;
    MakeMATRIKS(NBrsEff(M1),NKolEff(M2),&Mt);
    for (indeks i = GetFirstIdxBrs(Mt); i <= GetLastIdxBrs(Mt); i++){
        for (indeks j = GetFirstIdxKol(Mt); j <= GetLastIdxKol(Mt); j++){
            for (indeks k = GetFirstIdxKol(M1); k <= GetLastIdxKol(M1); k++){
                Elmt(Mt,i,j) += Elmt(M1,i,k)*Elmt(M2,k,j); 
            }       
        }
    }
    return Mt;
}
MATRIKS KaliKons (MATRIKS M, ElType X)
/* Mengirim hasil perkalian setiap elemen M dengan X */
{
    MATRIKS Mt;
    MakeMATRIKS(NBrsEff(M),NKolEff(M),&Mt);
    for (indeks i = GetFirstIdxBrs(Mt); i <= GetLastIdxBrs(Mt); i++){
        for (indeks j = GetFirstIdxKol(Mt); j <= GetLastIdxKol(Mt); j++){
            Elmt(Mt,i,j) = X*Elmt(M,i,j);
        }
    }
    return Mt;
}
void PKaliKons (MATRIKS * M, ElType K)
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
{
    for (indeks i = GetFirstIdxBrs(*M); i <= GetLastIdxBrs(*M); i++){
        for (indeks j = GetFirstIdxKol(*M); j <= GetLastIdxKol(*M); j++){
            Elmt(*M,i,j) = K*Elmt(*M,i,j);
        }
    }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQMATRIKS (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
{
    boolean equal;
    indeks i,j;

    if (EQSize(M1,M2)){
        equal = true;
        i = GetFirstIdxBrs(M1);
        while (equal && i<=GetLastIdxBrs(M1)){
            j = GetFirstIdxKol(M2);
            while (equal && j<=GetLastIdxKol(M2)){
                if (Elmt(M1,i,j)!=Elmt(M2,i,j)){
                    equal = false;
                } else {
                    j++;
                }
            }
            i++;
        }
        return equal;
    } else {
        return false;
    }
}
boolean NEQMATRIKS (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
    return !EQ(M1,M2);
}

boolean EQSizeMATRIKS (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu NBrsEff(M1) = NBrsEff (M2) dan NKolEff (M1) = NKolEff (M2) */
{
    return NBrsEff(M1) == NBrsEff(M2) && NKolEff(M1) == NKolEff(M2);
}

/* ********** Operasi lain ********** */
int NBElmtMATRIKS (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
    return NBrsEff(M)*NKolEff(M);
}

/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M)
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
{
    return NBrsEff(M)==NKolEff(M);
}
boolean IsSimetri (MATRIKS M)
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M) 
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
{
    boolean simetri;
    indeks i,j;

    if (IsBujurSangkar(M)){
        simetri = true;
        i = GetFirstIdxBrs(M);
        while (simetri && i<=GetLastIdxBrs(M)){
            j = GetFirstIdxKol(M);
            while (simetri && j<=GetLastIdxKol(M)){
                if (Elmt(M,i,j)!=Elmt(M,j,i)){
                    simetri = false;
                } else {
                    j++;
                }
            }
            i++;
        }
        return simetri;
    } else {
        return false;
    }
}
boolean IsSatuan (MATRIKS M)
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan 
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
{
    boolean satuan;
    indeks i,j;

    if (IsBujurSangkar(M)){
        satuan = true;
        i = GetFirstIdxBrs(M);
        while (satuan && i<=GetLastIdxBrs(M)){
            j = GetFirstIdxKol(M);
            while (satuan && j<=GetLastIdxKol(M)){
                if (i==j){
                    if (Elmt(M,i,j)!=1){
                        satuan = false;
                    }
                } else {
                    if (Elmt(M,i,j)!=0){
                        satuan = false;
                    }
                }
                j++;
            }
            i++;
        }
    }
} 
boolean IsSparse (MATRIKS M)
/* Mengirimkan true jika M adalah matriks sparse: matriks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */ 
{
    int count = 0;
    for (indeks i = GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++){
        for (indeks j = GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++){
            if (Elmt(M,i,j)!=0){
                count++;
            }
        }
    }
    return (0.05*NBElmt(M)>=count);
}
MATRIKS Inverse1 (MATRIKS M)
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
{
    MATRIKS MIn;
    MakeMATRIKS(NBrsEff(M),NKolEff(M),&MIn);
    for (indeks i = GetFirstIdxBrs(M); i<=GetLastIdxKol(M); i++){
        for (indeks j = GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++){
            Elmt(MIn,i,j) = (-1)*(Elmt(M,i,j));
        }
    }
    return MIn;
}
void Transpose (MATRIKS * M)
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
{
    ElType temp;
    for (indeks i=GetFirstIdxBrs(*M); i<=GetLastIdxBrs(*M); i++){
        for (indeks j=i; j<=GetLastIdxKol(*M); j++){
            temp = Elmt(*M,j,i);
            Elmt(*M,j,i) = Elmt(*M,i,j);
            Elmt(*M,i,j) = temp;
        }
    }
}
float RataBrs (MATRIKS M, indeks i)
/* Menghasilkan rata-rata dari elemen pada baris ke-i */
/* Prekondisi: i adalah indeks baris efektif dari M */
{
    ElType sum=0;
    for (indeks j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++){
        sum += Elmt(M,i,j);
    }
    return (float)sum/NKolEff(M);
}
float RataKol (MATRIKS M, indeks j)
/* Menghasilkan rata-rata dari elemen pada kolom ke-j */
/* Prekondisi: j adalah indeks kolom efektif dari M */
{
    ElType sum=0;
    for (indeks i=GetFirstIdxBrs(M); i<=GetLastIdxKol(M); i++){
        sum += Elmt(M,i,j);
    }
    return (float)sum/NBrsEff(M);
}
void MaxMinBrs (MATRIKS M, indeks i, ElType * max, ElType * min)
/* I.S. i adalah indeks baris efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada baris i dari M
           min berisi elemen minimum pada baris i dari M */
{
    *max = Elmt(M,i,0);
    *min = Elmt(M,i,0);
    for (indeks j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++){
        if (Elmt(M,i,j)>*max){
            *max = Elmt(M,i,j);
        }
        if (Elmt(M,i,j)<*min){
            *min = Elmt(M,i,j);
        }
    }
}
void MaxMinKol (MATRIKS M, indeks j, ElType * max, ElType * min)
/* I.S. j adalah indeks kolom efektif dari M, M terdefinisi */
/* F.S. max berisi elemen maksimum pada kolom j dari M
           min berisi elemen minimum pada kolom j dari M */
{
    *max = Elmt(M,0,j);
    *min = Elmt(M,0,j);
    for (indeks i=GetFirstIdxBrs(M); j<=GetLastIdxBrs(M); i++){
        if (Elmt(M,i,j)>*max){
            *max = Elmt(M,i,j);
        }
        if (Elmt(M,i,j)<*min){
            *min = Elmt(M,i,j);
        }
    }
}
int CountXBrs (MATRIKS M, indeks i, ElType X)
/* Menghasilkan banyaknya kemunculan X pada baris i dari M */
{
    int count = 0;
    for (indeks j=GetFirstIdxKol(M); j<GetLastIdxKol(M); j++){
        if (Elmt(M,i,j)==X){
            count++;
        }
    }
    return count;
}
int CountXKol (MATRIKS M, indeks j, ElType X)
/* Menghasilkan banyaknya kemunculan X pada kolom j dari M */
{
    int count = 0;
    for (indeks i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++){
        if (Elmt(M,i,j)==X){
            count++;
        }
    }
    return count;
}