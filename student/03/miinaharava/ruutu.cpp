#include "ruutu.hh"
#include <iostream>
#include <vector>
Ruutu::Ruutu(int x, int y, bool onkomiinaa, vector<vector<Ruutu>>* pelilauta)
{
    miinoja_ = 0;
    avattu_ = false;
    lippu_ = false;
    x_ = x;
    y_ = y;
    miina_ = onkomiinaa;
    lauta_ = pelilauta;
}

void Ruutu::laskeViereiset()
{

}
bool Ruutu::onkoValmis() const
{
    return false;
}

bool Ruutu::onkoLippu() const
{
    return false;
}

void Ruutu::poistaLippu()
{

}
void Ruutu::lisaaLippu()
{

}

/*     --------Debug methods--------             */
void Ruutu::tulosta_debug(std::ostream& virta) const
{
    if(miina_){
        virta<<'*';
    }else{
        virta<<'.';
    }
}

/*-----------------------------------------------*/
bool Ruutu::onko_miina()
{
    if (miina_){
        return true;
    }
    return false;
}




void Ruutu::tulosta(std::ostream& virta) const
{
    if(avattu_){
        //virta<<miinoja_;
    }else{
        virta<<'.';
    }
}

bool Ruutu::avaa()
{
    return false;
}
