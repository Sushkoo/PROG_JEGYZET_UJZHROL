#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstddef>

// ==================== 1 ====================

int* foglal_tomb(size_t elemszam);
void feltolt_veletlen(int* tomb, size_t meret);
char* konvertal_betuk(const char* forras, size_t meret, char mod);
bool beszur_egyedi(char*& tomb, size_t& meret, char uj_karakter);

// ==================== 2 ====================

struct AknaJatek {
    int** palya;         // 2D dinamikus tömb
    int meret;
    int pontszam;
    int osszes_akna;
    int megtalalt_akna;
};

// Játékkezelõ függvények
void jatek_inditasa();
void palya_felszabadit(AknaJatek& jatek);

#endif // FUNCTIONS_H