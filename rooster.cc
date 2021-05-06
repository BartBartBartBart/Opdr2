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
{ 
  nrTracks = 0;

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
  resetInt (vakkenPerTrack, MaxNrTracks);
  resetBool (tussenuurTracks, MaxNrTracks);

  fin.open (invoerNaam);
  if (fin.fail ()) {
    cout << invoerNaam << " kan ik niet openen." << endl;
    return false;
  }//if

  fin >> nrDagen >> nrUrenPerDag >> nrZalen;
  nrTijdsloten = nrDagen * nrUrenPerDag;
  fin >> nrDocenten;
  for (i = 0; i < nrDocenten; i++) {
    fin >> aantalTijdsloten0;

    for (j = 0; j < aantalTijdsloten0; j++) {
      fin >> tijdsloten0[j];
    }//for

    Docent docent;
    docent.setWaardes(i, tijdsloten0, aantalTijdsloten0);
    docenten[i] = docent;
  }//for
  
  fin >> nrVakken;
  for (i = 0; i < nrVakken; i++) {
    fin >> naam0;
    fin >> docentNummer0 >> aantalTracks0;

    for (j = 0; j < aantalTracks0; j++) {
      fin >> tracks0[j];
      vakkenPerTrack[tracks0[j]]++;

      if (tussenuurTracks[tracks0[j]] == false) {
        tussenuurTracks[tracks0[j]] = true;
        nrTracks++;
      }//if

    }//for
    Vak vak;
    vak.setWaardes(docentNummer0, tracks0, aantalTracks0, naam0);
    vakken[i] = vak;

  }//for
  
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
    }//for
    cout << endl << endl;
  }//for

  for (i = 0; i < nrVakken; i++) {
    cout << "Vak: " << vakken[i].getNaam() << endl
         << "Docent: " << vakken[i].getDocentNummer() << endl
         << "Aantal tracks: " << vakken[i].getAantalTracks() << endl
         << "Tracks: ";
    for (j = 0; j < vakken[i].getAantalTracks(); j++) {
      cout << vakken[i].getTrack(j) << " ";
    }//for
    cout << endl << endl;
  }//for
    
}  // drukAf 

//*************************************************************************

bool Rooster::zelfdeDocent (int docent, Vak vak) 
{ 
  if (docent == vak.getDocentNummer()) {
    return true;
  }//if

  return false;

}  // zelfdeDocent

void Rooster::resetBool (bool A[], int n)
{ int i;

  for (i = 0; i < n; i++){
    A[i] = false;
  }//for

}  // resetBool

void Rooster::resetInt (int A[], int n)
{ int i;

  for (i = 0; i < n; i++){
    A[i] = 0;
  }//for

}  // resetInt

bool Rooster::zelfdeTrack (Vak A, Vak B)
{ int i, j;

  for (i = 0; i < A.getAantalTracks(); i++) {
    for (j = 0; j < B.getAantalTracks(); j++) {
      if (A.getTrack(i) == B.getTrack(j)) {
        return true;
      }//if
    }//for
  }//for

  return false;

}  // zelfdeTrack

bool Rooster::geeftAlCollege(int docent, int tijdslot, int zaal,
                             int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int dag = tijdslot / nrUrenPerDag;
  int i, j;

  for (i = (dag * nrUrenPerDag); i < ((dag+1) * nrUrenPerDag); i++) {
    for (j = 0; j < nrZalen; j++){
      if (i < nrTijdsloten && rooster[i][j] != -1 
          && vakken[rooster[i][j]].getDocentNummer() == docent) {
        return true;

      }//if
    }//for
  }//for

  return false;

}  // geeftAlCollege

bool Rooster::trackHeeftEenDocent (int track) 
{ int i;
  int docent = -1;

  for (i = 0; i < nrVakken; i++) {
    if (vakken[i].zoekTrack(track) && docent == -1) {
      docent = vakken[i].getDocentNummer();
    }//if
    else if (vakken[i].zoekTrack(track) 
             && !zelfdeDocent(docent, vakken[i])) {
      return false;
    }//else if
  }//for

  return true;

}  // trackHeeftEenDocent

