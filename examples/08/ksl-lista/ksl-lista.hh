#ifndef KSL_LISTA_HH
#define KSL_LISTA_HH

#include <memory>

using namespace std;

class KSL_lista { // Kahteen Suuntaan Linkitetty lista
  public:
    KSL_lista();
    int pituus() const;
    bool onko_arvo_listassa(int arvo) const;
    void tulosta() const;
    void tulosta_takaperin() const;
    bool poista_arvo(int poistettava);
    bool lisaa_numerojarjestykseen(int lisattava);
    // Ei-purkajaa(!)

  private:
    struct Listan_alkio {
        int                       data;
        shared_ptr<Listan_alkio>  seuraavan_osoite;
        Listan_alkio*             edellisen_osoite;
    };

    shared_ptr<Listan_alkio> ensimmaisen_osoite_;
    Listan_alkio*            viimeisen_osoite_;
    int                      alkioiden_maara_;
};

#endif
