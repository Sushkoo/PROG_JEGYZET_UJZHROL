#include <iostream>
#include <string>
#include <fstream> //fajlkezeles
#include <cstdlib> // rand() fuggvenyhez kellene de lehet anelkul is jo 
#include <vector> //dinamikus lista
#include <stdexcept> //kivetelkezeles
#include <sstream> //sor darabolas (,)

using namespace std;

class Product {
private:
    string kategoria;
    string termeknev;
    unsigned int lejarat; //unsigned: csak 0 vagy pozitiv szamok, nincs elojel
    float ar;

public:
    //parameteres konstruktor
    Product(const string& kategoria, const string& termeknev, unsigned int lejarat, float ar)
        : kategoria(kategoria), termeknev(termeknev), lejarat(lejarat), ar(ar)
    {
    }
    //alapertelmezett konstruktor
    Product() = default;

    //destruktor - VIRTUAL kell ha orokoltetsz
    virtual ~Product() = default;

    void akcio(unsigned int datum) {
        // Csak akkor vonunk ki, ha a lejarat a nagyobb (nem csordul alul a kivonás),
        // VAGY ha le akarod értékelni a már lejártakat is, akkor sima int-be kell kényszeríteni a kivonást.

        // Biztonságos feltétel: még nem járt le, ÉS 3 napon belül le fog járni
        if (lejarat > datum && (lejarat - datum) < 3) {

            // Itt a (float) kényszeríti a C++-t, hogy törtszámos osztást csináljon!
            // Illetve visszatettem a *= (szorzás) jelet, hogy tényleg olcsóbb legyen.
            ar /= (1.0f - ((float)rand() / RAND_MAX) * 0.1f + 0.05f);

            cout << "Uj akcios ar: " << ar << " Ft" << endl;
        }
    }

    //ezzel lehet fajlba és console-ra irni
    virtual void kiir(ostream& kimenet = cout) const {
        kimenet << kategoria << "," << termeknev << "," << lejarat << "," << ar;
    }



    //LEKERDEZO METODUSOK (GETTER)

    string getKategoria() const { return kategoria; }

    string getTermeknev() const { return termeknev; }

    int getLejarat() const { return lejarat; }

    float getAr() const { return ar; }

    //MODOSITO METODUSOK (SETTER)

    void setAr(float ujAr) {
        if (ujAr >= 0) {
            ar = ujAr;
        }
        else {
            cout << "Hiba: Az ar nem lehet negatív!" << endl;
        }
    }
    
    void setKategoria(string ujKategoria) {
        this->kategoria = ujKategoria; //shortcut
    }

    void setLejarat(unsigned int ujLejarat) {
        this->lejarat = ujLejarat;
    }

    void setTermeknev(string ujTermeknev) {
        this->termeknev = ujTermeknev;
    }

    //binaris kiiratashoz kell xd
    void binariskiir(ofstream& bfajl) const {
        // Bináris fájlba írásnál a stringek méretét is el kell menteni, különben nem tudjuk visszaolvasni!
        size_t katMeret = kategoria.size();
        bfajl.write(reinterpret_cast<const char*>(&katMeret), sizeof(katMeret));
        bfajl.write(kategoria.c_str(), katMeret);

        size_t nevMeret = termeknev.size();
        bfajl.write(reinterpret_cast<const char*>(&nevMeret), sizeof(nevMeret));
        bfajl.write(termeknev.c_str(), nevMeret);

        // A számokat egyszerûen memóriacím alapján írjuk ki
        bfajl.write(reinterpret_cast<const char*>(&lejarat), sizeof(lejarat));
        bfajl.write(reinterpret_cast<const char*>(&ar), sizeof(ar));
    }

    
};

class Zoldseg : public Product {
private:
    unsigned int darabszam;

public:
    Zoldseg(string kategoria, string termeknev, unsigned int lejarat, float ar, unsigned int darabszam) : Product(kategoria,termeknev, lejarat, ar) //orokoltetes : utan
    {
        this->darabszam = darabszam; //setter shortcut
    }

