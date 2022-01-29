#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct kelimeYapisi {
    char *kelime;
    int adet;
    struct kelimeYapisi *sonraki;
};

struct kelimeYapisi* temp = NULL;
struct kelimeYapisi* kelimeler=NULL;

struct kelimeYapisi* kelimeOlustur (char* Kelime);
struct kelimeYapisi* kelimeEkle (struct kelimeYapisi** kelimeListesi, char* Kelime);
struct kelimeYapisi* basaEkle (struct kelimeYapisi** kelimeListesi, char* Kelime);
struct kelimeYapisi* arayaEkle (struct kelimeYapisi** kelimeListesi, char* arananKelime,char* atanacakKelime);
struct kelimeYapisi* sonaEkle (struct kelimeYapisi** kelimeListesi, char* Kelime);

void dugumleriSirala(struct kelimeYapisi* kelimeler);
void dugumDegistir(struct kelimeYapisi* x, struct kelimeYapisi* y);

int main () {

    FILE* dosya = fopen("test.txt","r");
    FILE* ciktiDosyasi;

    if (dosya == 0) {
        printf ("Dosya acilamadi.\n");
        exit(0);
    }

    int c = 0;
    int i = 0;
    char* kelime=malloc(100);
    char* ayrac = " \t\n";

    while ((c = fgetc (dosya)) != EOF) {
        if (strchr (ayrac, c)) {
                *(kelime+i) = '\0';
                kelimeEkle (&kelimeler, kelime);
                i = 0;
        }
        else {
            *(kelime+i++) = tolower(c);
        }
    }
    free(kelime);

    printf ("\nKelimeler ve adetleri listeye eklendi.\n\n");

    ciktiDosyasi = fopen ("cikti.txt", "w");
    if (ciktiDosyasi == 0) {
        printf ("Cikti dosyasi acilamadi. \n");
        exit(0);
    }

    dugumleriSirala(kelimeler);
    printf("Kelimeler adetlerine gore buyukten kucuge siralandi.\n\n");
    int kelimeSayisi=1;
    while (kelimeler != NULL) {
        fprintf (ciktiDosyasi, "%d. %s: %d \n",kelimeSayisi, kelimeler->kelime, kelimeler->adet);
        printf ("%s ", kelimeler->kelime);
        kelimeler = kelimeler->sonraki;
        kelimeSayisi++;
    }
    printf("\n");
    return 0;
}
struct kelimeYapisi* kelimeOlustur (char* Kelime)
{
    struct kelimeYapisi* yeniKelime = malloc (sizeof (struct kelimeYapisi));
    if (yeniKelime != NULL) {

        yeniKelime->kelime = (char*) malloc ((strlen (Kelime))+1);
        strcpy (yeniKelime->kelime, Kelime);
        yeniKelime->kelime[strlen (Kelime)] = '\0';

        yeniKelime->adet = 1;
        yeniKelime->sonraki = NULL;

    }
    return yeniKelime;
}

struct kelimeYapisi* kelimeEkle (struct kelimeYapisi** kelimeListesi, char* Kelime)
{
    if (!(*kelimeListesi)) {
        return *kelimeListesi = kelimeOlustur (Kelime);
    }

    struct kelimeYapisi* temp = *kelimeListesi;

    while (temp->sonraki != NULL) {

        if (strcmp (temp->kelime, Kelime) == 0) {
            temp->adet++;
            return *kelimeListesi;
        }
        else
            temp = temp->sonraki;
    }
    struct kelimeYapisi *yeniKelime = kelimeOlustur (Kelime);
    if (yeniKelime != NULL) {
        if(strcmp (temp->kelime, yeniKelime->kelime) == 0){
            temp->adet++;
            return *kelimeListesi;
        }
        temp->sonraki = yeniKelime;
    }
    return yeniKelime;
}

struct kelimeYapisi* basaEkle (struct kelimeYapisi** kelimeListesi, char* Kelime)
{
    struct kelimeYapisi* eklenecekKelime = kelimeOlustur(Kelime);
    if(*kelimeListesi == NULL){
        eklenecekKelime->sonraki = NULL;
        *kelimeListesi == eklenecekKelime;
        return *kelimeListesi;
    }
    else{
        eklenecekKelime->sonraki = *kelimeListesi;
        *kelimeListesi = eklenecekKelime;
        return *kelimeListesi;
    }
};

struct kelimeYapisi* arayaEkle (struct kelimeYapisi** kelimeListesi, char* arananKelime,char* atanacakKelime)
{
    struct kelimeYapisi* eklenecekKelime = kelimeOlustur(atanacakKelime);
    temp = *kelimeListesi;
    if(*kelimeListesi == NULL){
        eklenecekKelime->sonraki = NULL;
        *kelimeListesi == eklenecekKelime;
        return *kelimeListesi;
    }
    else{
        while(!(strcmp(temp->kelime,arananKelime)== 0)){
            temp = temp->sonraki;
        }
        eklenecekKelime->sonraki = temp->sonraki;
        temp->sonraki = eklenecekKelime;
        return *kelimeListesi;
    }

};

struct kelimeYapisi* sonaEkle (struct kelimeYapisi** kelimeListesi, char* Kelime){
    struct kelimeYapisi* eklenecekKelime = kelimeOlustur(Kelime);
    temp = *kelimeListesi;
    if(*kelimeListesi == NULL){
        eklenecekKelime->sonraki = NULL;
        *kelimeListesi == eklenecekKelime;
        return *kelimeListesi;
    }
    else{
        while(temp->sonraki != NULL){
            temp = temp->sonraki;
        }
        temp->sonraki = eklenecekKelime;
        return *kelimeListesi;
    }
};

void dugumleriSirala(struct kelimeYapisi* kelimeler)
{
    struct kelimeYapisi* anahtar;
    anahtar = kelimeler;

    while(anahtar != NULL)
    {
        temp = anahtar->sonraki;
        while(temp != NULL)
        {
            if(anahtar->adet < temp->adet)
            {
                dugumDegistir(temp, anahtar);
            }
            temp = temp->sonraki;
        }
        anahtar = anahtar->sonraki;
    }
}

void dugumDegistir(struct kelimeYapisi* x, struct kelimeYapisi* y)
{
    struct kelimeYapisi* temp2 =malloc (sizeof (struct kelimeYapisi));
    temp2->adet = x->adet;
    temp2->kelime = x->kelime;
    x->adet = y->adet;
    x->kelime = y->kelime;
    y->adet = temp2->adet;
    y->kelime = temp2->kelime;
}
