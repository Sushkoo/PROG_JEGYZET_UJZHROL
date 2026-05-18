#define _CRT_SECURE_NO_WARNINGS //azert van hogy ne rinyaljon a visual studio
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "functions.h"


// ==================== 1 ====================
void* foglal_tomb(size_t elemszam, size_t elem_meret) {
    void* ptr = calloc(elemszam, elem_meret);
    if (ptr == NULL) {
        fprintf(stderr, "Kritikus hiba: Sikertelen memoriafoglalas!\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void feltolt_veletlen(int* tomb, size_t meret) {
    if (tomb == NULL) return;
    for (size_t i = 0; i < meret; ++i) {
        tomb[i] = rand() % 256;
    }
}

char* konvertal_betuk(const char* forras, size_t meret, char mod) {
    if (forras == NULL) return NULL;
    char* cel_tomb = (char*)foglal_tomb(meret, sizeof(char));
    for (size_t i = 0; i < meret; ++i) {
        if (mod == 'k') cel_tomb[i] = tolower(forras[i]);
        else if (mod == 'n') cel_tomb[i] = toupper(forras[i]);
        else cel_tomb[i] = forras[i];
    }
    return cel_tomb;
}

bool beszur_egyedi(char** tomb, size_t* meret, char uj_karakter) {
    if (tomb == NULL || *tomb == NULL || meret == NULL) return false;
    for (size_t i = 0; i < *meret; ++i) {
        if ((*tomb)[i] == uj_karakter) return false;
    }
    char* uj_ptr = realloc(*tomb, (*meret + 1) * sizeof(char));
    if (uj_ptr == NULL) {
        fprintf(stderr, "Hiba: Sikertelen ujrafoglalas a beszuraskor!\n");
        return false;
    }
    *tomb = uj_ptr;
    (*tomb)[*meret] = uj_karakter;
    (*meret)++;
    return true;
}

// ==================== 2 ====================

// Segédfüggvény a 2D maphoz
void palya_felszabadit(AknaJatek* jatek) {
    if (jatek->palya != NULL) {
        for (int i = 0; i < jatek->meret; i++) {
            free(jatek->palya[i]);
        }
        free(jatek->palya);
        jatek->palya = NULL;
    }
}

void jatek_inditasa() {
    AknaJatek jatek;
    jatek.pontszam = 5; // kezdopontszam
    jatek.megtalalt_akna = 0;
    jatek.palya = NULL;

    printf("=== 2. Feladat: Aknakereso Jatek ===\n");
    printf("Adja meg a palya meretet (pl. 5 eseten 5x5 lesz): ");

    // hibakezeles
    if (scanf_s("%d", &jatek.meret) != 1 || jatek.meret <= 0) {
        fprintf(stderr, "Hiba: Ervenytelen palyameret!\n");
        return;
    }

    // 2D Dinamikus tömb foglalása a pályának
    jatek.palya = (int**)foglal_tomb(jatek.meret, sizeof(int*));
    for (int i = 0; i < jatek.meret; i++) {
        jatek.palya[i] = (int*)foglal_tomb(jatek.meret, sizeof(int));
    }


    int min_akna = jatek.meret;
    int max_akna = jatek.meret * 2;
    jatek.osszes_akna = min_akna + (rand() % (max_akna - min_akna + 1));

    // Nem lehet tobb akna annal amekkora a tomb
    if (jatek.osszes_akna > jatek.meret * jatek.meret) {
        jatek.osszes_akna = jatek.meret * jatek.meret;
    }

    // Aknák elhelyezése véletlenszerûen
    int lehelyezett_akna = 0;
    while (lehelyezett_akna < jatek.osszes_akna) {
        int r = rand() % jatek.meret;
        int c = rand() % jatek.meret;
        if (jatek.palya[r][c] == 0) { // Ha még üres a mezõ
            jatek.palya[r][c] = 1;    // 1 jelöli az aknát
            lehelyezett_akna++;
        }
    }

    printf("A palya legeneralva. Aknak szama: %d. Sok sikert!\n\n", jatek.osszes_akna);

    // Addig tart amig el nem fogy a pontunk (jatekmenet)
    while (jatek.pontszam > 0 && jatek.megtalalt_akna < jatek.osszes_akna) {
        // Aktuális állás és a rejtett pálya kirajzolása
        printf("Pontszamod: %d | Megtalalt aknak: %d/%d\n", jatek.pontszam, jatek.megtalalt_akna, jatek.osszes_akna);

        printf("   ");
        for (int j = 0; j < jatek.meret; j++) printf("%d ", j);
        printf("\n");

        for (int i = 0; i < jatek.meret; i++) {
            printf("%d |", i);
            for (int j = 0; j < jatek.meret; j++) {
                if (jatek.palya[i][j] == 2) {
                    printf("X "); // Megtalált akna
                }
                else {
                    printf(". "); // Rejtett mezo
                }
            }
            printf("\n");
        }

        // Tipp bekérése
        //printf az olyan mint a cout csak sokkal rovidebb  || ennek a parja az scanf ami meg a cin -t helyettesiti (%d: egesz szam, %c: karakter/betu, %f: float (tortszam))
        int tipp_sor, tipp_oszlop;
        printf("\nAdja meg a tippet (sor es oszlop szokozzel elvalasztva, pl: 1 2): ");
        if (scanf_s("%d %d", &tipp_sor, &tipp_oszlop) != 2) {
            fprintf(stderr, "Hiba a koordinatak beolvasasakor! Probalja ujra.\n");
            // hibas karakterrel tovabb megy
            while (getchar() != '\n');
            continue;
        }

        // hatarcsekk
        if (tipp_sor < 0 || tipp_sor >= jatek.meret || tipp_oszlop < 0 || tipp_oszlop >= jatek.meret) {
            printf("Hiba: A koordinata a palyan kivulre esik! (0 es %d kozott adjon meg ertekeket)\n\n", jatek.meret - 1);
            continue;
        }

        // Találat kiértékelése
        if (jatek.palya[tipp_sor][tipp_oszlop] == 1) {
            // JÓ TALÁLAT
            printf("-> Aknat talaltal! (+10 pont)\n\n");
            jatek.pontszam += 10;
            jatek.megtalalt_akna++;
            jatek.palya[tipp_sor][tipp_oszlop] = 2; // Megtalált státusz
        }
        else if (jatek.palya[tipp_sor][tipp_oszlop] == 2) {
            // MÁR MEGTALÁLT AKNA
            printf("-> Ezt az aknat mar korabban megtalaltad.\n\n");
        }
        else {
            // ROSSZ TALÁLAT
            printf("-> Melle! Itt nincs akna. (-1 pont)\n\n");
            jatek.pontszam -= 1;
        }
    }

    // Játék vége értékelés
    if (jatek.megtalalt_akna == jatek.osszes_akna) {
        printf("=== GRATULALOK, NYERTEL! ===\n");
        printf("Minden aknat sikeresen hatastalanitottal! Vegso pontszamod: %d\n", jatek.pontszam);
    }
    else {
        printf("=== JATEK VEGE, VESZTETTEL! ===\n");
        printf("Elfogyott az osszes pontod.\n");
    }

    // Memória felszabadítása a játék végén
    palya_felszabadit(&jatek);
    printf("A jatek memoria terulete sikeresen fel lett szabaditva.\n\n");
}