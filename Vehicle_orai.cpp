#include <iostream>
#include <string>
#include <fstream> //fajlkezeles
#include <cstdlib> // rand() fuggvenyhez kellene de lehet anelkul is jo 
#include <vector> //dinamikus lista
#include <stdexcept> //kivetelkezeles
#include <sstream> //sor darabolas (,)


using namespace std;

class Vehicle {
private:
    int loero;
    string marka;
    float fogyasztas;


public:
    Vehicle(int loero, const string& marka, float fogyasztas)
        : loero(loero), marka(marka), fogyasztas(fogyasztas)
    {
    }
    Vehicle() = default;

    virtual ~Vehicle() = default;


    int getLoero() const { return loero; }
    string getMarka() const { return marka; }
    float getFogyasztas() const { return fogyasztas; }

    void setLoero(int ujLoero) { this->loero = ujLoero; }
    void setMarka(string ujMarka) { this->marka = ujMarka; }
    void setFogyasztas(float ujFogyasztas) { this->fogyasztas = ujFogyasztas; }

    virtual void kiir(ostream& kimenet = cout) const{
        kimenet << loero << "," << marka << "," << fogyasztas << endl;
    }

    friend ostream& operator<<(ostream& os, const Vehicle& v) {
        v.kiir(os);
        return os;
    }

    void tuning() {
        float rand_factor = static_cast<float>(rand()) / RAND_MAX;
        float loero_szazalek = 7.0f + (rand_factor * 8.0f);

        float fogyasztas_szazalek = 3.0f + (rand_factor * 3.0f);

        this->loero = static_cast<int>(this->loero * (1.0f + (loero_szazalek / 100.0f)));
        this->fogyasztas = this->fogyasztas * (1.0f + (fogyasztas_szazalek / 100.0f));
    }





};


class Mercedes : public Vehicle {
private:
    bool amg;
public:

    Mercedes(int loero, string marka, float fogyasztas,bool amg) : Vehicle(loero,marka,fogyasztas)
    {
        this->amg = amg;
    }

    bool getAmg() const { return amg; }

    void kiir() {
        Vehicle::kiir();
        cout << "| AMG sajat: " << amg << endl;
    }

};



int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    Vehicle auto1(100, "Toyota", 6.5);
    auto1.kiir();
    auto1.tuning();
    auto1.kiir();

    //statik
    Vehicle statikusAuto(120, "Ford", 6.5);
    Mercedes statikusMerci(350, "Mercedes", 11.2, true);

    //statik metodusai
    cout << "Alap allapot:" << endl;
    statikusAuto.kiir();
    statikusMerci.kiir();

    cout << "\nTuningolas statikus auton..." << endl;
    statikusAuto.tuning();
    statikusAuto.kiir();

    //dinamikus

    Vehicle* dinamikusAuto = new Vehicle(150, "Audi", 7.0);
    Mercedes* dinamikusMerci = new Mercedes(510, "Mercedes", 14.5, true);

    cout << "Alap allapot:" << endl;
    dinamikusAuto->kiir();
    dinamikusMerci->kiir();

    cout << "\nGetterek es Setterek tesztelese dinamikus auton..." << endl;
    cout << "Eredeti loero: " << dinamikusAuto->getLoero() << endl;
    dinamikusAuto->setLoero(160);
    cout << "Beallitott uj loero: " << dinamikusAuto->getLoero() << endl;

    cout << "\nTuningolas dinamikus auton..." << endl;
    dinamikusAuto->tuning();
    dinamikusAuto->kiir();


    delete dinamikusAuto;
    delete dinamikusMerci;






    //kiiras

    // 1. Objektumok létrehozása
    Vehicle auto1(120, "Ford", 6.5);
    Mercedes auto2(350, "Mercedes", 11.2, true);

    // 2. Fájl megnyitása írásra
    // Létrehozza a "jarmuvek.txt" fájlt, vagy felülírja, ha már létezik
    ofstream kimenetiFajl("jarmuvek.txt");

    // 3. Ellenõrzés, hogy sikerült-e megnyitni a fájlt
    if (kimenetiFajl.is_open()) {

        // 4. Objektumok kiíratása a fájlba a most megírt << operátorral
        kimenetiFajl << auto1 << "\n";
        kimenetiFajl << auto2 << "\n";

        // 5. Fájl lezárása (Kötelezõ lépés a memóriaszivárgás és adatvesztés elkerülésére!)
        kimenetiFajl.close();

        cout << "Sikeresen kiirtuk az adatokat a jarmuvek.txt fajlba!" << endl;
    }
    else {
        cerr << "Hiba tortent a fajl megnyitasakor!" << endl;
    }





    return 0;
}

