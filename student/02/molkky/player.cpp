#include "player.hh"
#include <string>
#include <iostream>

Player::Player(std::string name)
{
    name_ = name;
    score_ = 0;
}

bool Player::has_won()
{
    if (score_ == 50){
        return true;
    }

    return false;
}

void Player::add_points(int pts)
{
    score_+=pts;

    if (score_ > 50){
        std::cout<<name_<<" gets penalty points!"<<std::endl;
        score_ = 25;
    }

}

std::string Player::get_name()
{
    return name_;
}

int Player::get_points()
{
    return score_;
}
