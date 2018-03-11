// Moduuli: geometria / tiedosto: geometria.cpp
// Moduulin geometria toteutustiedosto: sisältää määrittelyt geometristen 
// kuvioiden laskuihin tarvittaville funktioille.
const double PII = 3.141593;

double nelion_ymparysmitta(double sivu) {
    return 4 * sivu;
}

double nelion_pinta_ala(double sivu) {
    return sivu * sivu;
}

double ympyran_ymparysmitta(double sade) {
    return 2 * PII * sade;
}

double ympyran_pinta_ala(double sade) {
    return PII * sade * sade;
}
