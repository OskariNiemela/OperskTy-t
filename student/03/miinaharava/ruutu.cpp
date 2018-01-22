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
        int lauta_koko = static_cast<int>(lauta_->size());
        lauta_koko--;
        int y= 0;
        int x= 0;
        int myarray[8][2] = {{1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,+1},{-1,0},{-1,-1}};
        int coord[2] ={};
        for(int i=0;i<8;i++)
        {
            coord[0] = myarray[i][0];
            coord[1] = myarray[i][1];
            y=coord[0];
            x=coord[1];
            if((y_+y<=lauta_koko)&&(x_+x<=lauta_koko)&&(y_+y>=0)&&(x_+x>=0))
            {
                if(lauta_->at(y_+y).at(x_+x).onko_miina())
                {
                    miinoja_++;
                }
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



//Tulostaa oman ruudun kuvakkeen tällä hetkellä
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
    if(not avattu_)
    {
        if(miina_){
            avattu_ =true;
            return false;
        }else if(miinoja_==0){
            avattu_ = true;
            //jos miinoja ympärillä on nolla
            //avataan viereiset ruudut
            int lauta_koko = static_cast<int>(lauta_->size());
            lauta_koko--;
            int y= 0;
            int x= 0;
            int myarray[8][2] = {{1,1},{1,0},{1,-1},{0,1},{0,-1},{-1,+1},{-1,0},{-1,-1}};
            int coord[2] ={};
            for(int i=0;i<8;i++)
            {
                coord[0] = myarray[i][0];
                coord[1] = myarray[i][1];
                y=coord[0];
                x=coord[1];
                if((y_+y<=lauta_koko)&&(x_+x<=lauta_koko)&&(y_+y>=0)&&(x_+x>=0))
                {
                    lauta_->at(y_+y).at(x_+x).avaa();
                }
            }
            avattu_ = true;
            return true;
        }else{
            avattu_ = true;
            return true;
        }
    }else{
        return true;
    }
}
