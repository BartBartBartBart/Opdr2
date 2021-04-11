// Definitie van de klasse Vak

#include <string>

#ifndef VakHVar  // voorkom dat dit bestand meerdere keren
#define VakHVar  // ge-include wordt

class Vak
{ public:
     Vak(int docentNummer0, int tracks0[], int aantalTracks0, int naam0[], int n);
  private:
    char naam[31];
    int docentNummer; 
    int aantalTracks;
    int tracks[aantalTracks];

}

#endif