bool Rooster::minUren (int dag, int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int i, j, z;
  int trackTeller[MaxNrTracks]; 
  resetInt (trackTeller, MaxNrTracks);

  for (i = (dag * nrUrenPerDag); i < ((dag+1) * nrUrenPerDag); i++) { 
    if (i < nrTijdsloten) { 

      for (z = 0; z < nrZalen; z++){
        if (rooster[i][z] != -1) {

          for (j = 0; j < vakken[rooster[i][z]].getAantalTracks(); j++){
            trackTeller[vakken[rooster[i][z]].getTrack(j)]++;
          }//for

        }//if
      }//for

    }//if
  }//for

  for (i = 0; i < MaxNrTracks; i++){
    if (trackTeller[i] == 1 && vakkenPerTrack[i] != 1) {
      return false;
    }//if
    else if (trackTeller[i] == 1 && vakkenPerTrack[i] > 1 
             && !trackHeeftEenDocent(i)) {
      return false;
    }
  }//for

  return true;

}  // minUren

void Rooster::tweedeLes (int track, int j, bool & tweede, int & teller,
                         int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int z;

  for (z = 0; z < nrZalen; z++) {
    if (vakken[rooster[j][z]].zoekTrack(track)) {
      tweede = true;
    }//if
  }//for

  if (!tweede) {
    teller++;
  }//if
  
}  // tweedeLes

bool Rooster::aantalTussenuren (int dag, 
                                int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int i, j;
  bool eerste = false;
  bool tweede = false;
  int tussenuur, teller, begin = -1;

  for (i = 0; i < MaxNrTracks; i++) {
    if(vakkenPerTrack[i] != 0 && vakkenPerTrack[i] != 1){
      tussenuur = 0;
      teller = 0;
      for (j = (dag * nrUrenPerDag); j < ((dag+1) * nrUrenPerDag); j++) {
        tweede = false;
        if (j < nrTijdsloten) {
          
          //eerste les tegekomen
          eersteLes(eerste, begin, i, j, rooster);
          
          //is er een tweede les
          if (eerste && j != begin) {
            tweedeLes(i, j, tweede, teller, rooster);
          }//if

          if (eerste && tweede) {  
            tussenuur += teller;
            teller = 0;
          }//if

        }//if
      }//for
      if (tussenuur > 1) {
        return false;
      }//if  

    }//if
  }//for

  return true;

}  // aantalTussenuren

bool Rooster::zelfdeTrackOpUur (int tijdslot, int zaal, int vak, 
                                int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int j;

  for (j = 0; j < nrZalen; j++) {
    if (j != zaal && rooster[tijdslot][j] != -1) {
      if (zelfdeTrack(vakken[rooster[tijdslot][j]], vakken[vak])) {
        return true;
      }//if
    }//if
  }//for

  return false; 

}  // zelfdeTrackOpUur

bool Rooster::dagIsOke (int tijdslot, int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int i, j;
  int dag = tijdslot / nrUrenPerDag;

  for (i = (dag * nrUrenPerDag); i < ((dag + 1) * nrUrenPerDag); i++) {
    for (j = 0; j < nrZalen; j++) {
      if (rooster[i][j] == -1 && i < nrTijdsloten) {
        return true;
      }//if
    }//for
  }//for
  if (aantalTussenuren(dag, rooster) && minUren(dag, rooster)) {
    return true;
  }//if

  return false;

}  // dagIsOke

void Rooster::resetVakken ()
{
  resetVakkenPriv();

}  // resetVakken

void Rooster::resetVakkenPriv () 
{ int i;

  for (i = 0; i < MaxNrVakken; i++) {
    vakken[i].setIngeroosterd(0);
  }//for

}  // resetVakkenPriv

