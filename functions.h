#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>
#include <stdbool.h>

// 1
void* foglal_tomb(size_t elemszam, size_t elem_meret);
void feltolt_veletlen(int* tomb, size_t meret);
char* konvertal_betuk(const char* forras, size_t meret, char mod);
bool beszur_egyedi(char** tomb, size_t* meret, char uj_karakter);

// 2

// Sturct
typedef struct {
    int** palya;         // 2D dinamikus tömb a pályának (0: üres, 1: akna, 2: már megtalált akna)
    int meret;          // NxN - palya
    int pontszam;       //elert pont
    int osszes_akna;    
    int megtalalt_akna; 
} AknaJatek;


void jatek_inditasa();
void palya_felszabadit(AknaJatek* jatek);

#endif // FUNCTIONS_H