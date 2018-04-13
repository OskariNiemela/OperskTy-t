#ifndef GAMERULES_HH
#define GAMERULES_HH
#include <string>

namespace GameRules {

    // Tarkastusfunktio, joka varmistaa, että päälle laitetaan vain herttaa.
    bool checkIfHeart(std::string bottom, std::string top);
}

#endif // GAMERULES_HH
