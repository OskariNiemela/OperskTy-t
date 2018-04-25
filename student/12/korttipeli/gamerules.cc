/*
 * TIE-02200 Ohjelmoinnin peruskurssi
 * Project: Korttipeli
 * Project Coder: Oskari Niemela
 * Student Number: 263440
 *
 * File: Gamerules.cc
 * Desc:
 *     Contains the code for checking if the land slots are filled,
 *     also contains the code for checking if its legal to move the
 *     cards around the cardslots.
 *
*/

#include "gamerules.hh"
#include "card.hh"



bool GameRules::checkDiffColour(std::string bottom, std::string top,int& topCardVal)
{
    topCardVal = 0;
    //If there is no bottom card to compare with, return true.
    if(bottom=="")
    {
        return true;
    }
    std::string topSuit = top.substr(top.find_first_of(",")+1,1);
    std::string botSuit = bottom.substr(bottom.find_first_of(",")+1,1);

    // If the suit of the top cards colour is black and bottom cards colour is not black
    if((std::find(BLACK.begin(),BLACK.end(),stoi(topSuit))==BLACK.end())
            &&(std::find(BLACK.begin(),BLACK.end(),stoi(botSuit))!=BLACK.end()))
    {
        return true;
    }
    // If the suit of the top cards colour is red and bottom cards colour is not red
    else if((std::find(RED.begin(),RED.end(),stoi(topSuit))==RED.end())
            &&(std::find(RED.begin(),RED.end(),stoi(botSuit))!=RED.end()))
    {
        return true;
    }

    return false;

}

bool GameRules::checkSameLandPlus(std::string bottom, std::string top, int& topCardVal)
{
    // If there is no card here check that the card were trying to put here is
    // of the value 1.
    if(bottom=="")
    {

        std::string topVal = top.substr(0,top.find_first_of(","));
        topCardVal = stoi(topVal);
        if(stoi(topVal)==1)
        {

            return true;
        }
        else
        {
            return false;
        }
    }

    std::string topSuit = top.substr(top.find_first_of(",")+1,1);
    std::string botSuit = bottom.substr(bottom.find_first_of(",")+1,1);

    std::string topVal = top.substr(0,top.find_first_of(","));
    std::string botVal = bottom.substr(0,bottom.find_first_of(","));

    topCardVal = stoi(topVal);
    //  check that the suits are the same and if the value of the card were
    //  adding it +1 the bottom cards.
    if((topSuit==botSuit)&&(stoi(topVal)==stoi(botVal)+1))
    {
        return true;
    }

    return false;
}
