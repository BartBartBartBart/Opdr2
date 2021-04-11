#include "vak.h"

using namespace std;

Vak::Vak (int docentNummer0, int tracks0[], int aantalTracks0, int naam0[], int n)
{ int i;
  for (i = 0; i < n; i++) {
    naam[i] = naam0[i];  
  }
  
  docentNummer = docentNummer0;
  aantalTracks = aantalTracks0;
  
  for (i = 0; i < aantalTracks; i++) {
    tracks[i] = tracks0[i];
  }
}