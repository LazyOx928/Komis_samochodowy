#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Samochod {
public:
    Samochod(string marka, string model, string nrRejestracyjny) : marka(marka), model(model), nrRejestracyjny(nrRejestracyjny), dostepny(true) {}

    string getMarka() const { return marka; }
    string getModel() const { return model; }
    string getNrRejestracyjny() const { return nrRejestracyjny; }
    bool isDostepny() const { return dostepny; }

    void setDostepny(bool dostepny) { this->dostepny = dostepny; }

private:
    string marka;
    string model;
    string nrRejestracyjny;
    bool dostepny;
};

class Wypozyczalnia {
public:
    Wypozyczalnia() {
        wczytajZPliku("samochody.txt");
    }

    void dodajSamochod(const Samochod& samochod) {
        samochody.push_back(samochod);
        zapiszDoPliku("samochody.txt");
    }

    void wyswietlDostepneSamochody() const {
        cout << "Dostepne samochody:" << endl;
        for (const Samochod& samochod : samochody) {
            if (samochod.isDostepny()) {
                cout << " - " << samochod.getMarka() << " " << samochod.getModel() << " (" << samochod.getNrRejestracyjny() << ")" << endl;
            }
        }
    }

    void wypozyczSamochod(string nrRejestracyjny) {
        for (Samochod& samochod : samochody) {
            if (samochod.getNrRejestracyjny() == nrRejestracyjny) {
                if (samochod.isDostepny()) {
                    samochod.setDostepny(false);
                    cout << "Samochod " << samochod.getMarka() << " " << samochod.getModel() << " (" << samochod.getNrRejestracyjny() << ") zostal wypozyczony." << endl;
                    zapiszDoPliku("samochody.txt");
                    return;
                }
                else {
                    cout << "Samochod " << samochod.getMarka() << " " << samochod.getModel() << " (" << samochod.getNrRejestracyjny() << ") jest juz wypozyczony." << endl;
                    return;
                }
            }
        }

        cout << "Samochod o numerze rejestracyjnym " << nrRejestracyjny << " nie zostal znaleziony." << endl;
    }

    void oddajSamochod(string nrRejestracyjny) {
        for (Samochod& samochod : samochody) {
            if (samochod.getNrRejestracyjny() == nrRejestracyjny) {
                samochod.setDostepny(true);
                cout << "Samochod " << samochod.getMarka() << " " << samochod.getModel() << " (" << samochod.getNrRejestracyjny() << ") zostal zwrocony." << endl;
                zapiszDoPliku("samochody.txt");
                return;
            }
        }

        cout << "Samochod o numerze rejestracyjnym " << nrRejestracyjny << " nie zostal znaleziony." << endl;
    }

private:
    vector<Samochod> samochody;

    void zapiszDoPliku(string nazwaPliku) const {
        ofstream plik(nazwaPliku);
        if (!plik.is_open()) {
            cerr << "Blad: Nie mozna otworzyc pliku do zapisu." << endl;
            return;
        }

        for (const Samochod& samochod : samochody) {
            plik << samochod.getMarka() << " " << samochod.getModel() << " " << samochod.getNrRejestracyjny() << " " << (samochod.isDostepny() ? "1" : "0") << endl;
        }

        plik.close();
    }

    void wczytajZPliku(string nazwaPliku) {
        ifstream plik(nazwaPliku);
        if (!plik.is_open()) {
            cerr << "Blad: Nie mozna otworzyc pliku do odczytu";
        }

        string marka, model, nrRejestracyjny;
        bool dostepny;
        while (plik >> marka >> model >> nrRejestracyjny >> dostepny) {
            samochody.push_back(Samochod(marka, model, nrRejestracyjny));
        }

        plik.close();
    }
};

int main() {
    Wypozyczalnia wypozyczalnia;

    int wybor;
    do {
        cout << "1. Dodaj samochod" << endl;
        cout << "2. Wyswietl dostepne samochody" << endl;
        cout << "3. Wypozycz samochod" << endl;
        cout << "4. Oddaj samochod" << endl;
        cout << "0. Wyjscie z programu" << endl;

        cin >> wybor;

        if (wybor == 1) {
            // Dodanie nowego samochodu
            string marka, model, nrRejestracyjny;
            cout << "Podaj marke: ";
            cin >> marka;
            cout << "Podaj model: ";
            cin >> model;
            cout << "Podaj numer rejestracyjny: ";
            cin >> nrRejestracyjny;
            wypozyczalnia.dodajSamochod(Samochod(marka, model, nrRejestracyjny));

        }
        else if (wybor == 2) {
            // Wyświetlenie dostępnych samochodów
            wypozyczalnia.wyswietlDostepneSamochody();

        }
        else if (wybor == 3) {
            // Wypożyczenie samochodu
            string nrRejestracyjny;
            cout << "Podaj numer rejestracyjny samochodu, ktory chcesz wypozyczyc: ";
            cin >> nrRejestracyjny;
            wypozyczalnia.wypozyczSamochod(nrRejestracyjny);

        }
        else if (wybor == 4) {
            // Zwrot samochodu
            string nrRejestracyjny;
            cout << "Podaj numer rejestracyjny samochodu, ktory chcesz zwrocic: ";
            cin >> nrRejestracyjny;
            wypozyczalnia.oddajSamochod(nrRejestracyjny);
        }
        else if (wybor == 0) {
            cout << "Wyjscie z programu." << endl;
        }
        else {
            cout << "Nieprawidlowy wybor." << endl;
        }
    } while (wybor != 0);

    return 0;
}
