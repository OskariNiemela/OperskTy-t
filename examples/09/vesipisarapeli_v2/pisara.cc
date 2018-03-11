/* Moduuli: Pisara / tiedosto: pisara.cpp
 */

#include "pisara.hh"
#include "roiske.hh"
#include "pelilauta.hh"
#include <cstdlib>
#include <iostream>

Pisara::Pisara(int x, int y, int vetta, Pelilauta* lauta ):
    x_(x), y_(y), vetta_(vetta), lauta_(lauta)
{}

void Pisara::lisaaVetta(std::vector<Roiske>& uudetRoiskeet)
{
    ++vetta_;

    if( vetta_ > MAKSIMI_TILAVUUS )
    {
        std::cout << x_+1 << ',' << y_+1 << " poksahtaa!\n";
        vetta_ = 0;

        // Muodostetaan 4 roisketta, jotka lähtevät eri suuntiin
        uudetRoiskeet.push_back(Roiske(x_, y_, 1, YLOS));
        uudetRoiskeet.push_back(Roiske(x_, y_, 1, ALAS));
        uudetRoiskeet.push_back(Roiske(x_, y_, 1, OIKEALLE));
        uudetRoiskeet.push_back(Roiske(x_, y_, 1, VASEMMALLE));

        // Pisara poistaa laudalta osoittimen itseensä. Tällöin dynaamisesti varatun
        // olion viitelaskuri menee nollaan ja automaattiosoitin tuhoaa olion.
        // Tämän on siis syytä olla metodin viimeisenä käskynä.
        lauta_->poistaPisara(x_, y_);
    }
}

void Pisara::tulosta( std::ostream& virta )
{
    // MERKIT-taulukossa on pisaran piirrosmerkit talletettuna vesimäärää
    // vastaaville indekseille, joten oikeaan piirrosmerkkiin päästään
    // käsiksi kätevästi.
    virta << MERKIT[ vetta_ ];
}
