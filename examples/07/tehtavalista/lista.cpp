#include "lista.hh"
#include <iostream>
#include <string>

using namespace std;

Lista::Lista(): ensimmaisen_osoite_(nullptr), viimeisen_osoite_(nullptr) {
}

Lista::~Lista() {
   while ( ensimmaisen_osoite_ != nullptr ) {
      Listan_alkio* vapautettavan_osoite = ensimmaisen_osoite_;
      ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;

      delete vapautettavan_osoite;
   }
}

void Lista::tulosta() const {
   Listan_alkio* tulostettavan_osoite = ensimmaisen_osoite_;
   int jarjestysnumero = 1;

   while ( tulostettavan_osoite != nullptr ) {
      cout << jarjestysnumero << ". " << tulostettavan_osoite->tehtava << endl;
      ++jarjestysnumero;
      tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite;
   }
}

void Lista::lisaa_alkio_loppuun(const string& lisattava_tehtava) {
   Listan_alkio* uuden_osoite = new Listan_alkio{lisattava_tehtava, nullptr};

   if ( ensimmaisen_osoite_ == nullptr ) {
      ensimmaisen_osoite_ = uuden_osoite;
      viimeisen_osoite_ = uuden_osoite;
   } else {
      viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
      viimeisen_osoite_ = uuden_osoite;
   }
}

bool Lista::poista_alkio_alusta(string& poistettu_tehtava) {
   if ( onko_tyhja() ) {
      return false;
   }

   Listan_alkio* poistettavan_osoite = ensimmaisen_osoite_;

   poistettu_tehtava = poistettavan_osoite->tehtava;

   if ( ensimmaisen_osoite_ == viimeisen_osoite_ ) {
      ensimmaisen_osoite_ = nullptr;
      viimeisen_osoite_ = nullptr;
   } else {
      ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
   }

   delete poistettavan_osoite;

   return true;
}

bool Lista::onko_tyhja() const {
   if ( ensimmaisen_osoite_ == nullptr ) {
      return true;
   } else {
      return false;
   }
}
