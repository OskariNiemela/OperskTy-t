#include "drop.hh"
#include "splash.hh"
#include "gameengine.hh"
#include <cstdlib>
#include <iostream>

Drop::Drop(int x, int y, int waterAmount, GameEngine* engine ):
    x_(x),
    y_(y),
    waterAmount_(waterAmount),
    engine_(engine)
{}

void Drop::addWater(std::vector<Splash>& createdSplashes)
{
    ++waterAmount_;

    if( waterAmount_ > MAX_CAPACITY )
    {
        std::cout << x_+1 << ',' << y_+1 << " poksahtaa!" << std::endl;
        waterAmount_ = 0;

        // Muodostetaan 4 roisketta, jotka lähtevät eri suuntiin
        createdSplashes.push_back(Splash(x_, y_, UP));
        createdSplashes.push_back(Splash(x_, y_, DOWN));
        createdSplashes.push_back(Splash(x_, y_, RIGHT));
        createdSplashes.push_back(Splash(x_, y_, LEFT));

        // Pisara poistaa laudalta osoittimen itseensä. Tällöin dynaamisesti varatun
        // olion viitelaskuri menee nollaan ja automaattiosoitin tuhoaa olion.
        // Tämän on siis syytä olla metodin viimeisenä käskynä.
        engine_->removeDrop(x_, y_);
    }
}

void Drop::print( std::ostream& stream )
{
    // MERKIT-taulukossa on pisaran piirrosmerkit talletettuna vesimäärää
    // vastaaville indekseille, joten oikeaan piirrosmerkkiin päästään
    // käsiksi kätevästi.
    stream << CHARACTERS[ waterAmount_ ];
}

int Drop::waterAmount() const
{
    return waterAmount_;
}

int Drop::getX() const
{
    return x_;
}

int Drop::getY() const
{
    return y_;
}
