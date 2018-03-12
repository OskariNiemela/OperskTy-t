/* Moduuli: Pääohjelma / tiedosto: main.cpp
 * Sisältää pelin käyttöliittymän, pelilautaolion ja vesitankin.
 */

#include "pelilauta.hh"
#include <cstdlib>
#include <iostream>

bool lueKomento(int& x, int& y)
{
    while(true){
        std::cout << "x y> ";

        // Jos syötettä ei saada luettua, ohjelman toiminta päättyy
        if(not(std::cin >> x and std::cin >> y)){
            return false;
        }

        // Jos saadaan luettua kelvolliset koordinaatit, toiminta jatkuu
        if(0 < x and x <= KOKO and 0 < y and y <= KOKO){
            return true;
        }

        // Muuten jatketaan syötteiden käsittelyä
        std::cout << "Error! Coordinates must be 1-" << KOKO << std::endl;
    }
}

int main()
{
    Pelilauta lauta;
    lauta.tulosta(std::cout);

    int x = 0;
    int y = 0;
    int tankki = 10;

    while( tankki and lauta.onkoTyhja() and lueKomento(x, y) )
    {
        lauta.lisaaVetta(x-1, y-1);
        tankki--;
        lauta.tulosta(std::cout);
    }

    return EXIT_SUCCESS;
}
