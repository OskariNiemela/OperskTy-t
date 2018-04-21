#include "gameengine.hh"

#include <QMessageBox>
#include <QCoreApplication>
#include <QTime>

#include <thread>

GameEngine::GameEngine(GameBoard& gameBoard, int seed):
    QObject(0),
    board_(),
    splashes_(),
    graphicalGameBoard_(gameBoard),
    waterTank_(10)
{
    if(seed == 0) {
        // Jos käyttäjä ei syöttänyt siemenarvoa, käytetään siemenenä
        // tietokoneen kellosta otettua satunnaislukua.
        srand(time(NULL));
    } else {
        // Jos käyttäjä syötti siemenarvon, käytetään sitä.
        srand(seed);
    }

    initialize();
}

// Aseta pelimoottori aloitustilaan.
void GameEngine::initialize()
{
    waterTank_ = 10;
    board_.clear();

    // Pelilaudan tietosisällön alustaminen samoin kuin vesipisarapeli v2:ssa.
    for(int y = 0; y < SIZE; ++y)
    {
        std::vector< std::shared_ptr<Drop> > row;
        for(int x = 0; x < SIZE; ++x)
        {
            int size = rand()%5;
            std::shared_ptr<Drop> newDrop = nullptr;

            if (size != 0)
            {
                newDrop = std::make_shared<Drop>(x, y, size, this);
            }
            row.push_back(newDrop);
        }
        board_.push_back(row);
    }

    // Pelilaudan graafisen esityksen alustaminen.
    graphicalGameBoard_.clear();
    for (int row = 0; row < SIZE; row++)
    {
        for (int column = 0; column < SIZE; column++)
        {
            std::shared_ptr<Drop> drop = dropAt(column, row);
            if (drop != nullptr)
            {
                graphicalGameBoard_.addDrop(column, row, drop);
            }
        }
    }
}

// Tarkastus, onko pelilauta tyhjä vedestä.
bool GameEngine::isEmpty() const
{
    for( int y = 0; y < SIZE; ++y )
    {
        for( int x = 0; x < SIZE; ++x )
        {
            if( board_.at(y).at(x) != nullptr )
            {
                return false;
            }
        }
    }
    return true;
}

// Poista vesipisara pelilaudan tietosisällöstä.
void GameEngine::removeDrop(int x, int y)
{
    board_.at(y).at(x) = nullptr;
}

// Hae osoitin tietyssä kohdassa olevaan pisaraan, tai nollaosoitin,
// jos koordinaatit laudan ulkopuolella.
std::shared_ptr<Drop> GameEngine::dropAt(int x, int y) const
{
    if (0 <= x and x < SIZE and 0 <= y and y < SIZE){
        return board_.at(y).at(x);
    } else {
        return nullptr;
    }
}

// Lisää vettä tiettyyn kohtaan pelilautaa.
void GameEngine::addWater(int x, int y)
{
    // Vähennä vettä tankista.
    waterTank_--;

    // Päivitä pelin tietosisältö oikeaan tilaan.
    if(board_.at(y).at(x) != nullptr){
        board_.at(y).at(x)->addWater(splashes_);
    } else {
        board_.at(y).at(x) = std::make_shared<Drop>(x, y, 1, this);
    }

    // Haetaan osoitin pisaraan, jota juuri käsiteltiin.
    std::shared_ptr<Drop> drop = dropAt(x, y);

    // Päivitä myös graafinen esitys oikeaan tilaan.
    if (drop == nullptr) {
        // Jos pisara poksahti, poista sen kuva piirtoalueelta.
        graphicalGameBoard_.removeDrop(x, y);

    } else if (drop->waterAmount() == 1) {
        // Jos ruutu oli tyhjä, lisää piirtoalueelle uusi pisarakuva
        graphicalGameBoard_.addDrop(x, y, drop);

    } else {
        // Muuten kasvatetaan pisarakuvaa.
        graphicalGameBoard_.updateDrop(drop->getX(), drop->getY());
    }

    // Päivitä pelilaudan piirto, siirrä roiskeita ja lisää tarvittaessa
    // roiskeista vettä pisaroille.
    do {
        std::vector<std::shared_ptr<Drop> > growingDrops;

        moveSplashes(growingDrops);
        graphicalGameBoard_.animate();

        // Testitulostus konsoliin: Ota käyttöön poistamalla kommentti seuraavalta riviltä
        //print(std::cout, splashes_);

        // Käydään läpi kaikki vesipisarat, joihin pitää lisätä vettä.
        for (auto const& drop : growingDrops)
        {
            drop->addWater(splashes_);

            // Vesipisaroiden kuvat pitää päivittää näytöllä.
            if (dropAt(drop->getX(), drop->getY()) == nullptr){
                // Jos lisäys poksautti pisaran, täytyy kuva poistaa näkyvistä.
                graphicalGameBoard_.removeDrop(drop->getX(), drop->getY());
            }
            else {
                // Muuten kuva vaihdetaan.
                graphicalGameBoard_.updateDrop(drop->getX(), drop->getY());
            }
        }

    } while(splashes_.size() > 0);  // Toistetaan kunnes roiskeita ei enää ole.

    // Tarkasta päättyykö peli.
    if (waterTank_ <= 0 or isEmpty())
    {
        int messageBoxResult = 0;

        if (isEmpty()) {
            messageBoxResult = QMessageBox::question(0, "Level completed!", "Continue playing?",
                                                     QMessageBox::Yes, QMessageBox::No);
        }
        else {
            messageBoxResult = QMessageBox::question(0, "Oops!", "No more water. Try again?",
                                                     QMessageBox::Yes, QMessageBox::No);
        }

        if (messageBoxResult == QMessageBox::Yes)
        {
            initialize();
        }
        else
        {
            emit quitGame();
        }
    }
}

