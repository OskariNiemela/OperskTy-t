#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


// Annetaan map-tyypille uusi nimi, jotta ei ole niin paljon
// kirjoitettavaa aina, kun tyyppinimeä halutaan käyttää.
// Tästä eteenpäin sanaa Kalenteri voi käyttää kaikkialla,
// missä voisi kirjoittaa map<string, vector<string>>.
using Kalenteri = map<string, vector<string>>;


void tulosta_kalenteri(const Kalenteri& kal);
void lisaa_tapahtuma(Kalenteri& kal, const string& pvm, const string& tap);
void poista_paivan_tapahtumat(Kalenteri& kal, const string& pvm);
string kysy_paivamaara();
string kysy_tapahtuma();

int main() {
    // first: päivämäärä, second: vektori päivän tapahtumia
    Kalenteri kalenteri = {
        { "2016.12.24",  { "Joulukalenteri loppuu", "Joulupukki tulee!" } },
        { "2016.12.06",  { "Itsenaisyyspaiva" } },
        { "2017.06.01",  { "Kesa alkaa" } },
    };

    // Testikäyttöliittymä toteutettujen funktioiden testaamiseen
    while ( true ) {
        cout << "(t)ulosta, (l)isaa, (p)oista, (q)uit: ";
        string valinta = "";
        getline(cin, valinta);

        if ( valinta == "t" ) {
            tulosta_kalenteri(kalenteri);

        } else if ( valinta == "l" ) {
            string paivamaara = kysy_paivamaara();
            string tapahtuma = kysy_tapahtuma();

            lisaa_tapahtuma(kalenteri, paivamaara, tapahtuma);

        } else if ( valinta == "p" ) {
            string paivamaara = kysy_paivamaara();

            poista_paivan_tapahtumat(kalenteri, paivamaara);

        } else if ( valinta == "q" ) {
            cout << "Loppu!" << endl;
            break;

        } else {

            cout << "Tuntematon komento!" << endl;
        }

        cout << endl;
    }
}

void tulosta_tapahtumavektori(const vector<string>& tapahtumat) {
    vector<string>::const_iterator iter = tapahtumat.begin();

    while ( iter != tapahtumat.end() ) {
        cout << "* " << *iter << endl;

        ++iter;
    }

    // Toteutus voisi olla vaihtoehtoisesti:
    // for ( const auto& tapahtuma : tapahtumat ) {
    //     cout << "* " << tapahtuma << endl;
    // }
}


void tulosta_kalenteri(const Kalenteri& kal) {
    Kalenteri::const_iterator iter = kal.begin();

    while ( iter != kal.end() ) {
        cout << string(10, '=') << endl
             << iter->first << endl
             << string(10, '=') << endl;

        tulosta_tapahtumavektori(iter->second);

        ++iter;
    }

    // Toteutus voisi olla vaihtoehtoisesti:
    // for ( const auto& paivatiedot : kal ) {
    //     cout << string(10, '=') << endl
    //          << paivatiedot.first << endl
    //          << string(10, '=') << endl;
    //
    //     tulosta_tapahtumavektori(paivatiedot.second);
    // }
}

// Huomaa, kuinka tällä funktiolla ja poista_paivan_tapahtumat-funktiolla
// kalenterin täytyy olla viiteparametrina (&), ei tehokkuussyistä, vaan
// siksi, että funktioiden on pystyttävä muuttamaan pääohjelmassa
// todellsiena parametrina annettua kalenteria.
void lisaa_tapahtuma(Kalenteri& kal, const string& pvm, const string& tap) {
    Kalenteri::iterator iter = kal.find(pvm);

    // Jos päivämäärä ei ole hakuavaimena mapissa, kyseisellä
    // päivämäärällä ei ole kalenterimerkintöjä: lisätään pvm
    // hakuavaimeksi ja kyseisen päivän ainoaksi tapahtumaksi tap.
    if ( iter == kal.end() ) {
        kal.insert( {pvm, { tap }} );

    // Lisätään olemassa olevalle päivämäärälle merkintä.
    } else {
        // Jos samassa lausekkeessa on peräkkäin suoritettavana
        // useita "."- tai "->" -operaattoreita, ne suoritetaan
        // vasemmalta oikealle järjestyksessä. Eli seuraavassa
        // kal-muuttujaan kohdistetaan ensin at-metodi, joka
        // palauttaa hakuavaimeen pvm liitetyn vektorin, johon
        // sen jälkeen kohdistetaan push_back-metodi.

        kal.at(pvm).push_back(tap);
    }
}


void poista_paivan_tapahtumat(Kalenteri& kal, const string& pvm) {
    Kalenteri::iterator iter = kal.find(pvm);

    if ( iter == kal.end() ) {
        cout << "Paivamaaralla ei ole tapahtumia, poisto epaonnistui!"
             << endl;

    } else {
        // Mistä tahansa STL-säiliöstä saadaan poistettua iteraattorin
        // osoittama alkio erase-metodilla.

        kal.erase(iter);
    }
}


string kysy_paivamaara() {
    // Tämä on hyvin keskeneräinen toteutus:
    // käyttäjän syöttämälle päivämärälle ei
    // tehdä minkäänlaisia järkevyystarkistuksia.

    cout << "syota paivamaara: ";
    string pvm = "";
    getline(cin, pvm);

    return pvm;
}


string kysy_tapahtuma() {
    cout << "syota tapahtuma: ";
    string tapahtuma = "";
    getline(cin, tapahtuma);

    return tapahtuma;
}


