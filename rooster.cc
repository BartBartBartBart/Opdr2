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
  resetInt (vakkenPerTrack, MaxNrTracks);
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
      vakkenPerTrack[tracks0[j]]++;
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

bool Rooster::geeftAlCollege(int docent, int tijdslot, int zaal,
                             int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int dag = tijdslot / nrUrenPerDag;
  cout << "Dag: " << dag  << " " << "docent " << docent << endl;
  int i, j;
  for (i = (dag * nrUrenPerDag); i <= tijdslot; i++) {
    for (j = 0; j < nrZalen; j++){
      if (i != tijdslot || (i == tijdslot && j < zaal)) {
        if (rooster[i][j] == -1) {
          cout << "foutje gevonden"; 
        }
        cout << vakken[rooster[i][j]].getDocentNummer() << " en " << docent;
        if (rooster[i][j] != 100 && vakken[rooster[i][j]].getDocentNummer() == docent) {
          //cout << "i en j = " << i << " " << j << endl;
          return true;
        }
      }
    }
  }
  return false;
}

bool Rooster::minUren (int tijdslot, int rooster[MaxNrTijdsloten][MaxNrZalen])
{ cout << "hoi";
  int dag = (tijdslot / nrUrenPerDag);
  int i, j, z;
  int trackTeller[MaxNrTracks]; 
  resetInt (trackTeller, MaxNrTracks);
  for (i = (dag * nrUrenPerDag); i < ((dag+1) * nrUrenPerDag); i++) { 
    for (z = 0; z < nrZalen; z++){
      if (rooster[i][z] != -1 && rooster[i][z] != 100) {
        for (j = 0; j < vakken[rooster[i][z]].getAantalTracks(); j++){
          trackTeller[vakken[rooster[i][z]].getTrack(j)]++;
        }
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

bool Rooster::aantalTussenuren (int tijdslot, int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int i, j, z;
  int dag = (tijdslot / nrUrenPerDag);
  bool eerste = false;
  bool les;
  int tussenuur, teller, begin;
  for (i = 0; i < MaxNrTracks; i++) {
    if(vakkenPerTrack[i] != 0){
      tussenuur = 0;
      teller = 0;
      if (vakkenPerTrack[i] != 1) {
        for (j = (dag * nrUrenPerDag); j < ((dag+1) * nrUrenPerDag); j++) {
          les = false;
          for (z = 0; z < nrZalen; z++){
            if (rooster[j][z] != 100 && !eerste) {
              if (vakken[rooster[j][z]].zoekTrack(i)) {
                eerste = true;
                begin = j;
              }
            }
          }
          if (eerste && j != begin) {
            for (z = 0; z < nrZalen; z++) {
              if (rooster[j][z] != 100 && vakken[rooster[j][z]].zoekTrack(i)) {
                les = true;
              }
            }
            if (!les) {
              teller++;
            }
          } 
          if (eerste && les) {  
            tussenuur += teller;
            teller = 0;
          }
        }//for
        if (tussenuur > 1) {
          return false;
        }
      }  
    }
  }
  return true;
}

bool Rooster::bepaalRooster (int rooster[MaxNrTijdsloten][MaxNrZalen],
                        long long &aantalDeelroosters)
{ int i = 0, j = 0;
  int r, s, z;
  bool ok = false;
  bool goed;
  aantalDeelroosters++;
  while (rooster[i][j] != -1 && i < (nrDagen * nrUrenPerDag)) {
    while (j < (nrZalen - 1) && !ok) {
      j++; 
      if (rooster[i][j] == -1) { 
        ok = true;
      }
    }
    if (!ok) {
      i++;
      j = 0;
    }
  }
  cout << "i: " << i << "j: " << j;
  if (i >= nrDagen * nrUrenPerDag) {
    //cout << "Return true" << endl;
    return true;
  }
  ok = false;
  while (!ok) {
    for (r = 0; r < nrDocenten; r++) {
      cout << "Docentnummer " << r << endl;
      if (!ok) {
        if (docenten[r].zitErin(i)) {
          for (s = 0; s < nrVakken; s++){
            //cout << "Vaknummer " << s << endl;
            if (!ok) {
              if(docenten[r].getNummer() == vakken[s].getDocentNummer() && 
                 !vakken[s].getIngeroosterd()) {
                goed = true;
                for (z = 0; z < nrZalen; z++) {
                  if (z != j && rooster[i][z] != -1 && rooster[i][z] != 100
                    && zelfdeTrack (vakken[s], vakken[rooster[i][z]])){
                    cout << "Twee vakken van dezelfde track op 1 tijdstip." << endl;
                    goed = false;
                  }
                }
                if (geeftAlCollege(vakken[s].getDocentNummer(), i, j, rooster)){
                  cout << "Docent geeft al les vandaag." << endl
                       << "Docentnummer is " << r << endl;
                  goed = false;
                }
                if (goed) {
                  rooster[i][j] = s;
                  cout << " wordt ingeroosterd" << endl;
                  vakken[s].setIngeroosterd();
                  if ((i + 1) % nrUrenPerDag == 0 && j == (nrZalen - 1) && !minUren(i, rooster)) {
                    cout << "De studenten mogen niet voor 1 vak "
                         << "naar de Universiteit komen" << endl;
                    //rooster[i][j] = -1;
                    goed = false;
                  }
                  if ((i + 1) % nrUrenPerDag == 0 && !aantalTussenuren (i, rooster)) {
                    cout << "Er zijn te veel tussenuren voor een Track" << endl;
                    //rooster[i][j] = -1;
                    goed = false;
                  }
                  if (goed && bepaalRooster(rooster, aantalDeelroosters)){
                    //cout << "rooster is goed" << endl;
                    ok = true;
                  }
                  else {
                    //cout << "Goed is fout, fuck.";
                    rooster[i][j] = -1;
                    vakken[s].setIngeroosterd();
                  }
                }
              }
            }
          }
        }
      }
    }
    //tussenuur
    if (!ok && rooster[i][j] == -1) {
      rooster[i][j] = 100;
      if ((i + 1) % nrUrenPerDag == 0 && j == (nrZalen - 1) && !minUren(i, rooster)) {
        cout << "De studenten mogen niet voor 1 vak "
             << "naar de Universiteit komen" << endl;
        rooster[i][j] = -1;
        return false;
      }
      if ((i + 1) % nrUrenPerDag == 0 && !aantalTussenuren (i, rooster)) {
        cout << "Er zijn te veel tussenuren voor een Track" << endl;
        rooster[i][j] = -1;
        return false;
      }
      //cout << " wordt tussenuur" << endl;
      if (bepaalRooster(rooster, aantalDeelroosters)){
        // cout << "het eindelijke rooster is true" << endl;
        ok = true;
      }
      else {
        rooster[i][j] = -1;
        return false;
      }
    }
  }
  for (i = 0; i < MaxNrTijdsloten; i++){
    for (j = 0; j < nrZalen; j++) {
      if (rooster[i][j] == -1) {
        rooster[i][j] = 100;
      } 
    } 
  }
  // cout << "Return true" << endl;
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
{ int i, z;
  for (i = 0; i < (nrUrenPerDag * nrDagen); i++) {
    cout << "Tijdslot " << i << ": " << endl;
    for (z = 0; z < nrZalen; z++) {
      if (rooster[i][z] != 100) {
        cout << "Zaal " << z << ": " << endl
             << "Vak: " << vakken[rooster[i][z]].getNaam() << endl
             << "Docent: " << vakken[rooster[i][z]].getDocentNummer() << endl
             << "rooster[i][z]: " << rooster[i][z] << endl;
      }
      else {
        cout << "Zaal " << z << ": -" << endl;
      }
    }
  
    cout << endl << endl;
  }  

}  // drukAfRooster

//*************************************************************************

void Rooster::bepaalRoosterGretig (int rooster[MaxNrTijdsloten][MaxNrZalen])
{
  // TODO: implementeer deze functie

}  // bepaalRoosterGretig

