#include "gamerules.hh"
#include "card.hh"

// Funktio saa parametrinaan alla olevan kortin ja päälle tulevan kortin
// tiedot merkkijonomuodossa.
bool GameRules::checkIfHeart(std::string bottom, std::string top)
{
    // Tämä funktio ei tarkastele, mitä alle on jo laitettu, vaan pelkästään
    // sitä, mitä päälle ollaan laittamassa. Tässä kerrotaan kääntäjälle,
    // että ensimmäinen parametreista on tarkoituksella käyttämättä.
    Q_UNUSED(bottom);

    std::string suitString = top.substr(top.find_first_of(",")+1,1);
    return stoi(suitString) == HEART;
}

bool GameRules::checkIfSpade(std::string bottom, std::string top)
{
    Q_UNUSED(bottom);

    std::string suitString = top.substr(top.find_first_of(",")+1,1);

    return stoi(suitString) == SPADE;
}

bool GameRules::checkIfSameSuit(std::string bottom, std::string top)
{
    if(bottom=="")
    {
        return true;
    }
    else
    {
        std::string suitStringTop = top.substr(top.find_first_of(",")+1,1);
        std::string suitStringBot = bottom.substr(bottom.find_first_of(",")+1,1);
        return suitStringTop == suitStringBot;
    }

}
