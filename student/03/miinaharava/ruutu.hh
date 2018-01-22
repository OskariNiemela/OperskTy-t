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
        bool onkoValmis() const;
        bool onkoLippu() const;
        void poistaLippu();
        void lisaaLippu();
        void tulosta(std::ostream &virta) const;
        void tulosta_debug(std::ostream &virta) const;
        bool avaa();
        bool onko_miina();

    private:


        int y_;
        int x_;
        int miinoja_;
        bool lippu_;
        bool miina_;
        bool avattu_;
        vector<vector<Ruutu>>* lauta_;

};

#endif // RUUTU_HH
