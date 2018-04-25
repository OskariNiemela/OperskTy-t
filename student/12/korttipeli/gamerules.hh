/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * File: gamerules.hh
 * Coder: Oskari Niemela
 * Student Number: 263440
 *
 * Desc:
 *      Header file for the gamerules namespace.
 *      gamerules are the functions used to check if moves are legal.
 *
*/

#ifndef GAMERULES_HH
#define GAMERULES_HH
#include <string>
#include "card.hh"


std::vector<CardSuit> const BLACK = {SPADE,CLUB};
std::vector<CardSuit> const RED = {HEART,DIAMOND};

namespace GameRules {
    // Checks that the given cards are different colours.
    //
    // Param0: the data of the card thats on the pile
    // Param1: the data of the card were trying to add to the pile
    // Param2: the value of the card we're trying to add, however this is only
    //        needed when checking if we've succesfully stacked all the cards
    //        of the same land, so we'll just return 0 as the value in this method.
    //        the only reason it is even in this method is because we need to use the
    //        CheckFunction type structure in the cardslots and the two methods have to
    //        have the same type of parameters for that to work.
    //
    // Return: Returns whether the cards are different colours

    bool checkDiffColour(std::string bottom, std::string top,int &topCardVal);

    // Checks that the added card is of the same land and has the value of the existing top
    // card+1
    //
    // Param0: the data of the card thats on the pile
    // Param1: the data of the card were trying to add to the pile
    // Param2: the value of the card we're trying to add, this value is changed
    //        to the value of the card we're trying to add so that the cardslot we're doing
    //        this check for knows whether or not it's got all the cards from a land.
    //
    // returns whether or not


    bool checkSameLandPlus(std::string bottom, std::string top, int &topCardVal);
}

#endif // GAMERULES_HH
