#include "splash.hh"
#include "gameengine.hh"

Splash::Splash(int x, int y, Direction type):
    x_(x),
    y_(y),
    type_(type)
{
}

char Splash::getChar(){
    // Attribuutti tyyppi_ on enumin Roisketyyppi alkio. Sen arvot ovat
    // YLOS = 0, ALAS = 1, jne. Tässä indeksoidaan SUUNTATIEDOT-taulukkoa
    // roiskeen tyyppiä käyttäen, ja saadaan taulukosta oikea tulostusmerkki.
    return DIRECTIONS[type_].character;
}

int Splash::getX(){
    return x_;
}

int Splash::getY(){
    return y_;
}

bool Splash::move()
{
    // Päivitetään roiskeen sijainti SUUNTATIEDOT-taulukkosta löytyvillä
    // arvoilla.
    x_ += DIRECTIONS[type_].deltaX;
    y_ += DIRECTIONS[type_].deltaY;

    // Tarkastetaan, menikö roiske pois pelilaudalta, eli pitääkö se poistaa
    if(x_ < 0 or x_ >= SIZE or y_ < 0 or y_ >= SIZE) {
        return true;
    }
    return false;
}
