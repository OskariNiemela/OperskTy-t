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
    int lauta_koko = static_cast<int>(lauta_->size());
    lauta_koko--;
    if(not miina_)
    {
     //tarkista onko viereisissä ruuduissa miinoja
        if(y_+1<=lauta_koko)
        {
            if(lauta_->at(y_+1).at(x_).onko_miina())
            {
                miinoja_++;
            }
            if(x_+1<=lauta_koko){
                if(lauta_->at(y_+1).at(x_+1).onko_miina())
                {
                    miinoja_++;
                }

            }
            if(x_-1>=0)
            {
                if(lauta_->at(y_+1).at(x_-1).onko_miina())
                {
                    miinoja_++;
                }
            }
        }
        if(y_-1>=0)
        {
            if(lauta_->at(y_-1).at(x_).onko_miina())
            {
                miinoja_++;
            }
            if(x_+1<=lauta_koko)
            {
                if(lauta_->at(y_-1).at(x_+1).onko_miina())
                {
                    miinoja_++;
                }
            }
            if(x_-1>=0)
            {
                if(lauta_->at(y_-1).at(x_-1).onko_miina())
                {
                    miinoja_++;
                }
            }
        }
        if(x_-1>=0)
        {
            if(lauta_->at(y_).at(x_-1).onko_miina())
            {
                miinoja_++;
            }
        }
        if(x_+1<=lauta_koko)
        {
            if(lauta_->at(y_).at(x_+1).onko_miina()){
                miinoja_++;
            }

        }

    }
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
        virta<<miinoja_;
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
        virta<<miinoja_;
    }else if(lippu_){
        virta<<'P';
    }
    else{
        virta<<'.';
    }
}

bool Ruutu::avaa()
{
    return false;
}
