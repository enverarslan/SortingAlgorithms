#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Tur {
    sirali = 1, ters_sirali = 2, rastgele = 3
};

// Dizi boyutu global.
int boyut = 100000;
//  Ters sıralı dizi olacak.
enum Tur tur = ters_sirali;

// Recursion olduğu için değişim ve karşılaştırmaları global tut.
unsigned long long int toplam_degisim = 0, toplam_karsilastirma = 0;

/**
 * Adresi verilen dizinin elemanlarını ekrana bas.
 * @param pointer dizi
 * @return void
 */
void diziYaz(int *dizi) {

    int l;

    for (l = 0; l < boyut; l++) {
        printf("%d,", dizi[l]);
    }

}

/**
 * Belirtilen boyut ve türde dizi oluştur ve adresini döndür.
 * @param int boyut
 * @param enum Tur tip
 * @return  pointer
 */
int *diziOlustur(int boyut, enum Tur tip) {

    int *dizi;
    int i;

    dizi = (int *) malloc(sizeof(int) * boyut);

    if (tip == 1) {

        for (i = 0; i < boyut; i++) {
            dizi[i] = i;
        }

    } else if (tip == 2) {

        for (i = 0; i < boyut; i++) {
            dizi[i] = boyut - i - 1;
        }

    } else {

        srand(time(NULL)); // rastgele sayı üretmek için besleme.

        for (i = 0; i < boyut; i++) {
            dizi[i] = (rand() % boyut);
        }

    }

    return dizi;
}

int getMax(int * dizi, int boyut) {

    int i, max = dizi[0];
    for (i = 1; i < boyut; i++){
        if (dizi[i] > max){
            max = dizi[i];
        }
    }
    return max;
}

void countSort(int * dizi, int boyut, int taban) {

    // geçici dizi oluştur.
    int * output = (int *) malloc(sizeof(int) * boyut);
    // geçici 10 elemanlı rakam dizisi oluştur.
    int * count  = (int *) malloc(sizeof(int) * 10);

    int i, mod;

    // Count dizisini 0 ile doldur.
    for (i = 0; i < 10; i++){
        count[i] = 0;
    }

    // hanedeki rakamı bul, rakamsal dizideki yerini bir arttır.
    for (i = 0; i < boyut; i++){
        mod = (dizi[i] / taban) % 10;
        count[mod]++;
    }


    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // hanedeki rakamı bul, geçici diziye yaz.
    for (i = boyut - 1; i >= 0; i--) {

        mod = (dizi[i] / taban) % 10;

        output[count[mod] - 1] = dizi[i];
        count[mod]--;
    }

    // Geçici diziden asıl diziye elemanları geçir.
    for (i = 0; i < boyut; i++) {
        dizi[i] = output[i];
    }

    // Hafızadan geçici dizileri silelim.
    free(output);
    free(count);
}


void radixsort(int * dizi, int boyut) {

    int taban, max = getMax(dizi, boyut);

    for (taban = 1; (max / taban) > 0; taban *= 10) {
        countSort(dizi, boyut, taban);
    }

}

int main() {

    int *dizi = diziOlustur(boyut, tur);

    time_t baslangic, bitis;

    double toplam_sure;

    time(&baslangic);

    radixsort(dizi, boyut);

    time(&bitis);

    toplam_sure = difftime(bitis, baslangic);

    printf("%d | %d\n", dizi[0], dizi[boyut-1]);

    printf("----------------\n%d elemanli dizi siralandi, %.2f saniye surdu.\n----------------\n",
           boyut, toplam_sure);

    //diziYaz(dizi);


    return 0;
}
