// Lähdekooditiedosto: aika.hh
#ifndef AIKA_HH
#define AIKA_HH

#include <string>

using namespace std;

class Aika {
  public:
    Aika(const string& aika = "00.00");
    bool aseta(int tunti, int minuutti);
    bool aseta(const string& ttmm);
    bool kysy(const string& kehote);
    bool pienempi_yhtasuuri(const Aika& vertailtava) const;
    void tulosta() const;

  private:
    int tunti_;
    int min_;
};

#endif
