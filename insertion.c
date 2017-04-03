#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Tur { sirali = 1, ters_sirali = 2, rastgele = 3 };

// Dizi boyutu global.
int boyut = 100;
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

    int i,j, gecici, t;

    unsigned long long int adim_degisim, adim_karsilastirma, toplam_degisim=0, toplam_karsilastirma = 0;

    time_t baslangic, bitis;
    double toplam_sure;
    time(&baslangic);


    for (i = 1; i < boyut; i++) {

        gecici = dizi[i];
        j = i;

        adim_degisim = 0, adim_karsilastirma = 0;


        while ( (gecici < dizi[j - 1]) && (j > 0) ) {

            dizi[j] = dizi[j - 1];
            j--;

            adim_karsilastirma++;
            toplam_karsilastirma++;

            adim_degisim++;
            toplam_degisim++;


        }

        dizi[j] = gecici;

        printf("%d. adim | %llu karsilastirma | %llu yer degistirme\n", i, adim_karsilastirma, adim_degisim);

    }

    time(&bitis);

    toplam_sure = difftime(bitis, baslangic);

    printf("----------------\n%d elemanli dizi %d adimda %llu karsilastirma ve %llu degistirme ile siralandi, %.2f saniye surdu.\n----------------\n",
           boyut, i-1, toplam_karsilastirma, toplam_degisim, toplam_sure);

    return 1;
}

