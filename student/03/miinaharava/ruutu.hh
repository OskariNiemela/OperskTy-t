#ifndef RUUTU_HH
#define RUUTU_HH
#include <iostream>
#include <vector>
using std::vector;

class Ruutu
{
    public:

        Ruutu(int x, int y, bool onkomiinaa, vector<vector<Ruutu>>* pelilauta);
        void laskeViereiset();
        bool onkoValmis();
        bool onkoLippu();
        void poistaLippu();
        void lisaaLippu();
        void tulosta(std::ostream &virta);
        bool avaa();
    private:

        int y_;
        int x_;
        bool lippu;
        bool miina_;
        vector<vector<Ruutu>>* lauta_;

};

#endif // RUUTU_HH
