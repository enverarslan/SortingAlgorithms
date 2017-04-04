#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void degistir(int *, int *);

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

/**
 * Verilen iki pointerdaki değerleri yer değiştir.
 * @param item1
 * @param item2
 */
void degistir(int *item1, int *item2){
    int temp;
    temp = *item1;
    *item1 = *item2;
    *item2 = temp;
    toplam_degisim++;
}

int partition(int * dizi, int start, int end){

    int x = dizi[end];
    int i = start-1;
    int j;

    for(j=start; j<=end-1; j++)
    {
        toplam_karsilastirma++;
        if( dizi[j] <= x)
        {
            i++;
            degistir(&dizi[i], &dizi[j]);
        }
    }
    degistir(&dizi[i+1], &dizi[end]);

    return i+1;
}


void quickSort(int * dizi, int start, int end){

    if (start > end){
        return;
    }

    int q;

    if( start < end)
    {
        q = partition(dizi, start, end);
        quickSort(dizi, start, q-1);
        quickSort(dizi, q+1, end);
    }
}


int main(){
    int * dizi = diziOlustur(boyut, tur);

    time_t baslangic, bitis;

    double toplam_sure;

    time(&baslangic);

    quickSort(dizi, 0, boyut-1);

    time(&bitis);

    toplam_sure = difftime(bitis, baslangic);

    printf("----------------\n%d elemanli dizi %llu karsilastirma ve %llu degistirme ile siralandi, %.2f saniye surdu.\n----------------\n",
           boyut, toplam_karsilastirma, toplam_degisim, toplam_sure);

    return 1;
}