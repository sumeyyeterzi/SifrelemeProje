#include <stdio.h> //Dosya Giriþ-Çýkýþ iþlemlerini gerçekleþtirmeye yarar.
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void tercih();
void sifreleme();
void sdy(int a[], int b[], int sayac); //sifreyi dosyaya yaz
void coz(int coz[], int sayac, int durum[]);
void dvc(); //dosyadan verileri cek
void vsc(char cev[]);

int main()
{
    tercih();

    getch();
    return 0;
}

void tercih()
{
    while (1)
    {
        int tercih = 0;
        printf("Bir islem seciniz.\n");
        printf("1.Metini sifrele\n");
        printf("2.Sifreyi dosyadan coz.\n");
        printf("3.Cikis.\n");
        printf("4.Dosyayi sil.\n");
        printf("Tercihiniz:");
        scanf("%d", &tercih);
        printf("\n");

        if (tercih == 1)
        {
            sifreleme();
        }

        else if (tercih == 2)
        {
            dvc();
        }

        else if (tercih == 3)
        {
            printf("Cikis yapildi.\n");
            break;
        }
        else if (tercih == 4)
        {
            remove("sifre.txt");
        }

        else
        {
            printf("Basarisiz islem.\n");
            break;
        }
    }
}

void sifreleme()
{
    getchar();
    char metin[100];
    printf("Lutfen bir metin giriniz:");
    gets(metin);
    printf("Girdiginiz metin:%s\n", metin);

    //-----------------------------------------------
    int i, j, sayac = 0;
    int ascii[100];

    for (i = 0; metin[i] != '\0'; i++) // Karakterleri sayiya cevirir
    {
        sayac += 1;
        ascii[i] = (int)(metin[i]);
    }

    //-----------------------------------------------
    int hane[sayac][2];
    printf("Girdiginiz metinin sayisal degeri:"); //Girilen metinin ascii degerleri
    for (i = 0; i < sayac; i++)
    {
        printf("%d ", ascii[i]);
        hane[i][2] = 0; // Ýndexler sifirlaniyor.
    }
    printf("\n");

    //-------------------------------------------------
    for (i = 0; i < sayac; i++) // Sayýsal karþýlýðýný hanelere çeviren döngü
    {
        hane[i][0] = ascii[i] / 10;
        hane[i][1] = ascii[i] % 10;
    }
    //-------------------------------------------------
    for (i = 0; i < sayac; i++) //Haneleri ekrana basar
    {
        for (j = 0; j < 2; j++)
        {
            printf("%d  ", hane[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //--------------------------------------------------
    int sifre[sayac];
    int durum[sayac];
    for (i = 0; i < sayac; i++)
    {
        int anahtar = 0;
        int cal;

    don:
        cal = 0;
        if (hane[i][0] - hane[i][1] == 1)
        {
            cal = 1;
        }
        if (hane[i][1] - hane[i][0] == 1)
        {
            cal = 1;
        }
        if (hane[i][0] - hane[i][1] == 0)
        {
            cal = 1;
        }

        if (cal == 1)
        {
            if (hane[i][0] == hane[i][1])
            {
                sifre[i] = hane[i][1] * 10 + anahtar;
            }
            else
            {
                sifre[i] = hane[i][0] * 100 + hane[i][1] * 10 + anahtar;
            }
        }

        else
        {
            if (hane[i][1] - hane[i][0] < 0)
            {
                hane[i][0] = hane[i][0] - 1;
                hane[i][1] = hane[i][1] + 1;
                anahtar += 1;
                durum[i] = 1;
                goto don;
            }

            else if (hane[i][1] - hane[i][0] > 0)
            {
                hane[i][0] = hane[i][0] + 1;
                hane[i][1] = hane[i][1] - 1;
                anahtar += 1;
                durum[i] = 0;
                goto don;
            }
        }
    }
    //----------------------------------------------
    for (i = 0; i < sayac; i++)
    {
        printf("%d ", sifre[i]);
    }
    printf("\n");
    //-----------------------------------------------
    sdy(sifre, durum, sayac);
    coz(sifre, sayac, durum);
}

void sdy(int a[], int b[], int sayac)
{
    int i, j;
    FILE *sifre = fopen("sifre.txt", "a+");
    for (i = 0; i < sayac; ++i)
    {
        fprintf(sifre, "-%d,%d", a[i], b[i]);
    }
    fclose(sifre);
}

void dvc()
{
    FILE *sifre;
    if ((sifre = fopen("sifre.txt", "r")) == NULL)
    {
        printf("Dosya kayip yada silinmis");
        exit(1);
    }
    int veri[50];
    int durum[50];
    int i;
    int sayac = 0;
    int gecici;
    int gecici2;
    char a, b;

    for (i = 0; !feof(sifre); i++)
    {
        fscanf(sifre, "%c%d%c%d", &a, &gecici, &b, &gecici2);
        veri[i] = gecici;
        durum[i] = gecici2;
        sayac += 1;
    }
    for (i = 0; i < sayac; i++)
    {
        printf("%d ", veri[i]);
    }
    coz(veri, sayac, durum);

    fclose(sifre);
}

void coz(int coz[], int sayac, int durum[])
{
    int i, j;
    int dogru[sayac];
    int anahtar[sayac];

    for (i = 0; i < sayac; i++)
    {
        anahtar[i] = coz[i] % 10;
        coz[i] = (coz[i] - anahtar[i]) / 10;
        printf("%d  ", anahtar[i]);
    }
    printf("\n");
    // buraya kadar doðru

    for (i = 0; i < sayac; i++)
    {
        printf("%d  ", coz[i]);
    }

    printf("\n");
    // buraya kadarda doðru
    int p;
    for (i = 0; i < sayac; i++)
    {
        int t;
        int y;
        if (coz[i] < 10)
        {
            if (durum[i] == 1)
            {
                t = (coz[i] + anahtar[i]) * 10;
                y = coz[i] - anahtar[i];
            }
            else
            {
                t = (coz[i] - anahtar[i]) * 10;
                y = coz[i] + anahtar[i];
            }

            p = t + y;
            dogru[i] = p;
        }
        else
        {
            int f = coz[i] / 10;

            int d = coz[i] % 10;
            if (durum[i] == 1)
            {
                t = (f + anahtar[i]) * 10;
                y = d - anahtar[i];
            }
            else
            {
                t = (f - anahtar[i]) * 10;
                y = d + anahtar[i];
            }

            p = t + y;
            dogru[i] = p;
        }

        printf("%d  ", p);
    }
    printf("\n");

    for (i = 0; i < sayac; i++)
    {

        printf("%c", dogru[i]);
    }
    printf("\n\n");
}