    //getter a kiiratashoz kell
    unsigned int getDarabszam() const { return darabszam; }

    void kiir() { 
        Product::kiir();
        cout << "| Darabszam: " << darabszam << " db" << endl;
    }

};


class Tejtermek : public Product {
private:
    unsigned int darabszam;

public:
    Tejtermek(string kategoria,string termeknev, unsigned int lejarat, float ar, unsigned int darabszam) : Product(kategoria,termeknev, lejarat, ar) {
        this->darabszam = darabszam;
    }

    void kiir() {
        Product::kiir();
        cout << "| Darabszam: " << darabszam << " db" << endl;
    }

    unsigned int getDarabszam() const { return darabszam; }
};

int main()
{
    //statikus példányosítás (stack memory)
    Product termek1("elelmiszer","Parizsi", 20260516,500);
    Product termek2;


    //getteres kiiratas
    cout << "Kategoria: " << termek1.getKategoria() << endl;
    //setter hasznalat
    termek1.setAr(900.0);

    //Dinamikus példányosítás (manualis memory)
    Product* p1 = new Product("elelmiszer", "Parizsi", 10, 1500.5);
    Product* p2 = new Product();

    //Dinamikusat torolni kell a memory leak miatt
    delete p1;
    delete p2;




    //amit a feladat elvar (bemutatni hogy mukodik minden):

    cout << "------------------" << endl;

    Product termekPelda;
    termekPelda.setKategoria("Elelmiszer");
    termekPelda.setTermeknev("Parizsi");
    termekPelda.setAr(50000);
    termekPelda.setLejarat(20260516);

    cout << termekPelda.getKategoria() << endl;
    cout << termekPelda.getAr() << endl;
    cout << termekPelda.getLejarat() << endl;

    Zoldseg repa("Zoldseg","repa", 20260516, 400, 20);

    cout << "------------------" << endl;

    termekPelda.kiir();
    termekPelda.akcio(20260514);

    //kiiratas txt-be
    /*
    ofstream fajl("termek_kimenet.txt"); //letrehoz/megnyitja

    if (fajl.is_open())
    {
        fajl << "=== TERMEKEK ADATAI ===" << endl;

        fajl << "Kategoria: " << repa.getKategoria()
            << "| Lejarat: " << repa.getLejarat()
            << "| Ar: " << repa.getAr() << "Ft"
            << "| Darabszam: " << repa.getDarabszam() << "db" << endl;
    

    fajl.close();

    cout << "\nSikeresen letrehoztam a 'termekek_kimenet.txt' fajlt" << endl;

    }
    else {
        cout << "\nHiba: Nem sikerult letrehozni a fajlt" << endl;
    }
    */



    //2. feladat allomanykezelo

    //beolvaso

    vector<Product> termekekLista;
    string bemenetiFajlnev = "raktar.txt";

    cout << "----- ALLOMANYKEZELO ALKALMAZAS -----" << endl;

    //beolvasas hibakezelessel

    try {
        ifstream beolvaso(bemenetiFajlnev);

        if (!beolvaso.is_open()) {
            throw runtime_error("Hiba: Nem talalhato a bemeneti allomany");
        }

        string sor;
        while (getline(beolvaso, sor)) {
            // 1. VÉDELEM: Ha üres a sor, ugorjuk át (így nem omlik össze a stoi/stof)
            if (sor.empty()) {
                continue;
            }

            // 2. DARABOLÁS STRINGSTREAM NÉLKÜL
            size_t pos1 = sor.find(',');
            size_t pos2 = sor.find(',', pos1 + 1);
            size_t pos3 = sor.find(',', pos2 + 1);

            // Ha hiányzik vesszõ (hibás a sor formátuma), ugorjuk át
            if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) {
                continue;
            }

            string beKategoria = sor.substr(0, pos1);
            string beTermeknev = sor.substr(pos1 + 1, pos2 - pos1 - 1);
            string beLejaratStr = sor.substr(pos2 + 1, pos3 - pos2 - 1);
            string beArStr = sor.substr(pos3 + 1);

            // Szöveget számmá
            unsigned int beLejarat = stoi(beLejaratStr);
            float beAr = stof(beArStr);

            // Objektum létrehozása és vektorba rakás
            Product ujTermek(beKategoria, beTermeknev, beLejarat, beAr);
            termekekLista.push_back(ujTermek);
        }
        beolvaso.close();
        cout << "Sikeresen beolvasta, " << termekekLista.size() << " db termek van a listaban" << endl;
    }
    catch (const exception& e) {
        cerr << "Kivetel tortent a beolvasaskor: " << e.what() << endl;
        return 1;
    }



    // ------2. INDEX / KATEGORIA SZERINTI VALASZTAS

    vector<Product> kivalasztottTermekek;
    string valasztas;
    cout << "\nSzeretnel szurni a termekekre? (index / kategoria / nem): ";
    cin >> valasztas;

    try {
        if (valasztas == "index") {
            int index;
            cout << "Add meg a termek indexet (0-" << termekekLista.size() - 1 << "): ";
            cin >> index;

            //hibakezeles
            if (index < 0 || index >= termekekLista.size()) {
                throw out_of_range("Hiba: Érvénytelen index!");
            }

            //Hozzadjuk a kivalasztott listahoz
            kivalasztottTermekek.push_back(termekekLista[index]);
            cout << "Termek Kivalasztva: " << termekekLista[index].getTermeknev() << endl;
        }
        else if (valasztas == "kategoria") {
            string keresettKat;
            cout << "Add meg a kategoriat (pl.Tejtermek): ";
            cin >> keresettKat;

            //megnezzuk az osszes termeket es ha egyezik akkor elmentjuk
            for (const auto& termek : termekekLista) {
                if (termek.getKategoria() == keresettKat) {
                    kivalasztottTermekek.push_back(termek);
                }
            }
            cout << kivalasztottTermekek.size() << " db termek kivalasztva ebbol a kategoriabol." << endl;
        }
        else {
            //nincs szûrés
            kivalasztottTermekek = termekekLista;
        }
    }
    catch (const exception& e) {
        cerr << "Kivetel torent: " << e.what() << endl;
        return 1;
    }

    // ----- 3 KIIRAS (SZOVEGES VAGY BINARISBA)


    if (!kivalasztottTermekek.empty()) {
        try {
            string kimenetiFajlnev = "kivalasztott_" + bemenetiFajlnev;
            string mod;
            cout << "\nMilyen formatumba szeretned menteni? (txt / binaris): ";
            cin >> mod;

            if (mod == "binaris") {
                // Bináris mentés
                ofstream kimenet(kimenetiFajlnev + ".bin", ios::binary);
                if (!kimenet.is_open()) throw runtime_error("Nem lehet megnyitni a kimeneti binaris fajlt");

                for (const auto& termek : kivalasztottTermekek) {
                    termek.binariskiir(kimenet);
                }
                kimenet.close();
                cout << "Sikeresen mentettem a BINARIS formatumba a " << kimenetiFajlnev << ".bin fajlba" << endl;
            }
            else if (mod == "txt") {
                ofstream kimenet(kimenetiFajlnev);
                if (!kimenet.is_open()) throw runtime_error("Nem lehet megnyitni a kimeneti txt fajlt");

                for (const auto& termek : kivalasztottTermekek) {
                    termek.kiir(kimenet);
                    kimenet << endl; // Sortörés kell a txt fájlba
                }
                kimenet.close();
                cout << "Sikeresen mentettem a SZOVEGES formatumba a " << kimenetiFajlnev << " fajlba" << endl;
            }
            else {
                cout << "Ismeretlen formatum, nem tortent mentes." << endl;
            }
        }
        catch (const exception& e) {
            cerr << "Kivetel tortent a menteskor: " << e.what() << endl;
        }
    }
    else {
        cout << "Nincs mit kiirni (ures a kivalasztott lista)." << endl;
    }
    return 0;
}