bool Rooster::bepaalRooster (int rooster[MaxNrTijdsloten][MaxNrZalen],
                             long long &aantalDeelroosters) 
{ int i, j, r, s;
  aantalDeelroosters++;

  for (s = 0; s < nrVakken; s++) {
    if (!vakken[s].getIngeroosterd()) {

      for (r = 0; r < nrDocenten; r++) {
        if (vakken[s].getDocentNummer() == r) { 

          for (i = 0; i < nrTijdsloten; i++) {
            for (j = 0; j < nrZalen; j++) {

              if (docenten[r].zitErin(i) && rooster[i][j] == -1) {
                if (!zelfdeTrackOpUur(i, j, s, rooster) 
                    && !geeftAlCollege(r, i, j, rooster)) {
                  rooster[i][j] = s;
                  vakken[s].setIngeroosterd(1);
                  
                  if (dagIsOke(i, rooster) 
                      && bepaalRooster(rooster, aantalDeelroosters)) {
                    return true; 
                  }//if
                  else {                      
                    rooster[i][j] = -1;
                    vakken[s].setIngeroosterd(0);
                  }//else

                }//if

                break;
              }//if
            }//for
          }//for
          if (!vakken[s].getIngeroosterd()) {
            return false;
          }//ig

        }//if
      }//for
    }//if
  }//for
  for (i = 0; i < nrDagen; i++) {
    if (!minUren(i, rooster)) {
      return false;  
    }//if
    if (!aantalTussenuren (i, rooster)) {
      return false;
    }//if
  }//for 

  return true;

}  // bepaalRooster

//*************************************************************************

bool Rooster::bepaalMinRooster (int rooster[MaxNrTijdsloten][MaxNrZalen],
                                long long &aantalDeelroosters)
{ nrTijdsloten = nrVakken / nrZalen;

  if (nrVakken % nrZalen != 0) {
    nrTijdsloten++;
  }
  while (nrTijdsloten <= nrUrenPerDag * nrDagen) {
    resetVakkenPriv();
   
    if (bepaalRooster(rooster, aantalDeelroosters)) {
      nrTijdsloten = nrDagen * nrUrenPerDag;
      return true;
    }//if
    
    nrTijdsloten++;  

  }//while
  nrTijdsloten = nrDagen * nrUrenPerDag;

  return false;

}  // bepaalMinRooster
  
//*************************************************************************

void Rooster::drukAfRooster (int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int i, j;

  for (i = 0; i < (nrUrenPerDag * nrDagen); i++) {
    if (i % nrUrenPerDag == 0) {
      cout << "-------------------------------------" << endl
           << "Dag: " << (i / nrUrenPerDag) << endl << endl;
    }//if
    cout << "Tijdslot " << i << ": " << endl;
    for (j = 0; j < nrZalen; j++) {
      if (rooster[i][j] != -1) {
        cout << "Zaal: " << j << " | "
             << vakken[rooster[i][j]].getNaam() << " | "
             << "Docent: " << vakken[rooster[i][j]].getDocentNummer() << endl;
      }//if
      else {
        cout << "Zaal: " << j << " | -" << endl;
      }//else
    }//for
    cout << endl;
  }//for

}  // drukAfRooster

//*************************************************************************

void Rooster::eersteLes (bool & eerste, int & begin, int track, int j,
                         int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int z;

  for (z = 0; z < nrZalen; z++){
    if (rooster[j][z] != -1 && !eerste) {
      if (vakken[rooster[j][z]].zoekTrack(track)) {
        eerste = true;
        begin = j;
      }//if
    }//if
  }//for

}  // eersteLes

void Rooster::tweedeLesGretig (int tijdslot, int zaal, int vak, int track, 
                               int j, bool & tweede, int & teller,
                               int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int z;

  for (z = 0; z < nrZalen; z++) {
    if (!(j == tijdslot && z == zaal)) {
      if (rooster[j][z] != -1 && vakken[rooster[j][z]].zoekTrack(track)) {
        tweede = true;
      }//if
    }//if
    if (rooster[j][z] != -1 && j == tijdslot && z == zaal 
        && vakken[vak].zoekTrack(track)) {
      tweede = true;
    }//else if 

  } //for
  if (!tweede) {
    teller++;
  }//if

}  // tweedeLesGretig

