// Definitie van de klasse Vak
// Makers: Lisanne Wallaard (s2865459), Bart den Boef (s2829452)
// Vak: Algoritmiek
// Tweede programmeeropdracht: Rooster
// Studierichting: Kunstmatige Intelligentie
// Jaar van aankomst: 2020
// C++, 7.5.2021, GNU GCC Compiler

#include <string>
#include "constantes.h"
#ifndef VakHVar  // voorkom dat dit bestand meerdere keren
#define VakHVar  // ge-include wordt

class Vak
{ public:
     // Default constructor
     Vak();

     // Voor het inlezen van gegevens naar de private membervariabelen
     void setWaardes(int docentNummer0, int tracks0[], 
                     int aantalTracks0, std::string naam0);
     // Zet ingeroosterd op true (i == 1) of false (i == 0)
     void setIngeroosterd (int i);

     // Vijf 'getters'
     std::string getNaam();
     int getDocentNummer();
     int getAantalTracks();
     int getTrack(int i);
     bool getIngeroosterd ();
     
     // Zoekt een track 'track' de array tracks[]
     bool zoekTrack(int track);
     
  private:
    std::string naam; // de naam van het vak
    int docentNummer, // nummer van de docent die het vak geeft
        aantalTracks; // aantal tracks die dit vak hebben
    int tracks[MaxNrTracks]; // bevat alle tracks die dit vak hebben
    bool ingeroosterd; // een bool om te zien of het vak is ingeroosterd

};

#endif