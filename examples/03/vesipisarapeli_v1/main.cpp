#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include "ruutu.hh"

const int KOKO = 12;

void alustaLauta( Lauta& lauta )
{
    std::cout << "Enter a seed value for random number generator or an empty line: ";
    std::string siemen = "";
    getline(std::cin, siemen);

    if( siemen == "" ) {
        // Jos käyttäjä ei syöttänyt siemenarvoa, käytetään siemenenä tietokoneen kellosta otettua satunnaislukua.
        srand( time(NULL) );
    } else {
        // Jos käyttäjä syötti siemenarvon, käytetään sitä.
        srand( stoi(siemen) );
    }

    for( int y = 0; y < KOKO; ++y )
    {
        std::vector< Ruutu > rivi;
        for( int x = 0; x < KOKO; ++x )
        {
            Ruutu uusi_ruutu( x, y, rand()%5, &lauta);
            rivi.push_back( uusi_ruutu );
        }
        lauta.push_back( rivi );
    }
}

void tulostaLauta( Lauta& lauta, std::ostream& virta )
{
    // Tulostetaa jokaisen merkin jälkeen välilyönti, jotta ASCII-grafiikka olisi vähän selkeämpää katsoa.

    // Tulostetaan laudan yläpuolelle X-akselin suuntaiset numerot
    virta << "  ";
    for( int x = 0; x < KOKO; ++x )
    {
        virta << (x+1) % 10 << ' ';  // Käytetään jakojäännöstä 10:n suhteen, jotta tuloste mahtuu vaikka lauta olisi suurempi kuin 10
    }
    virta << std::endl;

    // Tulostetaan lauta siten, että jokaiselle riville tulee Y-akselin numero ja ko.
    // rivillä olevia pisaroita pyydetään sen jälkeen tulostamaan itsensä metodikutsua käyttäen.
    for( int y = 0; y < KOKO; ++y )
    {
        virta << (y+1) % 10 << ' ';
        for( int x = 0; x < KOKO; ++x )
        {
            lauta.at(y).at(x).tulosta( virta );
            virta << " ";
        }
        virta << std::endl;
    }
}

bool tarkistaLauta( Lauta& lauta )
{
    for( int y = 0; y < KOKO; ++y )
    {
        for( int x = 0; x < KOKO; ++x )
        {
            if( lauta[y][x].onkoVetta() )
            {
                return true;
            }
        }
    }
    return false;
}

bool lueKomento(int& x, int& y)
{
    std::cout << "x y> ";
    return std::cin >> x and std::cin >> y;
}

int main()
{
    Lauta lauta;
    alustaLauta(lauta);
    tulostaLauta(lauta, std::cout);

    int x = 0;
    int y = 0;
    int tankki = 10;

    while( tankki and tarkistaLauta(lauta) and lueKomento(x, y) )
    {
        lauta.at(y-1).at(x-1).lisaaVetta();
        tankki--;
        tulostaLauta(lauta, std::cout);
    }

    return EXIT_SUCCESS;
}
