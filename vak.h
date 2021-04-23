// Definitie van de klasse Vak

#include <string>
#include "constantes.h"
#ifndef VakHVar  // voorkom dat dit bestand meerdere keren
#define VakHVar  // ge-include wordt

class Vak
{ public:
     Vak();
     void setWaardes(int docentNummer0, int tracks0[], int aantalTracks0, std::string naam0);
     
     std::string getNaam();
     int getDocentNummer();
     int getAantalTracks();
     int getTrack(int i);
     bool zoekTrack(int track);
     bool getIngeroosterd ();
     void setIngeroosterd ();
    

  private:
    std::string naam;
    int docentNummer; 
    int aantalTracks;
    int tracks[MaxNrTracks];
    bool ingeroosterd;

};

#endif