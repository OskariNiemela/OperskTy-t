#ifndef RUUTU_HH
#define RUUTU_HH

#include <vector>
#include <iostream>


const int MAKSIMI_TILAVUUS = 4;
const char MERKIT[] = {' ', '.', 'o', 'O', '@'};

class Ruutu;
using Lauta = std::vector< std::vector< Ruutu > >;

class Ruutu
{
 public:

   // sijainti ja vesimäärä parametrina rakentajalle
   Ruutu( int x, int y, int tippoja, Lauta* );
   ~Ruutu();

   // lisää vettä ruutuun, käyttää poksahdusfunktiota jos ruudun tilavuus ei riitä.
   void lisaaVetta();

   // kertoo onko ruudussa vettä. jotta tiedetään lisätäänkö ruutuun tippa vai meneekö tippa ohi
   bool onkoVetta();

   // tulostaa ruudun annettuun virtaan vesimäärän perusteella
   void tulosta( std::ostream& );

 private:

   // lisää vettä joka suuntaan ja katoaa itse
   void poksahda();

   // Sijainti ja vesimäärä
   int x_;
   int y_;
   int tippoja_;

   // Osoitin lautaan, jolla vesipisara sijaitsee
   Lauta* lauta_;

};

#endif // RUUTU_HH
