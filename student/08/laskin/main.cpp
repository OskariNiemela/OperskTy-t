#include "laskut.hh"
#include <iostream>
#include <iomanip>
#include <sstream>  // string_doubleksi-funktion toteutusta varten.
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;

const string LOPPUTERVEHDYS = "Kiitos ja näkemiin!";

// Apufunktio, joka jakaa merkkijonon osiksi erotinmerkkien kohdalta.
vector< string > split(const string& s,
                       const char delimiter,
                       bool ignore_empty = false);

// string_doubleksi on apufunktio, jonka avulla merkkijonossa olevan
// reaaliluvun saa muutettua double-tyyppiseksi arvoksi
// laskutoimituksia varten. Funktion paluuarvo on true, jos parametri
// mjono oli esitti reaalilukua. Paluuarvo on false, jos mjono oli
// jollain tavoin virheellinen. Varsinainen muunnettu reaaliluku
// sijoitetaan viiteparametriin tulos. Funktion toteutuksessa on
// käytetty esimerkin vuoksi stringstreameja.
bool string_doubleksi(const string& mjono, double& tulos);


// TODO: Tutustu seuraaviin tietorakenteisiin!
struct Komento {
    string merkkijono;
    vector<string>::size_type parametrien_lkm;
    bool lopetus;
    double(*toiminto)(double, double);
};

const vector<Komento> KOMENNOT = {
    {"+", 2, false, yhteen},
    {"-", 2, false, vahennys},
    {"*", 2, false, kerto},
    {"/", 2, false, jako},
    {"PLUS", 2, false, yhteen},
    {"MIINUS", 2, false, vahennys},
    {"KERTAA", 2, false, kerto},
    {"JAETTUNA", 2, false, jako},
    {"YHTEEN", 2, false, yhteen},
    {"VAHENNYS", 2, false, vahennys},
    {"KERTO", 2, false, kerto},
    {"JAKO", 2, false, jako},
    {"SUMMA", 2, false, yhteen},
    {"EROTUS", 2, false, vahennys},
    {"TULO", 2, false, kerto},
    {"OSAMAARA", 2, false, jako},
    {"SUMMAA", 2, false, yhteen},
    {"PLUSSAA", 2, false, yhteen},
    {"VAHENNA", 2, false, vahennys},
    {"MIINUSTA", 2, false, vahennys},
    {"KERRO", 2, false, kerto},
    {"JAA", 2, false, jako},
    {"LOPETA", 0, true, nullptr},
    {"QUIT", 0, true, nullptr},
    {"EXIT", 0, true, nullptr},
    {"Q", 0, true, nullptr},
    {"^", 2, false, potenssi},
    {"EXP", 2, false, potenssi},
    {"POTENSSI", 2, false, potenssi}
};


int main() {

    // Määritellään tulostuksen tarkkuus kahteen desimaaliin
    cout.precision(2);
    cout << fixed;

    double ans;
    double par1;
    double par2;

    using Funktio = double(*)(double,double);
    vector<string>::size_type par_lkm;

    while ( true ) {
        cout << "laskin> ";

        string rivi = "";
        getline(cin, rivi);

        if ( rivi.empty() ) {
            // Tyhjän rivin syöttäminen keskeyttää käyttöliittymäsilmukan,
            // minkä seurauksena ohjelman suoritus tulee päättymään.
            cout << LOPPUTERVEHDYS << endl;
            break;
        }

        vector<string> palat = split(rivi, ' ', true);

        if(palat.size() == 0){
            continue;
        }

        string suoritettava_komento = palat.at(0);

        // TODO: Toteuta komennon suorittaminen tähän!
        for(string::iterator str_char=suoritettava_komento.begin(); str_char!=suoritettava_komento.end(); str_char++)
        {
            *str_char = toupper(*str_char);
        }

        Funktio lasku = nullptr;
        bool komento_loytyi = false;


        for(auto i:KOMENNOT)
        {
            if(i.merkkijono == suoritettava_komento)
            {
                lasku = i.toiminto;
                par_lkm = i.parametrien_lkm;
                komento_loytyi = true;
                break;
            }
        }

        if(!komento_loytyi)
        {
            std::cout<<"Virhe: tuntematon komento."<<std::endl;
            continue;
        }

        if(lasku == nullptr)
        {
            std::cout<<LOPPUTERVEHDYS<<std::endl;
            return EXIT_SUCCESS;
        }

        if(par_lkm == palat.size()-1)
        {
            if(string_doubleksi(palat.at(1),par1)&&string_doubleksi(palat.at(2),par2))
            {
                ans = lasku(par1,par2);
                std::cout<<ans<<std::endl;
            }
            else
            {
                std::cout<<"Virhe: kaikki operandit eivät ole lukuja."<<std::endl;
            }
        }
        else
        {
            std::cout<<"Virhe: väärä määrä parametreja."<<std::endl;
        }



    }
}


// Tämä funktio on esimerkki istringstreamin käytöstä.
// Periaatteessa merkkojonoja voi muuttaa doubleiksi myös
// string-kirjaston stod-funktiolla. Tässä vaiheessa koulutusta
// kaikkien virhetilanteiden havaitseminen stod-funktiota köytettäessä
// on kuitenkin monimutkaisempaa, kuin tässä funktiossa toteutettu
// bool-tyyppinen paluuarvo, jota voi tutkia funktion kutsukohdassa.
bool string_doubleksi(const string& mjono, double& tulos) {
    // Alustetaan istringstream-tyyppinen syötevirta merkkijonolla,
    // joka halutaan lukea läpi >>- tai getline-operaatioilla.
    istringstream syotevirta(mjono);

    double apu;

    // Luetaan syotevirrasta arvo muuttujaan normaalisti >>-operaattorilla.
    // istringstream-tyyppisiä virtoja voi käsitellä täsmälleen samoilla
    // operaatioilla kuin ciniä ja ifstream-tyyppisiä (tiedostot) virtoja.
    syotevirta >> apu;

    if ( not syotevirta ) {
        return false;
    }

    // ws on erikoisoperaatio, joka hyppää yli kaikki sanaerotinmerkit
    // (välilyönnit jne.) kunnes vastaan tulee jotain muuta.
    syotevirta >> ws;

    // Jos mjono-parametri oli oikein mutoiltu reaalilukua esittävä
    // merkkijono, sen perässä ei saa olla muuta kuin välilyönteja.
    // Eli koska edeltävä ">> ws"-operaatio heitti välilyönnit menemään,
    // tässä kohdassa syotevirrassa ei saa olla jäljellä mitään,
    // tai jos on, mjono oli virheellinen.  Yritetään lukea syötevirrasta
    // merkki. Jos lukeminen epäonnistuu siksi, että virrassa ei enää
    // ole mitään jäljellä, kaikki on kunnossa. Jos merkin lukeminen
    // onnistuu, se tarkoittaa, että mjonon perässä oli jotain ylimääräistä.

    syotevirta.get();

    if ( syotevirta ) {
        return false;
    } else {
        tulos = apu;
        return true;
    }
}

// Vanha tuttu split-funktion malliratkaisu.
vector< string > split(const string& s, const char delimiter, bool ignore_empty){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string sana = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and sana.empty()))
        {
            result.push_back(sana);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}