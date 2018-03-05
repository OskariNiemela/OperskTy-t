// Huomaa, ei tarvetta using namespace std:lle, koska tässä
// tiedostossa ei käytetä mitään C++:n valmiskirjastoja.
#include <math.h>

double yhteen(double vasen, double oikea) {
    return vasen + oikea;
}


double vahennys(double vasen, double oikea) {
    return vasen - oikea;
}


double kerto(double vasen, double oikea) {
    return vasen * oikea;
}

double jako(double vasen, double oikea) {
    return vasen / oikea;
}

double potenssi(double vasen, double oikea)
{
   return pow(vasen,oikea);
}
