#include "lista.hh"
#include <iostream>
#include <string>

using namespace std;

int main() {
   Lista tyolista;
   string poistettu = "";

   tyolista.lisaa_alkio_loppuun("siivoa tyopoyta");
   tyolista.lisaa_alkio_loppuun("pese pyykit");
   tyolista.lisaa_alkio_loppuun("tee kotilaksyt");

   cout << "Tekemattomat askareet:" << endl;
   tyolista.tulosta();

   tyolista.poista_alkio_alusta(poistettu);
   cout << "  suoritettu: " << poistettu << endl;

   tyolista.lisaa_alkio_loppuun("tiskaa");
   tyolista.lisaa_alkio_loppuun("vie roskat");

   cout << endl << "Tekemattomat askareet:" << endl;
   tyolista.tulosta();

   while ( not tyolista.onko_tyhja() ) {
      tyolista.poista_alkio_alusta(poistettu);
      cout << "  suoritettu: " << poistettu << endl;
   }

   if ( tyolista.onko_tyhja() ) {
      cout << "Kaikki askareet suoritettu!" << endl;
   }
}
