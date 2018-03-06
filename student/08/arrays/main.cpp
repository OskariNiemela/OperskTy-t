#include "array_operations.hh"
#include <iostream>
#include <algorithm>

using namespace std;

const int ALKIOIDEN_MAARA = 30;

int main() {

    // Määritellään 30-alkioinen taulukko, jossa on alussa 4 nollasta 
    // poikkeavaa arvoa, ja lopputaulukko täynnä nollia.
    int taulukko[ALKIOIDEN_MAARA] = { 1, 3, 6, 9 };

    // Esimerkki C-taulukon käsittelemisestä algorithm-kirjaston avulla
    sort(taulukko, taulukko + ALKIOIDEN_MAARA);

    for(int* kohta = taulukko; kohta < taulukko + ALKIOIDEN_MAARA; ++kohta){
        cout << *kohta << " ";
    }
    cout << endl;

    // a-kohta
    cout << suurin_v1(taulukko, ALKIOIDEN_MAARA) << endl;
    cout << suurin_v2(taulukko, taulukko + ALKIOIDEN_MAARA) << endl;

    // b-kohta
    int kohdetaulukko[ALKIOIDEN_MAARA];
    kopioi(taulukko, taulukko + ALKIOIDEN_MAARA, kohdetaulukko);

    for(int* kohta = kohdetaulukko; kohta < kohdetaulukko + ALKIOIDEN_MAARA; ++kohta){
        cout << *kohta << " ";
    }
    cout << endl;

    // c-kohta
    kaanna_takaperin(taulukko, taulukko + ALKIOIDEN_MAARA);

    for(int* kohta = taulukko; kohta < taulukko + ALKIOIDEN_MAARA; ++kohta){
        cout << *kohta << " ";
    }
    cout << endl;
}
