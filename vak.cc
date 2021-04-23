#include "vak.h"
#include <iostream>

using namespace std;

Vak::Vak ()
{ ingeroosterd = false;
}

void Vak::setWaardes(int docentNummer0, int tracks0[], int aantalTracks0, string naam0)
{ int i;
  naam = naam0;
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

bool Vak::zoekTrack (int track) 
{ int i;
  for (i = 0; i < aantalTracks; i++) {
    if (tracks[i] == track) {
      return true;
    }
  }
  return false;
}

bool Vak::getIngeroosterd () 
{
  return ingeroosterd;
}

void Vak::setIngeroosterd ()
{ if (ingeroosterd){
    ingeroosterd = false;
  }
  else {
    ingeroosterd = true;
  }
}