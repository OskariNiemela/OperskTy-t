/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * Project Coder: Oskari Niemela
 * Student Number: 263440
 *
 * File: Gamerules.cc
 * Desc:
 *     Contains the code for the win checking
 *
 * Notes:
 *     Assistants made the file originally I just made the
 *     one rule function.
*/

#include "gamerules.hh"
#include "card.hh"



bool GameRules::checkWin(Card *previous, Card *now, int &depth)
{
    // If previous is nullptr it means that its the first check we've ran
    // so we move on to the next one, since we have no particular suit
    // we need to check for.
    if(previous==nullptr)
    {
        depth +=1;
        return checkWin(now,now->getStacked(),depth);
    }

    if((now==nullptr))
    {
        return true;
    }

    // Making these variables makes it a bit more clear what we're checking
    // in the if statement.
    CardSuit prevSuit = previous->getSuit();
    CardSuit nowSuit = now->getSuit();
    unsigned previousVal = previous->getValue();
    unsigned nowVal = now->getValue()+1;

    // Check that the suits are the same, that the value of now is
    // +1 from the previous and that both the cards are open
    if((prevSuit==nowSuit)&&(previousVal==nowVal)&&(previous->isOpen())
            &&(now->isOpen()))
    {
        depth +=1;
        return(checkWin(now,now->getStacked(),depth));
    }
    return false;
}
