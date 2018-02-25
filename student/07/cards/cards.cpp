#include "cards.hh"

// TODO: Implement the methods here
Cards::Cards()
{
    top_ = nullptr;
}

void Cards::add(int id)
{
    Card_data* new_card = new Card_data;
    new_card->data = id;
    new_card->next = top_;

    top_ = new_card;
}


void Cards::print_from_top_to_bottom(std::ostream &s)
{
    if(top_ != nullptr)
    {
        int order = 0;
        Card_data* print_card = top_;
        while(print_card!= nullptr)
        {
         s<<order<<':'<<' '<<print_card->data<<std::endl;
         order++;
         print_card = print_card->next;
        }
    }

}

bool Cards::remove(int &id)
{
    if(top_ == nullptr)
    {
        return false;
    }

    Card_data* remove_card = top_;

    id = remove_card->data;
    top_ = remove_card->next;
    delete remove_card;

    return true;

}

bool Cards::bottom_to_top()
{
    if(top_ == nullptr)
    {
        return false;
    }
    else if (top_->next == nullptr)
    {
        return true;
    }



    Card_data* new_bottom_card = top_;
    Card_data* bottom_card = top_->next;

    while(bottom_card->next != nullptr)
    {
        new_bottom_card = bottom_card;
        bottom_card = bottom_card->next;
    }

    bottom_card->next = top_;
    top_ = bottom_card;
    new_bottom_card->next = nullptr;

    return true;

}

bool Cards::top_to_bottom()
{
    if(top_ == nullptr)
    {
        return false;
    }

    Card_data* switched_card;
    switched_card = top_;

    if(switched_card->next == nullptr)
    {
        return true;
    }
    top_ = switched_card->next;

    Card_data* bottom_card = top_;

    while(bottom_card->next != nullptr)
    {
        bottom_card = bottom_card->next;
    }

    switched_card->next = nullptr;
    bottom_card->next = switched_card;

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    if(top_!=nullptr)
    {
        recursive_print(top_,s);
    }
}

Cards::~Cards()
{
    Card_data* card_index;
    while(top_!=nullptr)
    {
     card_index = top_;
     top_ = card_index->next;
     delete card_index;
    }
}

int Cards::recursive_print(Cards::Card_data *top, std::ostream &s)
{
    int order = 1;

    if(top->next==nullptr)
    {
        s<<order<<':'<<' '<<top->data<<std::endl;
        return order;
    }
    else
    {
        order = recursive_print(top->next,s)+1;
        s<<order<<':'<<' '<<top->data<<std::endl;
        return order;
    }
}

