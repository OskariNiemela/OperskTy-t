/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * File: gamerules.hh
 * Coder: Oskari Niemela
 * Student Number: 263440
 *
 * Desc:
 *      Header file for the gamerules.cc file.,
 *      Contains declarations for the rule method
 *      were using to judge whether the player wins
 *      the game.
 *
 * Notes:
 *      Assistants made the file originally I just made the
 *      one rule function.
*/

#ifndef GAMERULES_HH
#define GAMERULES_HH
#include <string>
#include "card.hh"

namespace GameRules {
    // Checks if the conditions for winning are met. In this instance
    // checks if all the cards are the same suit, plus checks that theyre
    // all in order from 13->1,
    //
    // Param0: the previous card that was checked
    // Param1: the card we need to check now
    // Param2: how many cards have been checked so far,
    //
    // Returns whether all the cards have been stacked correctly
    bool checkWin(Card* previous,Card* now,int &depth);
}

#endif // GAMERULES_HH
