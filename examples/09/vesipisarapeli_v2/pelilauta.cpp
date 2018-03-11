/* Moduuli: Pelilauta / tiedosto: pelilauta.cpp
 */

#include "pelilauta.hh"
#include <string>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

Pelilauta::Pelilauta(): lauta_(), roiskeet_()
{
    // Käyttäjän mahdollista syöttää siemenluku testauksen vuoksi
    std::cout << "Enter a seed value for random number generator or an empty line: ";
    std::string siemen = "";
    getline(std::cin, siemen);

    if(siemen == "") {
        // Jos käyttäjä ei syöttänyt siemenarvoa, käytetään siemenenä
        // tietokoneen kellosta otettua satunnaislukua.
        srand(time(NULL));
    } else {
        // Jos käyttäjä syötti siemenarvon, käytetään sitä.
        srand(stoi(siemen));
    }

    // Lauta alustetaan muuten samoin kuin vesipisarapeli_v1:ssä, mutta ...
    for(int y = 0; y < KOKO; ++y)
    {
        std::vector< std::shared_ptr<Pisara> > rivi;
        for(int x = 0; x < KOKO; ++x)
        {
            int koko = rand()%5;
            std::shared_ptr< Pisara > uusiPisara = nullptr;

            // ... luodaan pisaraoliot vain niihin ruutuihin, joihin tulee vettä.
            if (koko != 0)
            {
                uusiPisara = std::make_shared<Pisara>(x, y, koko, this);
            }
            rivi.push_back(uusiPisara);
        }
        lauta_.push_back(rivi);
    }
}

void Pelilauta::tulosta(std::ostream& virta)
{
    // do - while on toistorakenne, joka suoritetaan aina vähintään yhden kerran.
    // Ehto on rakenteen lopussa, ja se evaluoidaan aina rungon suorittamisen jälkeen.
    do {
        // Uudet roiskeet ovat siinä ruudussa, jossa pisara poksahti, joten
        // siirretään kaikkia roiskeita yksi ruutu eteenpäin ennen laudan tulostamista.
        siirraRoiskeita();

        // Itse tulostus tapahtuu samoin kuin vesipisarapeli_v1:ssä.
        virta << "\n  ";
        for(int x = 0; x < KOKO; ++x)
        {
            virta << (x+1) % 10 << ' ';
        }
        virta << std::endl;

        for(int y = 0; y < KOKO; ++y)
        {
            virta << (y+1) % 10 << ' ';
            for(int x = 0; x < KOKO; ++x)
            {
                if(lauta_.at(y).at(x) != 0)
                {
                    lauta_.at(y).at(x)->tulosta(virta);
                    virta << " ";
                } else {
                    // Jos ruudussa ei ole pisaraa, täytyy kuitenkin tarkastaa,
                    // tulostuuko tyhjä, vai onko ruudussa roiskeita
                    virta << pisarattomanRuudunTulostusmerkki(x, y) << " ";
                }
            }
            virta << std::endl;
        }

        // Odotetaan pikku hetki ennen seuraavaa tulostusta, jotta
        // roiskeiden animointi näyttää edes vähän paremmalta.
        std::this_thread::sleep_for(std::chrono::seconds(1));

    // Tulostus toistetaan niin monta kertaa, että kaikkien roiskeiden lento on
    // saatu "animoitua", eli kunnes yhtään roisketta ei ole jäljellä.
    } while(roiskeet_.size() > 0);
}

bool Pelilauta::onkoTyhja()
{
    for( int y = 0; y < KOKO; ++y )
    {
        for( int x = 0; x < KOKO; ++x )
        {
            if( lauta_.at(y).at(x) != nullptr )
            {
                return true;
            }
        }
    }
    return false;
}

void Pelilauta::lisaaVetta(int x, int y)
{
    if(lauta_.at(y).at(x) != nullptr){
        lauta_.at(y).at(x)->lisaaVetta(roiskeet_);
    } else {
        lauta_.at(y).at(x) = std::make_shared<Pisara>(x, y, 1, this);
    }
}

