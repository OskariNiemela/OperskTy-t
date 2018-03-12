/* Moduuli: Roiske / tiedosto: roiske.cpp
 */

#include "roiske.hh"
#include "pelilauta.hh"

Roiske::Roiske(int x, int y, int vetta, Suunta suunta):
    x_(x), y_(y), vetta_(vetta), tyyppi_(suunta)
{
}

char Roiske::annaTulostusmerkki(){
    // Attribuutti tyyppi_ on enumin Roisketyyppi alkio. Sen arvot ovat
    // YLOS = 0, ALAS = 1, jne. Tässä indeksoidaan SUUNTATIEDOT-taulukkoa
    // roiskeen tyyppiä käyttäen, ja saadaan taulukosta oikea tulostusmerkki.
    return SUUNTATIEDOT[tyyppi_].merkki;
}

int Roiske::annaX(){
    return x_;
}

int Roiske::annaY(){
    return y_;
}

bool Roiske::liiku()
{
    // Päivitetään roiskeen sijainti SUUNTATIEDOT-taulukkosta löytyvillä
    // arvoilla.
    x_ += SUUNTATIEDOT[tyyppi_].deltaX;
    y_ += SUUNTATIEDOT[tyyppi_].deltaY;

    // Tarkastetaan, menikö roiske pois pelilaudalta, eli pitääkö se poistaa
    if(x_ < 0 or x_ >= KOKO or y_ < 0 or y_ >= KOKO) {
        return true;
    }
    return false;
}
