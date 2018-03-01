#include "ksl-lista.hh"
#include <iostream>
#include <memory>

using namespace std;

KSL_lista::KSL_lista():
    ensimmaisen_osoite_(nullptr),
    viimeisen_osoite_(nullptr),
    alkioiden_maara_(0) {
}

int KSL_lista::pituus() const {
    return alkioiden_maara_;
}

bool KSL_lista::onko_arvo_listassa(int arvo) const {
    shared_ptr<Listan_alkio> tutkittavan_osoite = ensimmaisen_osoite_;

    while ( tutkittavan_osoite != nullptr ) {
        if ( tutkittavan_osoite->data == arvo ) {
            return true;
        } else if ( tutkittavan_osoite->data > arvo ) {
            return false;
        }

        tutkittavan_osoite = tutkittavan_osoite->seuraavan_osoite;
    }

    return false;
}

void KSL_lista::tulosta() const {
    shared_ptr<Listan_alkio> tulostettavan_osoite = ensimmaisen_osoite_;

    cout << "Listan alkioiden maara: " << pituus() << endl;

    while ( tulostettavan_osoite != nullptr ) {
        cout << tulostettavan_osoite->data << " ";

        tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite;
    }

    cout << endl;
}


void KSL_lista::tulosta_takaperin() const {
    Listan_alkio* tulostettavan_osoite = viimeisen_osoite_;

    cout << "Listan alkioiden maara: " << pituus() << endl;

    while ( tulostettavan_osoite != nullptr ) {
        cout << tulostettavan_osoite->data << " ";

        tulostettavan_osoite = tulostettavan_osoite->edellisen_osoite;
    }

    cout << endl;
}


bool KSL_lista::poista_arvo(int poistettava) {
   if ( pituus() == 0 ) {
       return false;
   }

   shared_ptr<Listan_alkio> poistettavan_osoite = ensimmaisen_osoite_;

   while ( true ) {
      if ( poistettavan_osoite->data == poistettava ) {
         break;         // Poistettava arvo löytyi.

      } else if ( poistettavan_osoite->data > poistettava ) {
         return false;  // Arvo ei voi olla loppulistassa.

      } else if ( poistettavan_osoite->seuraavan_osoite == nullptr ) {
         return false;  // Viimeinen alkio on käsitelty.

      } else {
         poistettavan_osoite = poistettavan_osoite->seuraavan_osoite;
      }
   }

   // Tässä kohdassa tiedetään, että poistettava arvo löytyi
   // listasta ja poistettavan_osoite osoittaa siihen.

   // Poistettava alkio on listan ainoa alkio.
   if ( ensimmaisen_osoite_.get() == viimeisen_osoite_ ) {

      ensimmaisen_osoite_ = nullptr;
      viimeisen_osoite_ = nullptr;

   // Poistettava alkio on listan ensimmäinen alkio.
   } else if ( poistettavan_osoite == ensimmaisen_osoite_ ) {

      ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
      ensimmaisen_osoite_->edellisen_osoite = nullptr;

   // Poistettava alkio on listan viimeinen alkio.
   } else if ( poistettavan_osoite.get() == viimeisen_osoite_ ) {

      viimeisen_osoite_ = viimeisen_osoite_->edellisen_osoite;
      viimeisen_osoite_->seuraavan_osoite = nullptr;

   // Poistettava alkio on listan keskellä.
   } else {

      poistettavan_osoite->edellisen_osoite->seuraavan_osoite = poistettavan_osoite->seuraavan_osoite;
      poistettavan_osoite->seuraavan_osoite->edellisen_osoite = poistettavan_osoite->edellisen_osoite;
   }

   --alkioiden_maara_;

   return true;
}


bool KSL_lista::lisaa_numerojarjestykseen(int lisattava) {
    shared_ptr<Listan_alkio> uuden_osoite(new Listan_alkio);

   uuden_osoite->data = lisattava;

   // Lisäys tyhjään listaan.
   if ( pituus() == 0 ) {

      uuden_osoite->seuraavan_osoite = nullptr;
      uuden_osoite->edellisen_osoite = nullptr;

      ensimmaisen_osoite_ = uuden_osoite;
      viimeisen_osoite_ = uuden_osoite.get();

   // Lisäys lista alkuun.
   } else if ( lisattava < ensimmaisen_osoite_->data ) {

      uuden_osoite->seuraavan_osoite = ensimmaisen_osoite_;
      uuden_osoite->edellisen_osoite = nullptr;

      ensimmaisen_osoite_->edellisen_osoite = uuden_osoite.get();
      ensimmaisen_osoite_ = uuden_osoite;

   // Lisäys listan loppuun.
   } else if ( lisattava > viimeisen_osoite_->data ) {

      uuden_osoite->seuraavan_osoite = nullptr;
      uuden_osoite->edellisen_osoite = viimeisen_osoite_;

      viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
      viimeisen_osoite_ = uuden_osoite.get();

   // Lisäys listan keskelle.
   } else {
      shared_ptr<Listan_alkio>
          tutkittavan_osoite = ensimmaisen_osoite_;

      // Etsitään listasta ensimmäinen alkio, jonka sisältämä
      // arvo on suurempi tai yhtäsuuri kuin lisättävä arvo.
      while ( tutkittavan_osoite->data < lisattava ) {
          tutkittavan_osoite = tutkittavan_osoite->seuraavan_osoite;
      }

      // Arvo ei voi saa olla listassa useammin kuin kerran.
      if ( tutkittavan_osoite->data == lisattava ) {
          return false;
      }

      // Nyt tutkittavan_osoite osoittaa ensimmäiseen
      // alkioon listan sisällä, jonka arvo on suurempi
      // kuin lisättävä arvo: uusi alkio lisätään sen eteen.

      uuden_osoite->seuraavan_osoite = tutkittavan_osoite;
      uuden_osoite->edellisen_osoite = tutkittavan_osoite->edellisen_osoite;

      uuden_osoite->edellisen_osoite->seuraavan_osoite = uuden_osoite;
      uuden_osoite->seuraavan_osoite->edellisen_osoite = uuden_osoite.get();
   }

   ++alkioiden_maara_;

   return true;
}
