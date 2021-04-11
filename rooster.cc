// Implementatie van klasse Rooster
//lisanne was hier en bart
// JE DOET HET VERKEERD

#include <iostream>
#include <fstream>
#include <string>
#include "standaard.h"
#include "rooster.h"
#include "docent.h"
#include "vak.h"

using namespace std;

//*************************************************************************

// Default constructor
Rooster::Rooster ()
{ 
  

}  // default constructor

//*************************************************************************

bool Rooster::leesIn (const char* invoerNaam)
{ int i, j;
  ifstream fin;
  int tijdsloten0[MaxNrTijdsloten];
  int aantalTijdsloten0;
  string naam0;
  int docentNummer0, aantalTracks0;
  int tracks0[MaxNrTracks];

  fin.open (invoerNaam);
  if (fin.fail ()) {
    cout << invoerNaam << " kan ik niet openen." << endl;
    return false;
  }//if
  fin >> nrDagen >> nrUrenPerDag >> nrZalen;
  fin >> nrDocenten;
  for (i = 0; i < nrDocenten; i++) {
    fin >> aantalTijdsloten0;
    for (j = 0; j < aantalTijdsloten0; j++) {
      fin >> tijdsloten0[j];
    }
    Docent docent;
    docent.setWaardes(i, tijdsloten0, aantalTijdsloten0);
    docenten[i] = docent;
  }
  
  fin >> nrVakken;
  for (i = 0; i < nrVakken; i++) {
    fin >> naam0;
    fin >> docentNummer0 >> aantalTracks0;
    for (j = 0; j < aantalTracks0; j++) {
      fin >> tracks0[j];
    }
    Vak vak;
    vak.setWaardes(docentNummer0, tracks0, aantalTracks0, naam0);
    vakken[i] = vak;
  }
  
  return true;

}  // leesIn

//*************************************************************************

void Rooster::drukAf ()
{ int i, j;
  cout << "Aantal dagen: " << nrDagen << endl
       << "Aantal uren per dag: " << nrUrenPerDag << endl
       << "Aantal zalen: " << nrZalen << endl
       << "Aantal docenten " << nrDocenten << endl
       << "Aantal vakken: " << nrVakken << endl << endl;
  
  for (i = 0; i < nrDocenten; i++) {
    cout << "Docent " << docenten[i].getNummer() << ":" << endl
         << "Aantal tijdsloten: " << docenten[i].getAantalTijdsloten() << endl
         << "Tijdsloten: ";
    for (j = 0; j < docenten[i].getAantalTijdsloten(); j++) {
      cout << docenten[i].getTijdslot(j) << " ";
    }
    cout << endl << endl;
  }

  for (i = 0; i < nrVakken; i++) {
    cout << "Vak: " << vakken[i].getNaam() << endl
         << "Docent: " << vakken[i].getDocentNummer() << endl
         << "Aantal tracks: " << vakken[i].getAantalTracks() << endl
         << "Tracks: ";
    for (j = 0; j < vakken[i].getAantalTracks(); j++) {
      cout << vakken[i].getTrack(j) << " ";
    }
    cout << endl << endl;
  }
    
}  // drukAf ()

//*************************************************************************

bool Rooster::bepaalRooster (int rooster[MaxNrTijdsloten][MaxNrZalen],
                        long long &aantalDeelroosters)
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // bepaalRooster

//*************************************************************************

bool Rooster::bepaalMinRooster (int rooster[MaxNrTijdsloten][MaxNrZalen],
                        long long &aantalDeelroosters)
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // bepaalMinRooster
  
//*************************************************************************

void Rooster::drukAfRooster (int rooster[MaxNrTijdsloten][MaxNrZalen])
{
  // TODO: implementeer deze memberfunctie

}  // drukAfRooster

//*************************************************************************

void Rooster::bepaalRoosterGretig (int rooster[MaxNrTijdsloten][MaxNrZalen])
{
  // TODO: implementeer deze functie

}  // bepaalRoosterGretig