void GameEngine::moveSplashes(std::vector<std::shared_ptr<Drop> >& grownDrops)
{
    // Säiliö siirtämisen vuoksi syntyvien uusien roiskeiden tallentamiseen.
    // Näitä ei voi lisätä heti säiliöön splashes_, koska näitä ei haluta
    // vielä siirtää tällä siirtokierroksella, vaan vasta seuraavalla.
    std::vector<Splash> newDrops;

    // Kaikki laudalla olevat roiskeet käydään läpi iteraattorin avulla whilessä.
    std::vector<Splash>::iterator r = splashes_.begin();
    while (r != splashes_.end()) {

        // Otetaan talteen roiskeen lähtöpaikka.
        int beginX = r->getX();
        int beginY = r->getY();

        // Jokaiselle roiskeelle kutsutaan metodia liiku, joka palauttaa true,
        // jos roiske liikkuu pois pelilaudalta ja pitää poistaa. Tämä tieto talletataan.
        bool remove = r->move();

        // Otetaan talteen roiskeen loppupaikka ja lisätään sen liikkeelle animaation.
        int endX = r->getX();
        int endY = r->getY();
        graphicalGameBoard_.addSplash(beginX, beginY, endX, endY);

        // Jos roiske on liikkumisen jälkeen ruudussa, josta löytyy vesipisara
        // lisätään kyseiseen pisaraan vettä ja roiske poistetaan.
        std::shared_ptr<Drop> drop = dropAt(endX, endY);

        if(not remove and drop != nullptr) {
            remove = true;
            grownDrops.push_back(drop);
        }

        // Jos poistetaan roiskeolio vectorista, vectorin erase palauttaa uuden
        // iteraattorin siihen kohtaan vectoria, josta sen läpikäymistä jatketaan
        // poiston jälkeen. Muuten jatketaan siirtämällä iteraattoria pykälällä.
        if(remove) {
            r = splashes_.erase(r);
        } else {
            r++;
        }
    }
    // Lopuksi lisätään tämän siirtokierroksen aikana syntyneet uudet roiskeet
    // pelilaudan roiskeiden listalle, jotta nekin tulevat mukaan animointiin.
    splashes_.insert(splashes_.end(), newDrops.begin(), newDrops.end());
}

// Testitulostus konsoliin.
void GameEngine::print(std::ostream& stream, std::vector<Splash>& splashes)
{
    stream << "\n  ";
    for(int x = 0; x < SIZE; ++x)
    {
        stream << (x+1) % 10 << ' ';
    }
    stream << std::endl;

    for(int y = 0; y < SIZE; ++y)
    {
        stream << (y+1) % 10 << ' ';
        for(int x = 0; x < SIZE; ++x)
        {
            if(board_.at(y).at(x) != 0)
            {
                board_.at(y).at(x)->print(stream);
                stream << " ";
            } else {
                // Jos ruudussa ei ole pisaraa, täytyy kuitenkin tarkastaa,
                // tulostuuko tyhjä, vai onko ruudussa roiskeita
                stream << droplessSquareChar(x, y, splashes) << " ";
            }
        }
        stream << std::endl;
    }
}

char GameEngine::droplessSquareChar(int x, int y, std::vector<Splash>& splashes)
{
    // Tarkastetaan, onko kyseisessä ruudussa roiskeita. Tallennetaan jokaisen
    // löytyneen roiskeen piirrosmerkki merkkijonoon piirrosmerkit
    std::string characters = "";
    for(auto r: splashes)
    {
        if(r.getX() == x and r.getY() == y) {
            characters += r.getChar();
        }
    }

    if(characters.length() == 0) { // Ei yhtään roisketta ruudussa -> tulostuu tyhjä
        return ' ';
    } else if (characters.length() == 1){  // Yksi roiske -> tulostuu sen merkki
        return characters.at(0);
    } else {  // Useampia roiskeita samassa ruudussa
        for(auto character: characters){
            if(character != characters.at(0)){
                // Samassa ruudussa on useamman erinäköisiä roiskeita
                // -> Ei pysty tulostamaan kaikkia joten tulostetaan sotku
                return '*';
                // HUOM! Kun pisara poksahtaa, se muodostaa 4 roisketta siihen ruutuun,
                // jossa se sijaitsi, joten tavallaan tämä piirrosmerkki kuvaa myös poksahdusta.
            }
        }
        // Vaikka ruudussa on useampia roiskeita, on niillä kaikilla sama tulostusmerkki,
        // joten tulostetaan tämä yhteinen merkki
        return characters.at(0);
    }
}
