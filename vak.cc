#include "vak.h"
#include <iostream>

using namespace std;

Vak::Vak ()
{ ingeroosterd = false;
  int i;
  for (i = 0; i < MaxNrTijdsloten; i++) {
    tijdsloten[i] = true;
  }
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

void Vak::setIngeroosterd (int i)
{ if (i == 0){
    ingeroosterd = false;
  }
  else if (i == 1) {
    ingeroosterd = true;
  }
}

void Vak::setTijdsloten (int tijdslot, int j)
{
  if (j == 1) {
    tijdsloten[tijdslot] = true;
  }
  else {
    tijdsloten[tijdslot] = false;
  }
}

bool Vak::getTijdslot(int i)
{ 
  return tijdsloten[i];
}