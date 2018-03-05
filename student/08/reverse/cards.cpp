#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if(top_ == nullptr)
    {
        return false;
    }
    id = top_->data;
    top_ = top_->next;
    return true;
}

void Cards::reverse()
{
    if(top_==nullptr || top_->next==nullptr)
    {
        return;
    }

    std::shared_ptr<Card_data> temptop = top_;

    while(top_->next != nullptr)
    {
        top_ = top_->next;
    }
    std::shared_ptr<Card_data> current = top_;
    std::shared_ptr<Card_data> now = temptop;

    while(current!=temptop)
    {
        while(now->next!=current)
        {
            now = now->next;

        }
        current->next = now;
        current = now;
        now = temptop;
    }
    temptop->next = nullptr;

}





// Älä kirjoita metodien remove ja reverse stubeja tähän itse, 
// vaan avaa tiedosto cards.hh ja klikkaa metodin esittelyä 
// hiiren oikeanpuoleisella näppäimellä ja valitse toiminto 
// Refactor > Add definition in cards.cpp
