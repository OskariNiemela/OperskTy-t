#ifndef SPLASH_HH
#define SPLASH_HH

#include "drop.hh"

// Koska enum on kokonaislukutyyppi, jonka alkiot on numeroitu nollasta alkaen
// eli YLOS = 0, ALAS = 1, niin sen arvoja käyttäen pääsee käsiksi
// oikeisiin tietoihin SUUNTATIEDOT-taulukossa.
enum Direction {UP, DOWN, RIGHT, LEFT};

struct DirectionInfo {
    int deltaX;
    int deltaY;
    char character;
};

const DirectionInfo DIRECTIONS[] = { {  0, -1, '^' },
                                     {  0,  1, 'v' },
                                     {  1,  0, '>' },
                                     { -1,  0, '<' } };

class Splash
{
public:
    Splash(int x, int y, Direction type);

    // Apumetodit roiskeen tietojen tutkimiseen ulkopuolelta
    int getX();
    int getY();
    char getChar();

    // Liikuttaa roisketta yhden pykälän eteenpäin pelilaudalla. Palauttaa
    // tiedon, onko roiske laudan ulkopuolella, eli pitääkö se poistaa.
    // (true = poistettava, false = ei poisteta)
    bool move();

private:
    int x_;  // Roiske voi mennä laudan reunan yli, joten sen koordinaatit
    int y_;  // voivat olla myös negatiivisia

    Direction type_;
};

#endif // SPLASH_HH
