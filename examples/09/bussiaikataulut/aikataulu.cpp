// Lähdekooditiedosto: aikataulu.cpp
#include "aika.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int TULOSTETTAVIEN_MAARA = 3;

using Aikataulu = map<int, vector<Aika>>;

void tulosta_seuraavat_lahtoajat(const Aikataulu& aikataulu,
                                 const Aika& nyt, int bus);
int main() {
   Aikataulu aikataulu = {
      // first: bussin numero, second: vektori lähtöaikoja
      {  1,  {{"06.00"}, {"09.00"}, {"12.00"}, {"21.00"}} },
      { 14,  {{"10.26"}, {"16.26"}, {"22.26"}} },
      { 17,  {{"11.02"}} },
      { 25,  {{"8.41"}, {"20.41"}} },
   };

   // Kovin yksinkertainen käyttöliittymä:
   // ei lopetusmahdollisuutta laisinkaan.
   while ( true ) {
      Aika klo_nyt;
      while ( not klo_nyt.kysy("Kellonaika: ") ) {
          cout << "Virheellinen kellonaika!" << endl;
      }
      int bussi = 0;
      while ( not lue_kokonaisluku("Bussin nro: ", bussi) ) {
          cout << "Virheellinen numero!" << endl;
      }
      tulosta_seuraavat_lahtoajat(aikataulu, klo_nyt, bussi);
   }
}
void tulosta_seuraavat_lahtoajat(const Aikataulu& aikataulu,
                                 const Aika& nyt, int bus) {
   Aikataulu::const_iterator iter = aikataulu.find(bus);

   if ( iter == aikataulu.end() ) {
      cout << "Tuntematon bussi " << bus << "!" << endl;
      return;
   } else if ( iter->second.size() == 0 ) {
      cout << "Bussilla " << bus << " ei lahtoja!" << endl;
      return;
   }

   const vector<Aika>& aikavek = iter->second;  //***

   vector<Aika>::size_type tutkittava = 0;
   while ( tutkittava < aikavek.size() ) {
      if ( nyt.pienempi_yhtasuuri(aikavek.at(tutkittava)) ) {
         break;
      }
      ++tutkittava;
   }

   cout << "Bussin " << bus << " seuraavat lahdot:" << endl;

   int montako_tulostettu = 0;
   while ( montako_tulostettu < TULOSTETTAVIEN_MAARA ) {
      if ( tutkittava >= aikavek.size() ) {
         tutkittava = 0;
      }

      aikavek.at(tutkittava).tulosta();

      ++montako_tulostettu;
      ++tutkittava;
   }
}
