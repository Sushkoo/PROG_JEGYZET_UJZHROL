#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"


int main() {
    // Véletlenszám-generátor inicializálása
    srand((unsigned int)time(NULL));

    printf("=========================================\n");
    printf("          1. FELADAT          \n");
    printf("=========================================\n");

    // 1-2. feladat: 128 elemû tömb
    int* egesz_tomb = (int*)foglal_tomb(128, sizeof(int));
    printf("1-2. Feladat: 128 elemu dinamikus egesz tomb lefoglalva.\n");

    // 3. feladat: Feltöltés
    feltolt_veletlen(egesz_tomb, 128);
    printf("3. Feladat: Tomb feltoltve. Pelda ertekek: %d, %d...\n\n", egesz_tomb[0], egesz_tomb[1]);

    // 4. feladat: Karakterkonverzió
    size_t kar_tomb_meret = 6;
    char* eredeti_kar_tomb = (char*)foglal_tomb(kar_tomb_meret, sizeof(char));
    char minta[] = { 'A', 'b', 'C', 'd', 'E', 'f' };
    for (size_t i = 0; i < kar_tomb_meret; i++) eredeti_kar_tomb[i] = minta[i];

    char konv_mod;
    printf("4. Feladat: Karakterkonverzio (k = kisbetu, n = nagybetu): ");
    if (scanf(" %c", &konv_mod) != 1) {
        fprintf(stderr, "Hiba a beolvasaskor!\n");
        return EXIT_FAILURE;
    }

    char* konvertalt_tomb = konvertal_betuk(eredeti_kar_tomb, kar_tomb_meret, konv_mod);
    printf("Eredeti: ");
    for (size_t i = 0; i < kar_tomb_meret; i++) printf("%c", eredeti_kar_tomb[i]);
    printf(" -> Konvertalt: ");
    for (size_t i = 0; i < kar_tomb_meret; i++) printf("%c", konvertalt_tomb[i]);
    printf("\n\n");

    // 5. feladat: Beszúrás
    char uj_kar;
    printf("5. Feladat: Adjon meg egy karaktert a beszurasra: ");
    if (scanf(" %c", &uj_kar) != 1) {
        fprintf(stderr, "Hiba a beolvasaskor!\n");
        return EXIT_FAILURE;
    }

    if (beszur_egyedi(&eredeti_kar_tomb, &kar_tomb_meret, uj_kar)) {
        printf("-> Sikeres beszuras!\n");
    }
    else {
        printf("-> Sikertelen: mar létezik a karakter!\n");
    }

    // 1. feladat memóriáinak takarítása
    free(egesz_tomb);
    free(eredeti_kar_tomb);
    free(konvertalt_tomb);

    printf("\n=========================================\n");
    printf("          2. FELADAT FUTTATASA           \n");
    printf("=========================================\n");

    // 2. feladat meghívása: Interaktív aknakeresõ játék indítása
    jatek_inditasa();

    printf("A program sikeresen befejezodott.\n");
    return 0;
}