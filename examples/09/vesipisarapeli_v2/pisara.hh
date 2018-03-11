/* Moduuli: Pisara / tiedosto pisara.hh
 * Sisältää yksittäisen vesipisaran tiedot ja toiminnallisuuden.
 */

#ifndef PISARA_HH
#define PISARA_HH

#include <iostream>
#include <vector>
#include <memory>

class Roiske;
class Pelilauta;

const int MAKSIMI_TILAVUUS = 4;
const char MERKIT[] = {' ', '.', 'o', 'O', '@'};

class Pisara
{
public:
    Pisara(int x, int y, int vetta, Pelilauta* lauta);

    // Lisää vettä pisaraan. Jos maksimitilavuus tulee täyteen, pisara poksahtaa.
    // Paluuarvona mahdollisessa poksahduksessa syntyvät uudet roiskeoliot.
    void lisaaVetta(std::vector<Roiske>& mahdollisessaPoksahduksessaSyntyvatRoiskeet);

    // Tulostaa pisaran kokoa vastaavan merkin annettuun virtaan vesimäärän perusteella
    void tulosta( std::ostream& );

  private:
    // Pisaran sijainti laudalla ja vesimäärä
    int x_;
    int y_;
    int vetta_;

    // Osoitin pelilautaan, jolla vesipisara sijaitsee
    Pelilauta* lauta_;
};

#endif // PISARA_HH
