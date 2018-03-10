// Moduuli: laskin / tiedosto: laskin.cpp
// Sisältää pääohjelman geometrialaskimelle.
#include "geometria.hh"
#include <iostream>

using namespace std;

int main() {
    double dimensio = 0.0;

    cout << "syota nelion sivun pituus: ";
    cin >> dimensio;
    cout << "ymparysmitta: " << nelion_ymparysmitta(dimensio) << endl
         << "pinta-ala:    " << nelion_pinta_ala(dimensio) << endl;

    cout << "syota ympyran sade: ";
    cin >> dimensio;
    cout << "ymparysmitta: " << ympyran_ymparysmitta(dimensio) << endl
         << "pinta-ala:    " << ympyran_pinta_ala(dimensio) << endl;
}
