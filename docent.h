// Definitie van de klasse Docent
// Makers: Lisanne Wallaard (s2865459), Bart den Boef (s2829452)
// Vak: Algoritmiek
// Tweede programmeeropdracht: Rooster
// Studierichting: Kunstmatige Intelligentie
// Jaar van aankomst: 2020
// C++, 7.5.2021, GNU GCC Compiler

#include "constantes.h"
#ifndef DocentHVar  // voorkom dat dit bestand meerdere keren
#define DocentHVar  // ge-include wordt

class Docent
{ public:
    // Default constructor
    Docent();

    // Voor het inlezen van gegevens naar de private membervariabelen
    void setWaardes(int nummer0, int tijdsloten0[], int aantalTijdsloten0);
    
    // Drie 'getters'
    int getNummer();
    int getAantalTijdsloten();
    int getTijdslot(int i);
    
    // Controleert of de docent op 'tijdslot' kan lesgeven
    bool zitErin (int tijdslot);

  private:
    int nummer, // docentnummer
        aantalTijdsloten; // aantal tijdsloten in de array tijdsloten[]
    int tijdsloten[MaxNrTijdsloten]; // bevat alle tijdsloten waarop de docent
                                     // les kan geven

};

#endif