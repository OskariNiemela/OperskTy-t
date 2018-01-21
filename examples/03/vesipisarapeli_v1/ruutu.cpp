#include <cstdlib>
#include <iostream>
#include "ruutu.hh"


Ruutu::Ruutu( int x, int y, int tippoja, Lauta* lauta ): x_(x), y_(y), tippoja_(tippoja), lauta_(lauta)
{
   // Ruutuun alustettiin liikaa vettä, se poksahtaa jo ennen kuin peli alkaa :)
   if( tippoja_ > MAKSIMI_TILAVUUS )
   {
      poksahda();
   }
}

Ruutu::~Ruutu() {}

void Ruutu::lisaaVetta()
{
   if( ++tippoja_ > MAKSIMI_TILAVUUS )
   {
      poksahda();
   } 
}

bool Ruutu::onkoVetta()
{
   return tippoja_;
}

void Ruutu::tulosta( std::ostream& virta )
{
    virta << MERKIT[ tippoja_ ];
}

void Ruutu::poksahda()
{
   std::cout << x_+1 << ',' << y_+1 << " poksahtaa!\n";
   tippoja_ = 0;

   // Lähes sama koodi kopioitu 4 kertaa. Voisko tämän tehdä fiksummin?
   for( unsigned int x = x_; x < lauta_->at(y_).size(); ++x )
   {
      if( lauta_->at(y_).at(x).onkoVetta() )
      {
         lauta_->at(y_).at(x).lisaaVetta();
         break;
      }
   }

   for( int x = x_; x >= 0; --x )
   {
      if( lauta_->at(y_).at(x).onkoVetta() )
      {
         lauta_->at(y_).at(x).lisaaVetta();
         break;
      }
   }

   for( unsigned int y = y_; y < lauta_->size(); ++y )
   {
      if( lauta_->at(y).at(x_).onkoVetta() )
      {
         lauta_->at(y).at(x_).lisaaVetta();
         break;
      }
   }

   for( int y = y_; y >= 0; --y )
   {
      if( lauta_->at(y).at(x_).onkoVetta() )
      {
         lauta_->at(y).at(x_).lisaaVetta();
         break;
      }
   }
}
