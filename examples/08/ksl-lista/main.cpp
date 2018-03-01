#include "ksl-lista.hh"

// Ei-kattava testipääohjelma
int main() {
    KSL_lista testilista;

    testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(5);  testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(2);  testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(8);  testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(0);  testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(10); testilista.tulosta();

    testilista.lisaa_numerojarjestykseen(10); testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(0);  testilista.tulosta();

    testilista.lisaa_numerojarjestykseen(4);  testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(6);  testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(1);  testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(9);  testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(1);  testilista.tulosta();
    testilista.lisaa_numerojarjestykseen(9);  testilista.tulosta();

    testilista.tulosta_takaperin();

    testilista.poista_arvo(1);  testilista.tulosta();
    testilista.poista_arvo(9);  testilista.tulosta();
    testilista.poista_arvo(0);  testilista.tulosta();
    testilista.poista_arvo(10); testilista.tulosta();
    testilista.poista_arvo(5);  testilista.tulosta();
}
