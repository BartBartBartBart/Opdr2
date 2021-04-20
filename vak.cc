#include "vak.h"
#include <iostream>

using namespace std;

Vak::Vak ()
{ 
}

void Vak::setWaardes(int docentNummer0, int tracks0[], int aantalTracks0, string naam0)
{ int i;
  //for (i = 0; i < n; i++) {
  //  naam[i] = naam0[i];  
  //}
  //cout << "HALLO" << endl;
  naam = naam0;
  //cout << "DOEI" << endl;
  docentNummer = docentNummer0;
  aantalTracks = aantalTracks0;
  
  for (i = 0; i < aantalTracks; i++) {
    tracks[i] = tracks0[i];
  }

}

string Vak::getNaam () 
{
  return naam;
}

int Vak::getDocentNummer () 
{
  return docentNummer;
}

int Vak::getAantalTracks ()
{
  return aantalTracks;
}

int Vak::getTrack (int i)
{
  return tracks[i];
}