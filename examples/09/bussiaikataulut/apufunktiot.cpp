// Lähdekooditiedosto: apufunktiot.cpp
#include <iostream>
#include <string>

using namespace std;

namespace {  //***
  bool onko_numeromerkkijono(const string& mjono) {
     const string NUMEROMERKIT = "0123456789";

     // Tyhjä merkkijono ei esitä numeroa.
     if ( mjono.length() == 0 ) {
        return false;
     }

     string::size_type tutkittava_indeksi = 0;

     // Jos merkkijonossa on useampia kuin yksi merkki ja
     // ensimmäinen merkki on miinus, kyseessä saattaa olla
     // negatiivinen luku: hypätään miinusmerkki yli.
     if ( mjono.length() > 1 and mjono.at(0) == '-' ) {
        ++tutkittava_indeksi;
     }

     // Käydään loput merkit läpi ja varmistetaan, että
     // kaikki ovat numeromerkkejä.
     while ( tutkittava_indeksi < mjono.length() ) {
        char tutkittava_merkki = mjono.at(tutkittava_indeksi);
        if ( NUMEROMERKIT.find(tutkittava_merkki)
                 == string::npos ) {
           return false;
        }
        ++tutkittava_indeksi;
     }
     return true;
  }
}

bool string_intiksi(const string& lahtoarvo, int& tulos) {
   if ( not onko_numeromerkkijono(lahtoarvo) ) {
      return false;
   } else {
      tulos = stoi(lahtoarvo);
      return true;
   }
}

bool lue_kokonaisluku(const string& kehote, int& tulos) {
   cout << kehote;
   string lukustr = "";
   getline(cin, lukustr);

   if ( not string_intiksi(lukustr, tulos) ) {
      return false;
   } else {
      return true;
   }
}
