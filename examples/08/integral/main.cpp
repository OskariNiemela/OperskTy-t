#include <iostream>
#include <cmath>

using namespace std;


double polynomi(double x);


// decltype-käskyllä saadaan selville minkä tahansa
// muuttujan tai funktion tietotyyppi.
using Func = decltype(&polynomi);


// Func-tyyppi edellä olisi voitu määritellä myös ilman
// decltype-käskyä C?+:n tyyppimäärittelysyntaksilla (osoitin
// funktioon, joka palauttaa double:n ja saa parametrinaan
// doublen):
//
//    using Func = double(*)(double);
//
// decltype on kuitenkin selvästi helppotajuisempi, jos on
// olemassa jokin funktio, jota voidaan käyttää decltype:n
// "parametrina".  decltype ei ole funktio, vaan suora käsky
// kääntäjälle, joka ratkaistaan jo käännösaikana.


// integroi:
// Laskee funktion «f» integraalille välillä «vasen»–«oikea» likiarvon
// nk. suorakulmiomenetelmällä (tai jossain yhteyksissä sitä on myös
// kutsuttu keskipistesäännöksi).  Parametri «osavaleja» määrää,
// kuinka moneen tasalevyiseen osaan integroitava väli jaetaan,
// eli kuinka monen eri suorakaiteen pinta-alojen summana kokonais-
// integraali saadaan.
double integroi(Func f, double vasen, double oikea, int osavaleja = 500) {
    double osavalin_pituus = (oikea - vasen) / osavaleja;
    double summa = 0.0;

    double keskipiste = vasen + osavalin_pituus / 2;
    while ( keskipiste < oikea ) {
        summa += f(keskipiste);  // Sama kuin: summa = summa + f(keskipiste);
        keskipiste += osavalin_pituus;
    }

    return summa * osavalin_pituus;
}


int main() {
    // Huomaa, kuinka seuraavissa kutsuissa integroi-funktiolle
    // ei anneta parametrina funkioiden sin, cos, sqrt ja polynomi
    // paluuarvoa, vaan funktio itsessään. Siis em. funktioiden
    // perässä ei ole ()-paria, joka on C++:ssa operaattori, joka
    // saa aikaan funktion kutsumisen.
    cout << integroi(sin,      0,  2) << endl;
    cout << integroi(cos,      0,  2) << endl;
    cout << integroi(sqrt,     0,  2) << endl;
    cout << integroi(polynomi, 0,  2) << endl;
}


double polynomi(double x) {
    return 2 * x * x - 3 * x + 1;
}