void Pelilauta::poistaPisara(int x, int y)
{
    lauta_.at(y).at(x) = nullptr;
}

void Pelilauta::siirraRoiskeita()
{
    // Säiliö siirtämisen vuoksi syntyvien uusien roiskeiden tallentamiseen.
    // Näitä ei voi lisätä heti säiliöön roiskeet_, koska näitä ei haluta
    // vielä siirtää tällä siirtokierroksella, vaan vasta seuraavalla.
    std::vector<Roiske> uudetRoiskeet;

    // Kaikki laudalla olevat roiskeet käydään läpi iteraattorin avulla whilessä.
    std::vector<Roiske>::iterator r = roiskeet_.begin();
    while (r != roiskeet_.end()) {

        // Jokaiselle roiskeelle kutsutaan metodia liiku, joka palauttaa true,
        // jos roiske liikkuu pois pelilaudalta ja pitää poistaa. Tämä tieto talletataan.
        bool poistetaankoRoiske = r->liiku();

        // Jos roiske on liikkumisen jälkeen ruudussa, josta löytyy vesipisara
        // lisätään kyseiseen pisaraan vettä ja roiske poistetaan.
        if(not poistetaankoRoiske and lauta_.at(r->annaY()).at(r->annaX()) != 0) {
            lauta_.at(r->annaY()).at(r->annaX())->lisaaVetta(uudetRoiskeet);
            poistetaankoRoiske = true;
        }

        // Jos poistetaan roiskeolio vectorista, vectorin erase palauttaa uuden
        // iteraattorin siihen kohtaan vectoria, josta sen läpikäymistä jatketaan
        // poiston jälkeen. Muuten jatketaan siirtämällä iteraattoria pykälällä.
        if(poistetaankoRoiske) {
            r = roiskeet_.erase(r);
        } else {
            r++;
        }
    }
    // Lopuksi lisätään tämän siirtokierroksen aikana syntyneet uudet roiskeet
    // pelilaudan roiskeiden listalle, jotta nekin tulevat mukaan animointiin.
    roiskeet_.insert(roiskeet_.end(), uudetRoiskeet.begin(), uudetRoiskeet.end());
}

char Pelilauta::pisarattomanRuudunTulostusmerkki(int x, int y)
{
    // Tarkastetaan, onko kyseisessä ruudussa roiskeita. Tallennetaan jokaisen
    // löytyneen roiskeen piirrosmerkki merkkijonoon piirrosmerkit
    std::string piirrosmerkit = "";
    for(auto r: roiskeet_)
    {
        if(r.annaX() == x and r.annaY() == y) {
            piirrosmerkit += r.annaTulostusmerkki();
        }
    }

    if(piirrosmerkit.length() == 0) { // Ei yhtään roisketta ruudussa -> tulostuu tyhjä
        return ' ';
    } else if (piirrosmerkit.length() == 1){  // Yksi roiske -> tulostuu sen merkki
        return piirrosmerkit.at(0);
    } else {  // Useampia roiskeita samassa ruudussa
        for(auto merkki: piirrosmerkit){
            if(merkki != piirrosmerkit.at(0)){
                // Samassa ruudussa on useamman erinäköisiä roiskeita
                // -> Ei pysty tulostamaan kaikkia joten tulostetaan sotku
                return '*';
                // HUOM! Kun pisara poksahtaa, se muodostaa 4 roisketta siihen ruutuun,
                // jossa se sijaitsi, joten tavallaan tämä piirrosmerkki kuvaa myös poksahdusta.
            }
        }
        // Vaikka ruudussa on useampia roiskeita, on niillä kaikilla sama tulostusmerkki,
        // joten tulostetaan tämä yhteinen merkki
        return piirrosmerkit.at(0);
    }
}
