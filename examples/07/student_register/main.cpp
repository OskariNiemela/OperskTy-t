#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string HELP_TEXT = "N = Lista opiskelijanumeroiden mukaisessa järjestyksessä\n"
                         "K = Lista käyttäjätunnusten mukaisessa aakkosjärjestyksessä\n"
                         "Q = Lopeta\n";

struct Opiskelija {
    std::string opiskelijanumero;
    std::string kayttajatunnus;
    std::string nimi;
    std::string puhelinnumero;
    std::string sahkoposti;
    std::string skype;
};

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


bool lue_tiedot(std::string tiedoston_nimi, map< string, Opiskelija* >& aakkosjarjestys, map< string, Opiskelija* >& numerojarjestys) {
    ifstream tiedosto_olio(tiedoston_nimi);
    if( !tiedosto_olio ) {
        return false;
    }

    string rivi = "";

    while( getline( tiedosto_olio, rivi ) ) {
        std::vector<std::string> osat = split(rivi, ';');
        if(osat.size() != 6){
            return false;
        }

        Opiskelija* uusi_opiskelija = new Opiskelija({osat[0], osat[1], osat[2], osat[3], osat[4], osat[5]});
        numerojarjestys[osat[0]] = uusi_opiskelija;
        aakkosjarjestys[osat[1]] = uusi_opiskelija;
    }
    return true;
}


void tulosta_tiedot(Opiskelija o){
    std::cout << o.opiskelijanumero << " " << o.kayttajatunnus << std::endl
              << o.nimi << std::endl
              << o.puhelinnumero << std::endl
              << o.sahkoposti << std::endl
              << o.skype << std::endl << std::endl;
}


int main()
{
    string tiedoston_nimi = "";
    cout << "Opiskelijatiedosto: ";
    getline(cin, tiedoston_nimi);

    map< std::string, Opiskelija* > kayttajatunnukset;
    map< std::string, Opiskelija* > opiskelijanumerot;
    if(not lue_tiedot(tiedoston_nimi, kayttajatunnukset, opiskelijanumerot)) {
        cout << "Virhe tiedoston lukemisessa!" << std::endl;
        return EXIT_FAILURE;
    }

    while(true){
        std::string rivi;
        std::cout << "> ";
        getline(std::cin, rivi);
        std::vector<std::string> osat = split(rivi, ' ', true);

        if(osat.empty()){
            continue;
        }
        std::string komento = osat.at(0);

        // Tulostetaan aakkostettuna käyttäjätunnusten mukaisesti
        if(komento == "K" or komento == "k"){
            if(osat.size() != 1){
                std::cout << "Virheelliset parametrit!" << std::endl << HELP_TEXT;
                continue;
            } else {
                for(auto pari: kayttajatunnukset) {
                    tulosta_tiedot(*(pari.second));
                }
            }

            // Tulostetaan järjestettynä opiskelijanumeroiden mukaisesti suuruusjärjestykseen
        } else if(komento == "N" or komento == "n"){
            if(osat.size() != 1){
                std::cout << "Virheelliset parametrit!" << std::endl << HELP_TEXT;
                continue;
            } else {
                for(auto pari: opiskelijanumerot) {
                    tulosta_tiedot(*(pari.second));
                }
            }

            // Muokataan opiskelijan tietoja
        } else if(komento == "M" or komento == "m"){
            if(osat.size() != 2){
                std::cout << "Virheelliset parametrit!" << std::endl << HELP_TEXT;
                continue;
            }

            string tunniste = osat.at(1);
            // TODO: Lisää toiminnallisuus tähän.

        } else if(komento == "Q" or komento == "q"){
            // Tietorakenteen tuhoaminen: nollataan osoittimet ja vapautetaan muisti
            for(auto pari: opiskelijanumerot) {
                pari.second = nullptr;
            }

            for(auto pari: kayttajatunnukset) {
                delete pari.second;
                pari.second = nullptr;
            }

            return EXIT_SUCCESS;
        } else {
            std::cout << "Virheellinen komento!" << std::endl << HELP_TEXT;
        }
    }
}


