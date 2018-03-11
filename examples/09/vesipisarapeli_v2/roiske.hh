/* Moduuli Roiske / tiedosto: roiske.hh
 * Sisältää yksittäisen roiskeen tiedot ja toiminnallisuuden.
 */

#ifndef ROISKE_HH
#define ROISKE_HH

#include "pisara.hh"

// Koska enum on kokonaislukutyyppi, jonka alkiot on numeroitu nollasta alkaen
// eli YLOS = 0, ALAS = 1, niin sen arvoja käyttäen pääsee käsiksi
// oikeisiin tietoihin SUUNTATIEDOT-taulukossa.
enum Suunta {YLOS, ALAS, OIKEALLE, VASEMMALLE};

struct Suuntainfo {
    int deltaX;
    int deltaY;
    char merkki;
};

const Suuntainfo SUUNTATIEDOT[] = { {  0, -1, '^' },
                                    {  0,  1, 'v' },
                                    {  1,  0, '>' },
                                    { -1,  0, '<' } };

class Roiske
{
public:
    Roiske(int x, int y, int vetta, Suunta tyyppi);

    // Apumetodit roiskeen tietojen tutkimiseen ulkopuolelta
    int annaX();
    int annaY();
    char annaTulostusmerkki();

    // Liikuttaa roisketta yhden pykälän eteenpäin pelilaudalla. Palauttaa
    // tiedon, onko roiske laudan ulkopuolella, eli pitääkö se poistaa.
    // (true = poistettava, false = ei poisteta)
    bool liiku();

private:
    int x_;  // Roiske voi mennä laudan reunan yli, joten sen koordinaatit
    int y_;  // voivat olla myös negatiivisia
    int vetta_;
    Suunta tyyppi_;
};

#endif // ROISKE_HH