bool Rooster::aantalTussenurenGretig (int tijdslot, int zaal, int vak, 
                                      int tussenurenPerTrack[],
                                      int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int i, j, z;
  int dag = (tijdslot / nrUrenPerDag);
  bool eerste = false;
  bool tweede;
  int teller, begin;
  resetInt(tussenurenPerTrack, MaxNrTracks);

  for (i = 0; i < MaxNrTracks; i++) {
    if(vakkenPerTrack[i] != 0){
      teller = 0;
      if (vakkenPerTrack[i] != 1) {
        for (j = (dag * nrUrenPerDag); j <= tijdslot; j++) {
          tweede = false;
          
          //Eerst een vak tegenkomen
          eersteLes(eerste, begin, i, j, rooster);

          if (eerste && j != begin) {

            //Tweede vak tegenkomen
            tweedeLesGretig(tijdslot, zaal, vak, i, j, tweede, teller, rooster);

          }//if

          if (eerste && tweede) {  
            tussenurenPerTrack[i] += teller;
            teller = 0;
          }//if

        }//for
        for (z = 0; z < MaxNrTracks; z++) {
          if (tussenurenPerTrack[z] > 1) {
            return false;
          }//if
        }//for
      }//if
    }//if
  }//for

  return true;

}  // aantalTussenUrenGretig


bool Rooster::minUrenGretig (int tijdslot, int zaal, int trackTeller[],
                             int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int dag = (tijdslot / nrUrenPerDag);
  int i, j, z;
  resetInt (trackTeller, MaxNrTracks);

  for (i = (dag * nrUrenPerDag); i <= tijdslot; i++) { 
    for (z = 0; z < nrZalen; z++){     
      if (!(i == tijdslot && z >= zaal)){          
        if (rooster[i][z] != -1 ) {    
          for (j = 0; j < vakken[rooster[i][z]].getAantalTracks(); j++){
            trackTeller[vakken[rooster[i][z]].getTrack(j)]++; 
          }//for
        }//if
      }//if
    }//fpr
  }//for

  for (i = 0; i < MaxNrTracks; i++){
    if (trackTeller[i] == 1 && vakkenPerTrack[i] != 1) {
      return false;
    }//if
  }//for

  return true;

}  // minUrenGretig


bool Rooster::geeftNuCollege(int docent, int zaal, int tijdslot, 
                             int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int j;

  for (j = 0; j < nrZalen; j++){
    if (j != zaal && rooster[tijdslot][j] != -1 
        && vakken[rooster[tijdslot][j]].getDocentNummer() == docent) {
      return true;
    }//if
  }//for

  return false;

}  // geeftNuCollege

int Rooster::besteScore (int tijdslot, int zaal, int docent, int vak, 
                         int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int teller = 0;
  int i;
  int trackTeller[MaxNrTracks];
  int tussenurenPerTrack[MaxNrTracks];

  if (!geeftAlCollege(docent, tijdslot, zaal, rooster)) {
      teller++;
  }//if
  if (!minUrenGretig(tijdslot, zaal, trackTeller, rooster)) {
    for (i = 0; i < MaxNrTracks; i++) {
      if (trackTeller[i] == 1 && vakken[vak].zoekTrack(i)) {
        teller++;
      }//if
    }//for
  }//if
  if (aantalTussenurenGretig(tijdslot, zaal, vak, tussenurenPerTrack, rooster)) {
    teller++;
  }//if

  return teller;

}  // besteScore

void Rooster::bepaalRoosterGretig (int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int i, j, r, s;
  int beste,
      tijdslot,
      zaal;

  for (s = 0; s < nrVakken; s++) {
    beste = -1;
    tijdslot = -1;
    zaal = -1;
    if (!vakken[s].getIngeroosterd()) {
      
      for (r = 0; r < nrDocenten; r++) {
        if (vakken[s].getDocentNummer() == r) {  
          
          for (i = 0; i < nrTijdsloten; i++) {
            for (j = 0; j < nrZalen; j++) {

              if (docenten[r].zitErin(i) && rooster[i][j] == -1) {
                if (!geeftNuCollege(r, j, i, rooster) 
                    && !zelfdeTrackOpUur(i, j, s, rooster)) {

                  if (besteScore(i, j, r, s, rooster) > beste){
                    beste = besteScore(i, j, r, s, rooster);
                    tijdslot = i;
                    zaal = j; 
                  }//if

                }//if             
              }//if

            }//for
          }//for

        }
      }//for

    }
    rooster[tijdslot][zaal] = s;
    vakken[s].setIngeroosterd(1);
  }//for

}  // bepaalRoosterGretig