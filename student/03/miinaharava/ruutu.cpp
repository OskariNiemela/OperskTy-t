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

//Laskee viereisten ruutujen miinat ja laittaa määrän muistiin
void Ruutu::laskeViereiset()
{
    int lauta_koko = static_cast<int>(lauta_->size());
    lauta_koko--;
    //tarkista jos ruudussa ei ole miinaa
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
//Onko tämä ruutu "valmis", eli tarkistaa onko joko
//1) ruudussa on miina ja lippu jolloin ruutu on valmis
//2) ruudussa on lippu mutta ei miinaa, jolloin ruutu ei ole valmis
//3) ruudussa on miina mutta ei lippua, jolloin ruutu ei ole valmis
//muissa tapauksissa ruutu on valmis
bool Ruutu::onkoValmis() const
{
    if((lippu_)&&(miina_))
    {
        return true;
    }else if (lippu_){
        return false;
    }else if((miina_)&&(not lippu_))
    {
        return false;
    }
    return true;
}
//Kertoo onko oliolla lippu
bool Ruutu::onkoLippu() const
{
    return lippu_;
}
//postaa lipun oliolta
void Ruutu::poistaLippu()
{
    lippu_ = false;
}
//lisää ruutuun lipun
void Ruutu::lisaaLippu()
{
    lippu_ = true;
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
//Kertoo onko ruudussa miina
//kaytetaan ymparoivien miinojen laskuun
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

//Avaa kyseisen ruudun, ja palauttaa arvoksi true jos ruudussa ei ollut pommia
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
            return true;
        }else{
            avattu_ = true;
            return true;
        }
    }else{
        return true;
    }
}
