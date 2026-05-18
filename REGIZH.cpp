#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <set>

using namespace std;

// ======================================================================
// 1. FELADAT: Adatmanipulációs szoftvermodul
// ======================================================================

bool isMaganhangzo(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int kulonbozoMassalhangzok(const char* tomb, int meret) {
    set<char> massalhangzok;
    for (int i = 0; i < meret; ++i) {
        if (!isMaganhangzo(tomb[i]) && isalpha(tomb[i])) {
            massalhangzok.insert(tomb[i]);
        }
    }
    return massalhangzok.size();
}

void maganhangzokSzamjeggye(char* tomb, int meret) {
    for (int i = 0; i < meret; ++i) {
        switch (tomb[i]) {
        case 'a': tomb[i] = '1'; break;
        case 'e': tomb[i] = '2'; break;
        case 'i': tomb[i] = '3'; break;
        case 'o': tomb[i] = '4'; break;
        case 'u': tomb[i] = '5'; break;
        }
    }
}

void karakterTorlese(char* tomb, int& meret, char torlendo) {
    int uj_meret = 0;
    for (int i = 0; i < meret; ++i) {
        if (tomb[i] != torlendo) {
            tomb[uj_meret++] = tomb[i];
        }
    }
    meret = uj_meret;
}

void kulonbozoKarakterekFajlba(const char* tomb, int meret, const string& fajlnev) {
    set<char> egyedi_karakterek;
    for (int i = 0; i < meret; ++i) {
        egyedi_karakterek.insert(tomb[i]);
    }

    ofstream out(fajlnev);
    if (out.is_open()) {
        out << "A tombben levo kulonbozo karakterek: ";
        for (char c : egyedi_karakterek) {
            out << c << " ";
        }
        out.close();
        cout << "-> A kulonbozo karakterek kimentve a '" << fajlnev << "' fajlba.\n";
    }
}

void futtas_feladat1() {
    cout << "--- 1. FELADAT: ADATMANIPULACIO ---\n";
    int a, b, c;
    cout << "Kerek harom egesz szamot (szokozzel elvalasztva): ";
    cin >> a >> b >> c;

    int meret = abs(a + b + c);
    if (meret == 0) meret = 10;
    cout << "A lefoglalt tomb merete: " << meret << " elem.\n";

    char* karakter_tomb = new char[meret];
    cout << "Eredeti tomb: ";
    for (int i = 0; i < meret; ++i) {
        karakter_tomb[i] = 'a' + (rand() % 26);
        cout << karakter_tomb[i];
    }
    cout << "\n";

    int mh_szam = kulonbozoMassalhangzok(karakter_tomb, meret);
    cout << "Kulonbozo massalhangzok szama: " << mh_szam << "\n";

    maganhangzokSzamjeggye(karakter_tomb, meret);
    cout << "Maganhangzok cserelve: ";
    for (int i = 0; i < meret; ++i) cout << karakter_tomb[i];
    cout << "\n";

    char torlendo;
    cout << "Melyik karaktert toroljuk a tombbol? ";
    cin >> torlendo;
    karakterTorlese(karakter_tomb, meret, torlendo);

    cout << "Tomb a torles utan: ";
    for (int i = 0; i < meret; ++i) cout << karakter_tomb[i];
    cout << " (Uj meret: " << meret << ")\n";

    kulonbozoKarakterekFajlba(karakter_tomb, meret, "egyedi_karakterek.txt");

    delete[] karakter_tomb;
    cout << "\n";
}

// ======================================================================
// 2. FELADAT: Tömörítõ szoftver
// ======================================================================

class TomoritoSzoftver {
public:
    void tomorit(const vector<string>& bemeneti_fajlok, const string& kimeneti_fajl) {
        ofstream kimenet(kimeneti_fajl, ios::binary);
        if (!kimenet.is_open()) {
            throw runtime_error("Kritikus hiba: Nem sikerult letrehozni az archivumot!");
        }

        int fajlAzonosito = 0x4B434150;
        kimenet.write(reinterpret_cast<const char*>(&fajlAzonosito), sizeof(int));

        int fajlokSzama = (int)bemeneti_fajlok.size();
        kimenet.write(reinterpret_cast<const char*>(&fajlokSzama), sizeof(int));

        vector<int> meretek;
        for (const string& nev : bemeneti_fajlok) {
            ifstream bemenet(nev, ios::binary | ios::ate);
            if (!bemenet.is_open()) {
                throw runtime_error("Hiba: A beolvasando fajl nem talalhato: " + nev);
            }
            meretek.push_back((int)bemenet.tellg());
            bemenet.close();
        }

        for (int m : meretek) {
            kimenet.write(reinterpret_cast<const char*>(&m), sizeof(int));
        }

        for (size_t i = 0; i < bemeneti_fajlok.size(); ++i) {

            // --- ITT A VALTOZTATAS: Kuka a strncpy, helyette sima ciklus! ---
            char nev_buffer[32] = { 0 };
            string aktualis_nev = bemeneti_fajlok[i];

            for (size_t j = 0; j < aktualis_nev.length() && j < 31; ++j) {
                nev_buffer[j] = aktualis_nev[j];
            }
            // ----------------------------------------------------------------

            kimenet.write(nev_buffer, 32);

            ifstream bemenet(bemeneti_fajlok[i], ios::binary);
            kimenet << bemenet.rdbuf();
            bemenet.close();
        }

        kimenet.close();
        cout << "-> A tomorites sikeres! Felveve " << fajlokSzama << " fajl a(z) '" << kimeneti_fajl << "' archívumba.\n";
    }
};

void tesztFajlokLetrehozasa() {
    ofstream f1("teszt1.txt"); f1 << "Ez az elso tesztfajl tartalma."; f1.close();
    ofstream f2("teszt2.txt"); f2 << "Ez pedig a masodik tesztfajl kicsit tobb szoveggel."; f2.close();
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    futtas_feladat1();

    cout << "--- 2. FELADAT: TOMORITO SZOFTVER ---\n";
    tesztFajlokLetrehozasa();

    vector<string> fajlok_tomoritesre = { "teszt1.txt", "teszt2.txt" };
    TomoritoSzoftver archivalo;

    try {
        archivalo.tomorit(fajlok_tomoritesre, "archivalt_adatok.bin");
    }
    catch (const exception& e) {
        cerr << "\nFutasideju hiba elkapva:\n" << e.what() << "\n";
    }

    return 0;
}