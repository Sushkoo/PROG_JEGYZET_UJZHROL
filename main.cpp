#include <iostream>
#include <ctime>
#include <cstdlib>
#include "functions.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "=========================================\n";
    cout << "          1. FELADAT FUTTATASA           \n";
    cout << "=========================================\n";

    // 1-2. feladat
    int* egesz_tomb = foglal_tomb(128);
    cout << "1-2. Feladat: 128 elemu dinamikus egesz tomb lefoglalva 0 kezdoertekkel.\n";

    // 3. feladat
    feltolt_veletlen(egesz_tomb, 128);
    cout << "3. Feladat: Tomb feltoltve. Pelda ertekek: " << egesz_tomb[0] << ", " << egesz_tomb[1] << "\n\n";

    // 4. feladat
    size_t kar_tomb_meret = 6;
    char* eredeti_kar_tomb = new char[kar_tomb_meret];
    char minta[] = { 'A', 'b', 'C', 'd', 'E', 'f' };
    for (size_t i = 0; i < kar_tomb_meret; i++) eredeti_kar_tomb[i] = minta[i];

    char konv_mod;
    cout << "4. Feladat: Karakterkonverzio (k = kisbetu, n = nagybetu): ";
    cin >> konv_mod;

    char* konvertalt_tomb = konvertal_betuk(eredeti_kar_tomb, kar_tomb_meret, konv_mod);
    cout << "Eredeti: ";
    for (size_t i = 0; i < kar_tomb_meret; i++) cout << eredeti_kar_tomb[i];
    cout << " -> Konvertalt: ";
    for (size_t i = 0; i < kar_tomb_meret; i++) cout << konvertalt_tomb[i];
    cout << "\n\n";

    // 5. feladat
    char uj_kar;
    cout << "5. Feladat: Adjon meg egy karaktert a beszurasra: ";
    cin >> uj_kar;

    if (beszur_egyedi(eredeti_kar_tomb, kar_tomb_meret, uj_kar)) {
        cout << "-> Sikeres beszuras!\n";
    }
    else {
        cout << "-> Sikertelen: mar letezi a karakter!\n";
    }

    // Tiszta C++ memóriatakarítás
    delete[] egesz_tomb;
    delete[] eredeti_kar_tomb;
    delete[] konvertalt_tomb;

    cout << "\n=========================================\n";
    cout << "          2. FELADAT FUTTATASA           \n";
    cout << "=========================================\n";

    jatek_inditasa();

    cout << "A program sikeresen befejezodott.\n";
    return 0;
}