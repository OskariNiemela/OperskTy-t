#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

const string LOPETUS = "-";

void tulosta_hinnasto(const map<string, double>& hinnasto);
void tulosta_kuitti(const map<string, double>& hinnasto,
                    const map<string, int>& ostokset);

int main() {
    // first: tuote, second: hinta
    map<string, double> hinnasto = {
        { "maito",    1.05 },
        { "juusto",   4.95 },
        { "liima",    3.65 },
        { "pippuri",  2.10 },
        { "kerma",    1.65 },
        { "suklaa",   2.0  },
    };

    tulosta_hinnasto(hinnasto);

    // Ostosten lukeminen kannattaisi toteuttaa funktiona.
    map<string, int> ostokset;
    while ( true ) {
        cout << "Syota tuotenimi: ";
        string tuotenimi = "";
        getline(cin, tuotenimi);

        if ( tuotenimi == LOPETUS ) {
            break;
        }

        map<string, double>::iterator tuoteiter;
        tuoteiter = hinnasto.find(tuotenimi);
        if ( tuoteiter == hinnasto.end() ) {
            cout << "Tuntematon tuote!" << endl;
            continue;
        }

        // first: tuote, second: määrä
        map<string, int>::iterator ostositer;
        ostositer = ostokset.find(tuotenimi);
        if ( ostositer == ostokset.end() ) {
            ostokset.insert({ tuotenimi, 1 });
        } else {
            ++ostokset.at(tuotenimi);
        }
    }

    tulosta_kuitti(hinnasto, ostokset);
}


void tulosta_hinnasto(const map<string, double>& hinnasto) {
    cout << "Hinnasto:" << endl;
    // first: tuote  second: hinta
    for ( auto tuote : hinnasto ) {
        cout << left << setw(10)
             << tuote.first
             << right << setprecision(2) << fixed
             << tuote.second << endl;
    }
}


void tulosta_kuitti(const map<string, double>& hinnasto,
                    const map<string, int>& ostokset) {
    double kokonaissumma = 0.0;

    cout << "Kuitti:" << endl;

    // hinnasto:  first: tuote  second: hinta
    // ostokset:  first: tuote  second: määrä
    for ( auto ostos : ostokset ) {
        double hinta = ostos.second * hinnasto.at(ostos.first);
        cout << left << setw(3) << ostos.second
             << left << setw(10)
             << ostos.first
             << right << setprecision(2) << fixed
             << hinta
             << endl;
        kokonaissumma += hinta;
    }

    cout << "Loppusumma: "
         << setprecision(2) << fixed
         << kokonaissumma << endl;
}
