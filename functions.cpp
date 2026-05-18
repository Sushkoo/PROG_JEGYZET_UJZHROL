#include "functions.h"
#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

// ==================== 1 ====================

int* foglal_tomb(size_t elemszam) {
    // A 'new int[elemszam]()' a () miatt automatikusan 0-val tölti fel
    int* ptr = new (nothrow) int[elemszam]();
    if (!ptr) { 
        cerr << "Kritikus hiba: Sikertelen memoriafoglalas!\n";
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void feltolt_veletlen(int* tomb, size_t meret) {
    if (!tomb) return;
    for (size_t i = 0; i < meret; ++i) {
        tomb[i] = rand() % 256;
    }
}

char* konvertal_betuk(const char* forras, size_t meret, char mod) {
    if (!forras) return nullptr;

    char* cel_tomb = new (nothrow) char[meret];
    if (!cel_tomb) return nullptr;

    for (size_t i = 0; i < meret; ++i) {
        if (mod == 'k') cel_tomb[i] = tolower(forras[i]);
        else if (mod == 'n') cel_tomb[i] = toupper(forras[i]);
        else cel_tomb[i] = forras[i];
    }
    return cel_tomb;
}

bool beszur_egyedi(char*& tomb, size_t& meret, char uj_karakter) {
    if (!tomb) return false;

    //benne van-e már?
    for (size_t i = 0; i < meret; ++i) {
        if (tomb[i] == uj_karakter) return false;
    }

    
    char* uj_tomb = new (nothrow) char[meret + 1];
    if (!uj_tomb) return false; // Hibakezelés

    for (size_t i = 0; i < meret; ++i) uj_tomb[i] = tomb[i];
    uj_tomb[meret] = uj_karakter;

    delete[] tomb; // Régi memória felszabadítása
    tomb = uj_tomb;
    meret++;

    return true;
}

// ==================== 2 ====================

void palya_felszabadit(AknaJatek& jatek) {
    if (jatek.palya) {
        for (int i = 0; i < jatek.meret; i++) {
            delete[] jatek.palya[i];
        }
        delete[] jatek.palya;
        jatek.palya = nullptr;
    }
}

void jatek_inditasa() {
    AknaJatek jatek;
    jatek.pontszam = 5;
    jatek.megtalalt_akna = 0;
    jatek.palya = nullptr;

    cout << "=== 2. Feladat: Aknakereso Jatek ===\n";
    cout << "Adja meg a palya meretet (pl. 5 eseten 5x5 lesz): ";

    if (!(cin >> jatek.meret) || jatek.meret <= 0) {
        cerr << "Hiba: Ervenytelen palyameret!\n";
        return;
    }

    // 2D Dinamikus tömb foglalása
    jatek.palya = new int* [jatek.meret];
    for (int i = 0; i < jatek.meret; i++) {
        jatek.palya[i] = new int[jatek.meret](); // 0 kezdõérték
    }

    int min_akna = jatek.meret;
    int max_akna = jatek.meret * 2;
    jatek.osszes_akna = min_akna + (rand() % (max_akna - min_akna + 1));
    if (jatek.osszes_akna > jatek.meret * jatek.meret) jatek.osszes_akna = jatek.meret * jatek.meret;

    int lehelyezett_akna = 0;
    while (lehelyezett_akna < jatek.osszes_akna) {
        int r = rand() % jatek.meret;
        int c = rand() % jatek.meret;
        if (jatek.palya[r][c] == 0) {
            jatek.palya[r][c] = 1;
            lehelyezett_akna++;
        }
    }

    cout << "A palya legeneralva. Aknak szama: " << jatek.osszes_akna << ". Sok sikert!\n\n";

    while (jatek.pontszam > 0 && jatek.megtalalt_akna < jatek.osszes_akna) {
        cout << "Pontszamod: " << jatek.pontszam << " | Megtalalt aknak: " << jatek.megtalalt_akna << "/" << jatek.osszes_akna << "\n   ";

        for (int j = 0; j < jatek.meret; j++) cout << j << " ";
        cout << "\n";
        for (int i = 0; i < jatek.meret; i++) {
            cout << i << " |";
            for (int j = 0; j < jatek.meret; j++) {
                if (jatek.palya[i][j] == 2) cout << "X ";
                else cout << ". ";
            }
            cout << "\n";
        }

        int tipp_sor, tipp_oszlop;
        cout << "\nAdja meg a tippet (sor es oszlop szokozzel elvalasztva, pl: 1 2): ";

        if (!(cin >> tipp_sor >> tipp_oszlop)) {
            cerr << "Hiba a beolvasaskor! Probalja ujra.\n";
            cin.clear(); cin.ignore(10000, '\n');
            continue;
        }

        if (tipp_sor < 0 || tipp_sor >= jatek.meret || tipp_oszlop < 0 || tipp_oszlop >= jatek.meret) {
            cout << "Hiba: A koordinata a palyan kivulre esik!\n\n";
            continue;
        }

        if (jatek.palya[tipp_sor][tipp_oszlop] == 1) {
            cout << "-> BINGO! Aknat talaltal! (+10 pont)\n\n";
            jatek.pontszam += 10;
            jatek.megtalalt_akna++;
            jatek.palya[tipp_sor][tipp_oszlop] = 2;
        }
        else if (jatek.palya[tipp_sor][tipp_oszlop] == 2) {
            cout << "-> Ezt az aknat mar korabban megtalaltad.\n\n";
        }
        else {
            cout << "-> Melle! Itt nincs akna. (-1 pont)\n\n";
            jatek.pontszam -= 1;
        }
    }

    if (jatek.megtalalt_akna == jatek.osszes_akna) {
        cout << "=== GRATULALOK, NYERTEL! Vegso pontszamod: " << jatek.pontszam << " ===\n";
    }
    else {
        cout << "=== JATEK VEGE, VESZTETTEL! Elfogyott az osszes pontod. ===\n";
    }

    palya_felszabadit(jatek);
}