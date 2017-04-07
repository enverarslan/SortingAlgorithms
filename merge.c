#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergeSort(int *, int, int);
void merge(int *, int, int, int);

enum Tur { sirali = 1, ters_sirali = 2, rastgele = 3 };

// Dizi boyutu global.
int boyut = 100000;
//  Ters sıralı dizi olacak.
enum Tur tur = ters_sirali;

// Recursion olduğu için değişim ve karşılaştırmaları global tut.
unsigned long long int toplam_degisim=0, toplam_karsilastirma = 0;

/**
 * Adresi verilen dizinin elemanlarını ekrana bas.
 * @param pointer dizi
 * @return void
 */
void diziYaz(int * dizi){

    int l;

    for( l = 0; l < boyut; l++){
        printf("%d,", dizi[l]);
    }

}

/**
 * Belirtilen boyut ve türde dizi oluştur ve adresini döndür.
 * @param int boyut
 * @param enum Tur tip
 * @return  pointer
 */
int * diziOlustur(int boyut, enum Tur tip){

    int *dizi;
    int i;

    dizi = (int *) malloc( sizeof(int) * boyut );

    if(tip  == 1){

        for( i=0; i < boyut; i++ ){
            dizi[i] = i;
        }

    }else if(tip == 2){

        for( i=0; i < boyut; i++ ){
            dizi[i] = boyut -i -1;
        }

    }else{

        srand(time(NULL)); // rastgele sayı üretmek için besleme.

        for(i=0; i < boyut; i++ ){
            dizi[i] = (rand() % boyut);
        }

    }

    return dizi;
}

void mergeSort(int * dizi, int start, int end){

    if(start < end){
        int middle = start + (end-start) / 2;
        mergeSort(dizi, start, middle);
        mergeSort(dizi, middle+1, end);
        merge(dizi, start, middle, end);
    }
}

void merge(int * dizi, int start, int middle, int end)
{
    int i, j, k;
    int sub1 = middle - start + 1;
    int sub2 =  end - middle;

    // Oluşturacağımız alt dizileri stack'ta değil heap'ta tutmamız lazım yoksa büyük dizilerde memory allocation hatası alacağız.
    int *L, *R;
    L = (int *) malloc(sizeof(int) * sub1);
    R = (int *) malloc(sizeof(int) * sub2);

    // Alt dizileri sınırlara göre doldur.
    for (i = 0; i < sub1; i++)
        L[i] = dizi[start + i];
    for (j = 0; j < sub2; j++)
        R[j] = dizi[middle + 1+ j];

    // Birleştirmeye başla.
    i = 0;
    j = 0;
    k = start;

    while (i < sub1 && j < sub2)
    {
        toplam_karsilastirma++;

        // Soldaki alt dizinin elemanı sağdakinden küçükse soldakini koy.
        if (L[i] <= R[j])
        {
            dizi[k] = L[i];
            i++;
            toplam_degisim++;
        }
        else // Tersi durumda sağdakini koy.
        {
            dizi[k] = R[j];
            j++;
            toplam_degisim++;
        }
        k++;
    }

    // Sol alt dizide başka eleman kaldıysa birleştirilen diziye koy. bunlar zaten sağ dizidekilerden küçük.
    while (i < sub1)
    {
        dizi[k] = L[i];
        i++;
        k++;
    }

    // En son sağ alt dizide başka eleman kaldıysa üst diziye koy. bunlar zaten sol diziden büyük.
    while (j < sub2)
    {
        dizi[k] = R[j];
        j++;
        k++;
    }

    // Hafızadan sağ ve sol diziyi temizle.
    free(L);
    free(R);
}

int main(){

    int * dizi = diziOlustur(boyut, tur);


    time_t baslangic, bitis;

    double toplam_sure;

    time(&baslangic);

    mergeSort(dizi, 0, boyut-1);

    time(&bitis);

    toplam_sure = difftime(bitis, baslangic);

    printf("----------------\n%d elemanli dizi %llu karsilastirma ve %llu degistirme ile siralandi, %.2f saniye surdu.\n----------------\n",
           boyut, toplam_karsilastirma, toplam_degisim, toplam_sure);

    return 1;
}