#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Tur { sirali = 1, ters_sirali = 2, rastgele = 3 };

// Dizi boyutu global.
int boyut = 100000;
//  Ters sıralı dizi olacak.
Tur tur = ters_sirali;


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


int main(){

    int * dizi = diziOlustur(boyut, tur);

    int i, j, minimum, gecici;

    unsigned long long int adim_degisim, adim_karsilastirma, toplam_degisim=0, toplam_karsilastirma = 0;

    time_t baslangic, bitis;

    double toplam_sure;

    //printf("Baslayalim, dizinin hali:\n");

    //diziYaz(dizi);

    printf("\n----------------\n");

    time(&baslangic);


    for (i = 0; i < boyut-1; i++) {

        minimum = i;
        adim_degisim = 0;
        adim_karsilastirma = 0;

        for (j = i + 1; j < boyut; j++) {

            if (dizi[j] < dizi[minimum]) {
                minimum = j;
            }

            adim_karsilastirma++;
            toplam_karsilastirma++;

        }

        if(minimum != i){

            gecici = dizi[i];
            dizi[i] = dizi[minimum];
            dizi[minimum] = gecici;

            adim_degisim++;
            toplam_degisim++;

        }

        printf("%d. adim | %llu karsilastirma | %llu yer degistirme\n", i + 1, adim_karsilastirma, adim_degisim);

    }

    time(&bitis);

    toplam_sure = difftime(bitis, baslangic);

    printf("----------------\n%d elemanli dizi %d adimda %llu karsilastirma ve %llu degistirme ile siralandi, %.2f saniye surdu.\n----------------\n",
           boyut, i+1, toplam_karsilastirma, toplam_degisim, toplam_sure);
    //diziYaz(dizi);

    return  0;
}
