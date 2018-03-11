// Lähdekooditiedosto: aika.cpp
#include "aika.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

Aika::Aika(const string& aika) {
   aseta(aika);  //***
}

bool Aika::aseta(int tunti, int minuutti) {
   if ( tunti < 0 or tunti > 23 ) {
      return false;
   } else if ( minuutti < 0 or minuutti > 59  ) {
      return false;
   } else {
      tunti_ = tunti;
      min_ = minuutti;
      return true;
   }
}

bool Aika::aseta(const string& ttmm) {
   string::size_type pisteind = 0;

   pisteind = ttmm.find('.');

   if ( pisteind == string::npos ) {
      return false;
   }

   int tt = 0;  // apumuuttuja tuntiarvon tallettamiseen
   int mm = 0;  // apumuuttuja minuuttiarvolle

   if ( not string_intiksi(ttmm.substr(0, pisteind), tt) ) {
      return false;
   }

   if ( not string_intiksi(ttmm.substr(pisteind + 1), mm) ) {
      return false;
   }

   return aseta(tt, mm);
}

bool Aika::kysy(const string& kehote) {
   cout << kehote;
   string rivi = "";
   getline(cin, rivi);

   return aseta(rivi);
}

bool Aika::pienempi_yhtasuuri(const Aika& vertailtava) const {
   if ( tunti_ < vertailtava.tunti_ ) {
      return true;
   } else if ( tunti_ == vertailtava.tunti_
                 and min_ <= vertailtava.min_ ) {
      return true;
   } else {
      return false;
   }
}

void Aika::tulosta() const {
   cout << setw(2) << right << setfill('0') << tunti_
        << "."
        << setw(2) << right << setfill('0') << min_ << endl;
}
