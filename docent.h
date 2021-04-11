// Definitie van de klasse Docent

#include "constantes.h"
#ifndef DocentHVar  // voorkom dat dit bestand meerdere keren
#define DocentHVar  // ge-include wordt

class Docent
{ public:
    Docent();
    void setWaardes(int nummer0, int tijdsloten0[], int aantalTijdsloten0);
    
    int getNummer();
    int getAantalTijdsloten();
    int getTijdslot(int i);

  private:
    int nummer;
    int aantalTijdsloten;
    int tijdsloten[MaxNrTijdsloten];

};

#endif