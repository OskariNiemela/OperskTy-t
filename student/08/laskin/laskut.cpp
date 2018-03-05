// Huomaa, ei tarvetta using namespace std:lle, koska tässä
// tiedostossa ei käytetä mitään C++:n valmiskirjastoja.

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
   double ans = 1;
   for(double i=0;i<oikea;i++)
   {
       ans = ans*vasen;
   }
   return ans;
}
