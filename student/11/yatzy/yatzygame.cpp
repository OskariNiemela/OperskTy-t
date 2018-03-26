#include "yatzygame.hh"
#include "yatzyrules.hh"

#include <algorithm>
#include <cstdlib>
#include <ctime>

#include <iostream>


YatzyGame::YatzyGame(unsigned int seedValue) :
    rollsLeft_(YatzyRules::ROLLS_PER_TURN),
    dieRolls_(YatzyRules::NUMBER_OF_DICE, 1),
    keepDie_(YatzyRules::NUMBER_OF_DICE, false),
    scores_()
{    
    // Required for random number generation in roll().
    if(seedValue == 0) {
        // If there was no seed value given as a parameter for the
        // constructor, use a seed value from the clock.
        randomEngine_.seed(time(NULL));
    } else {
        // Otherwise use the seed value given as a parameter.
        randomEngine_.seed(seedValue);
    }
}

YatzyGame::~YatzyGame()
{

}

unsigned int YatzyGame::getNumberOfRollsLeft() const
{
    return rollsLeft_;
}

std::vector<unsigned int> YatzyGame::roll()
{
    for (int dieNumber = 0; dieNumber < YatzyRules::NUMBER_OF_DICE; dieNumber++)
    {
        if (keepDie_.at(dieNumber) == false)
        {
            // Roll a random number in range 1-6.
            std::uniform_int_distribution<int> distribution (1,6);
            int rollNumber = distribution(randomEngine_);
            dieRolls_[dieNumber] = rollNumber;
        }
    }

    rollsLeft_--;

    return dieRolls_;
}

bool YatzyGame::canKeep(unsigned int dieNumber) const
{
    return 0 < rollsLeft_ && rollsLeft_ <= YatzyRules::ROLLS_PER_TURN - 1 && keepDie_.at(dieNumber) == false;
}

void YatzyGame::keepRoll(unsigned int dieNumber)
{
    keepDie_[dieNumber] = true;
}

bool YatzyGame::canScore(YatzyRules::ScoreCombination combination) const
{
    return rollsLeft_ <= YatzyRules::ROLLS_PER_TURN - 1 && scores_.count(combination) == 0;
}

unsigned int YatzyGame::scoreOnes()
{
    unsigned int score = std::count(dieRolls_.cbegin(), dieRolls_.cend(), 1);

    scores_.insert({YatzyRules::ONES, score});
    resetRolls();

    return score;
}

unsigned int YatzyGame::scoreOnePair()
{
    unsigned int score = 0;

    for (int i = 0; i < YatzyRules::NUMBER_OF_DICE; i++)
    {
        for (int j = i + 1; j< YatzyRules::NUMBER_OF_DICE; j++)
        {
            if (dieRolls_.at(i) == dieRolls_.at(j))
            {
                score = std::max(dieRolls_.at(i)*2, score);
            }
        }
    }

    scores_.insert({YatzyRules::ONE_PAIR, score});
    resetRolls();

    return score;
}

unsigned int YatzyGame::scoreTwoPairs()
{
    unsigned int score = 0;
    unsigned int firstPair = 0;
    for (int i = 0; i < YatzyRules::NUMBER_OF_DICE; i++)
    {
        for (int j = i + 1; j< YatzyRules::NUMBER_OF_DICE; j++)
        {
            if ((dieRolls_.at(i) == dieRolls_.at(j))&&(dieRolls_.at(i)!=firstPair))
            {
                if(firstPair==0)
                {
                    firstPair = dieRolls_.at(i);
                }
                else
                {
                    score = std::max(dieRolls_.at(i)*2+firstPair*2, score);

                    if(dieRolls_.at(i)>firstPair)
                    {
                        firstPair = dieRolls_.at(i);
                    }
                }

            }
        }
    }

    scores_.insert({YatzyRules::TWO_PAIRS, score});
    resetRolls();

    return score;
}

unsigned int YatzyGame::scoreYatzy()
{
    unsigned int score = 0;
    for (int i = 0; i < YatzyRules::NUMBER_OF_DICE; i++)
    {
        for (int j = i + 1; j< YatzyRules::NUMBER_OF_DICE; j++)
        {
            if (dieRolls_.at(i) != dieRolls_.at(j))
            {
                scores_.insert({YatzyRules::YATZY, score});
                resetRolls();

                return score;
            }
        }
    }
    score = 50;
    scores_.insert({YatzyRules::YATZY, score});
    resetRolls();

    return score;
}

unsigned int YatzyGame::scoreSmallStraight()
{
    unsigned int score = 0;
    std::map<unsigned int,bool> map;
    map[1] = false;
    map[2] = false;
    map[3] = false;
    map[4] = false;
    map[5] = false;
    for (int i = 0; i < YatzyRules::NUMBER_OF_DICE; i++)
    {
        if(map.find(dieRolls_.at(i))!=map.end())
        {
            map[i] = true;
        }
        else
        {
            scores_.insert({YatzyRules::SMALL_STRAIGHT, score});
            resetRolls();

            return score;
        }
    }

    score = 15;
    scores_.insert({YatzyRules::SMALL_STRAIGHT, score});
    resetRolls();

    return score;

}

unsigned int YatzyGame::getTotalScore() const
{
    unsigned int total = 0;

    for (std::map<YatzyRules::ScoreCombination, unsigned int>::const_iterator iter = scores_.cbegin();
         iter != scores_.cend();
         iter++)
    {
        total += iter->second;
    }

    return total;
}

void YatzyGame::reset()
{
    scores_.clear();
    resetRolls();
}

void YatzyGame::resetRolls()
{
    rollsLeft_ = YatzyRules::ROLLS_PER_TURN;

    for (int i = 0; i < YatzyRules::NUMBER_OF_DICE; i++)
    {
        keepDie_[i] = false;
    }
}
