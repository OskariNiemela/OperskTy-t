#ifndef PISARA_HH
#define PISARA_HH

#include <iostream>
#include <vector>
#include <memory>

class Splash;
class GameEngine;

const int MAX_CAPACITY = 4;
const char CHARACTERS[] = {' ', '.', 'o', 'O', '@'};

class Drop
{
public:
    Drop(int x, int y, int waterAmount_, GameEngine* engine);

    // Lisää vettä pisaraan. Jos maksimitilavuus tulee täyteen, pisara poksahtaa.
    // Paluuarvona mahdollisessa poksahduksessa syntyvät uudet roiskeoliot.
    void addWater(std::vector<Splash>& createdSplashes);

    // Tulostaa pisaran kokoa vastaavan merkin annettuun virtaan vesimäärän perusteella
    void print(std::ostream& stream);

    int waterAmount() const;

    int getX() const;

    int getY() const;

  private:
    // Pisaran sijainti laudalla ja vesimäärä
    int x_;
    int y_;
    int waterAmount_;

    // Osoitin pelimoottoriin, jonka laudalla vesipisara sijaitsee
    GameEngine* engine_;
};

#endif // PISARA_HH
