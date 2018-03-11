/* Moduuli: Pelilauta / tiedosto: pelilauta.hh
 * Hallinnoi pelilaudalla olevia vesipisaroita ja roiskeita.
 */

#ifndef PELILAUTA_HH
#define PELILAUTA_HH

#include "pisara.hh"
#include "roiske.hh"
#include <iostream>
#include <vector>
#include <memory>

const int KOKO = 12;

class Pelilauta
{
public:
    // Rakentaja alustaa pelilaudalle satunnaisiin kohtiin vesipisaroita
    Pelilauta();

    // Tulostaa pelilaudan annettuun virtaan animoiden roiskeiden lennon
    void tulosta(std::ostream& virta);

    // Tarkastaa, onko peli loppunut, eli onko pelilauta tyhjä pisaroista
    bool onkoTyhja();

    // Pudottaa yhden tipan vettä tiettyyn kohtaan pelilaudalla
    void lisaaVetta(int x, int y);

    // Pisaran pitää pystyä tuhoutuessaan poistamaan itsensä laudalta.
    void poistaPisara(int x, int y);

private:
    std::vector< std::vector< std::shared_ptr<Pisara> > > lauta_;
    std::vector< Roiske > roiskeet_;

    // Siirtää jokaista laudalla olevaa roisketta yhden ruudun eteenpäin
    void siirraRoiskeita();

    // Tulostusmetodin käyttämä apumetodi
    char pisarattomanRuudunTulostusmerkki(int x, int y);
};

#endif // PELILAUTA_HH
