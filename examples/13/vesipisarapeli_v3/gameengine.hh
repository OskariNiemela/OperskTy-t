#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "gameboard.hh"

#include "drop.hh"
#include "splash.hh"
#include <iostream>
#include <vector>
#include <memory>

const int SIZE = 6;

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine(GameBoard& gameBoard, int seed = 0);

    // Alustaa uuden pelin.
    void initialize();

    // Tarkastaa, onko peli loppunut, eli onko pelilauta tyhjä pisaroista
    bool isEmpty() const;

    // Pisaran pitää pystyä tuhoutuessaan poistamaan itsensä laudalta.
    void removeDrop(int x, int y);

    // Noutaa pisara-olion annetuissa koordinaateissa laudalta.
    std::shared_ptr<Drop> dropAt(int x, int y) const;

signals:
    // Lähetetään, kun peli halutaan sulkea.
    void quitGame();

public slots:
    // Aktivoidaan, kun laudalle halutaan lisätä vettä annettuun kohtaan.
    void addWater(int x, int y);

private:
    // Siirtää jokaista laudalla olevaa roisketta yhden ruudun eteenpäin.
    void moveSplashes(std::vector<std::shared_ptr<Drop> >& removedDrops);

    // Tulostaa pelilaudan annettuun virtaan animoiden roiskeiden lennon
    void print(std::ostream& stream, std::vector<Splash>& splashes);

    // Tulostusmetodin käyttämä apumetodi
    char droplessSquareChar(int x, int y, std::vector<Splash> &splashes);

    // Käytettävä pelilauta.
    std::vector< std::vector< std::shared_ptr<Drop> > > board_;

    // Pelissä olevat roiskeet.
    std::vector< Splash > splashes_;

    // Piirtoalue, jolla näyttää pelitilanne.
    GameBoard& graphicalGameBoard_;

    // Käytettävissä oleva veden määrä.
    int waterTank_;
};

#endif // GAMEENGINE_H
