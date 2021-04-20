// Implementatie van klasse Rooster

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
{ nrTracks = 0;
  

}  // default constructor

//*************************************************************************

bool Rooster::leesIn (const char* invoerNaam)
{ int i, j;
  ifstream fin;
  bool tussenuurTracks[MaxNrTracks];
  int tijdsloten0[MaxNrTijdsloten];
  int aantalTijdsloten0;
  string naam0;
  int docentNummer0, aantalTracks0;
  int tracks0[MaxNrTracks];
  
  resetBool (tussenuurTracks, MaxNrTracks);
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
      if (tussenuurTracks[tracks0[j]] == false) {
        tussenuurTracks[tracks0[j]] = true;
        nrTracks++;
      }
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
       << "Aantal vakken: " << nrVakken << endl
       << "Aantal tracks: " << nrTracks << endl << endl;
  
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

bool Rooster::zelfdeDocent (int docent, Vak vak) 
{ if (docent == vak.getDocentNummer()) {
    return true;
  }
  return false;
}

void Rooster::resetBool (bool A[], int n)
{ int i;
  for (i = 0; i < n; i++){
    A[i] = false;
  }
}

void Rooster::resetInt (int A[], int n)
{ int i;
  for (i = 0; i < n; i++){
    A[i] = 0;
  }
}

bool Rooster::zelfdeTrack (Vak A, Vak B)
{ int i, j;
  for(i = 0; i < A.getAantalTracks(); i++) {
    for(j = 0; j < B.getAantalTracks(); j++) {
      if (A.getTrack(i) == B.getTrack(j)) {
        return true;
      }
    }
  }
  return false;
}

bool Rooster::geeftAlCollege(int docent, int tijdslot, 
                             int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int dag = tijdslot / nrUrenPerDag;
  int i;
  for (i = (dag * nrUrenPerDag); i < ((dag+1) * nrUrenPerDag); i++) {
    if (vakken[rooster[i][1]].getDocentNummer() == docent) {
      return true;
    }
    if (vakken[rooster[i][2]].getDocentNummer() == docent) {
      return true;
    } 
  }
  return false;
}

bool Rooster::minUren (int tijdslot, int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int dag = (tijdslot / nrUrenPerDag);
  int i, j;
  int trackTeller[MaxNrTracks]; 
  resetInt (trackTeller, MaxNrTracks);
  for (i = (dag * nrUrenPerDag); i < ((dag+1) * nrUrenPerDag); i++) { 
    if (rooster[i][1] != -1 && rooster[i][1] != 100) {
      for (j = 0; j < vakken[rooster[i][1]].getAantalTracks(); j++){
        trackTeller[vakken[rooster[i][1]].getTrack(j)]++;
      }
    }
    else if (rooster[i][2] != -1 && rooster[i][2] != 100) {
      for (j = 0; j < vakken[rooster[i][2]].getAantalTracks(); j++){
        trackTeller[vakken[rooster[i][2]].getTrack(j)]++;
      }
    }
  }
  for (i = 0; i < MaxNrTracks; i++){
    if (trackTeller[i] == 1) {
      return false;
    }
  }
  return true;
}

bool Rooster::aantalTussenuren ()
{ //int i;
  //for (i == 0; )
  return false;
}

bool Rooster::bepaalRooster (int rooster[MaxNrTijdsloten][MaxNrZalen],
                        long long &aantalDeelroosters)
{ int i= 0, j= 0;
  int r, s;
  bool ok = false;
  bool ingeroosterd[nrVakken];
  resetBool (ingeroosterd, nrVakken);
  aantalDeelroosters++;
  while (rooster[i][j] != -1 && i < nrDagen * nrUrenPerDag) {
    j++;
    if (rooster[i][j] != -1) { 
      i++;
      j--;
    }
  }
  
  if (i >= nrDagen * nrUrenPerDag) {
    return true;
  }

  while (!ok) {
    for (r = 0; r < nrDocenten; r++) {
      if (docenten[r].zitErin(i)) {
        for (s = 0; s < nrVakken; s++){
          if(docenten[r].getNummer() == vakken[s].getDocentNummer() && 
             ingeroosterd[s] == false) {
            if (j == 1 && rooster[i][2] != -1 && rooster[i][2] != 100
                && zelfdeTrack (vakken[s], vakken[rooster[i][2]])){
              cout << "Twee vakken van dezelfde track op 1 tijdstip." << endl;
            }
            else if (j == 2 && rooster[i][1] != -1 && rooster[i][1] != 100
                     && zelfdeTrack (vakken[s], vakken[rooster[i][2]])) {
              cout << "Twee vakken van dezelfde track op 1 tijdstip." << endl;          
            }
            if (geeftAlCollege(vakken[s].getDocentNummer(), i, rooster)){
              cout << "Docent geeft al les vandaag." << endl;
            }
            if ((i + 1) % nrUrenPerDag == 0 && minUren(i, rooster)) {
              cout << "De studenten mogen niet voor 1 vak" 
                   << "naar de Universiteit komen" << endl;
            }

            
            
            //hulpfuncties, mag dit?
            rooster[i][j] = s;
            ingeroosterd[s] = true;
            if (bepaalRooster(rooster, aantalDeelroosters)){
              ok = true;
            }
            else {
              rooster[i][j] = -1;
            }
          }
        }
      }
    }
    //tussenuur
    if (rooster[i][j] == -1) {
      rooster[i][j] = 100;
      if (bepaalRooster(rooster, aantalDeelroosters)){
        ok = true;
      }
      else {
        return false;
      }
    }
  }
  
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

