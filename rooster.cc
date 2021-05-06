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
  nrTijdsloten = nrDagen * nrUrenPerDag;
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
  int i, j;
  for (i = (dag * nrUrenPerDag); i < ((dag+1) * nrUrenPerDag); i++) {
    for (j = 0; j < nrZalen; j++){
      if (i < nrTijdsloten && rooster[i][j] != -1 && vakken[rooster[i][j]].getDocentNummer() == docent) {
        return true;
      }
    }
  }
  return false;
}

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
          }
        }
      }
    }
  }
  for (i = 0; i < MaxNrTracks; i++){
    if (trackTeller[i] == 1 && vakkenPerTrack[i] != 1) {
      return false;
    }
  }
  return true;
}

bool Rooster::aantalTussenuren (int dag, int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int i, j, z;
  bool eerste = false;
  bool les;
  int tussenuur, teller, begin = -1;
  for (i = 0; i < MaxNrTracks; i++) {
    if(vakkenPerTrack[i] != 0){
      tussenuur = 0;
      teller = 0;
      if (vakkenPerTrack[i] != 1) {
        for (j = (dag * nrUrenPerDag); j < ((dag+1) * nrUrenPerDag); j++) {
          les = false;
          if (j < nrTijdsloten) {
            for (z = 0; z < nrZalen; z++){
              if (rooster[j][z] != -1 && !eerste) {
                if (vakken[rooster[j][z]].zoekTrack(i)) {
                  eerste = true;
                  begin = j;
                }
              }
            }
            if (eerste && j != begin) {
              for (z = 0; z < nrZalen; z++) {
                if (vakken[rooster[j][z]].zoekTrack(i)) {
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

bool Rooster::zelfdeTrackOpUur (int tijdslot, int zaal, int vak, int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int j;
  for (j = 0; j < nrZalen; j++) {
    if (j != zaal && rooster[tijdslot][j] != -1) {
      if (zelfdeTrack(vakken[rooster[tijdslot][j]], vakken[vak])) {
        return true;
      }
    }
  }
  return false; 
}

bool Rooster::dagIsOke (int tijdslot, int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int i, j;
  int dag = tijdslot / nrUrenPerDag;
  for (i = (dag * nrUrenPerDag); i < ((dag + 1) * nrUrenPerDag); i++) {
    for (j = 0; j < nrZalen; j++) {
      if (rooster[i][j] == -1 && i < nrTijdsloten) {
        return true;
      }
    }
  }
  if (aantalTussenuren(dag, rooster) && minUren(dag, rooster)) {
    return true;
  }
  return false;

}


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
                if (j == 0 || ((j > 0) && rooster[i][0] != -1)) {
                  if (!zelfdeTrackOpUur(i, j, s, rooster) && !geeftAlCollege(r, i, j, rooster)) {
                    rooster[i][j] = s;
                    vakken[s].setIngeroosterd(1);
                    
                    if (dagIsOke(i, rooster) && bepaalRooster(rooster, aantalDeelroosters)) {
                      return true; 
                    }
                    else {                      
                      rooster[i][j] = -1;
                      vakken[s].setIngeroosterd(0);
                    } 

                  }
                  break;
                }
              }
            }
          }
          if (!vakken[s].getIngeroosterd()) {
            return false;
          }
        }
      }
    }
  }
  for (s = 0; s < nrVakken; s++) {
    if (!vakken[s].getIngeroosterd()) {
      return false;
    }
  }

  for (i = 0; i < nrDagen; i++) {
    if (!minUren(i, rooster)) {
      return false;  
    }
    if (!aantalTussenuren (i, rooster)) {
      return false;
    }
    
  }

  return true;
}

//*************************************************************************

bool Rooster::bepaalMinRooster (int rooster[MaxNrTijdsloten][MaxNrZalen],
                        long long &aantalDeelroosters)
{ int i;
  nrTijdsloten = nrVakken / nrZalen;
  if (nrVakken % nrZalen != 0) {
    nrTijdsloten++;
  }
  while (nrTijdsloten <= nrUrenPerDag * nrDagen) {
    for (i = 0; i < nrVakken; i++) {
      vakken[i].setIngeroosterd(0);
    }
    cout << nrTijdsloten << " tijdsloten " << endl;
    if (bepaalRooster(rooster, aantalDeelroosters)) {
      return true;
    }
    nrTijdsloten++;   
  }
  return false;

}  // bepaalMinRooster
  
//*************************************************************************

void Rooster::drukAfRooster (int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int i, z;
  for (i = 0; i < (nrUrenPerDag * nrDagen); i++) {
    if (i % nrUrenPerDag == 0) {
      cout << "-------------------------------------" << endl
           << "Dag: " << (i / nrUrenPerDag) << endl << endl;
    }
    cout << "Tijdslot " << i << ": " << endl;
    for (z = 0; z < nrZalen; z++) {
      if (rooster[i][z] != /*100*/ -1) {
        cout << "Zaal: " << z << " | "
             << vakken[rooster[i][z]].getNaam() << " | "
             << "Docent: " << vakken[rooster[i][z]].getDocentNummer() << endl;
      }
      else {
        cout << "Zaal: " << z << " | -" << endl;
      }
    }
  
    cout << endl;
  }  

}  // drukAfRooster

//*************************************************************************
bool Rooster::aantalTussenurenGretig (int tijdslot, int zaal, int vak, int tussenurenPerTrack[],
                                      int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int i, j, z;
  //cout << "aantalTussenurenGretig" << endl;
  int dag = (tijdslot / nrUrenPerDag);
  bool eerste = false;
  bool les;
  int teller, begin;
  resetInt(tussenurenPerTrack, MaxNrTracks);
  for (i = 0; i < MaxNrTracks; i++) {
    if(vakkenPerTrack[i] != 0){
      teller = 0;
      //cout << "hoi" << endl;
      if (vakkenPerTrack[i] != 1) {
        //cout << "doei" << endl;
        for (j = (dag * nrUrenPerDag); j <= tijdslot; j++) {
          //cout << "why" << endl;
          les = false;
          for (z = 0; z < nrZalen; z++){
            //cout << "damn" << endl;
            if (!(j == tijdslot && z == zaal)) {
              //cout << "blub" << endl;
              if (rooster[j][z] != -1 && !eerste) {
                //cout << "urghh" << endl;
                if (vakken[rooster[j][z]].zoekTrack(i)) {
                  //cout << "pff" << endl;
                  eerste = true;
                  begin = j;
                }
              }
            } 
          }
          if (eerste && j != begin) {
            for (z = 0; z < nrZalen; z++) {
              if (!(j == tijdslot && z >= zaal)) {
                if (rooster[j][z] != -1 && vakken[rooster[j][z]].zoekTrack(i)) {
                  les = true;
                }
              }
              else if (rooster[j][z] != -1 && i == tijdslot && z == zaal && vakken[vak].zoekTrack(i)) {
                les = true;
              }
            }
            if (!les) {
              teller++;
            }
          } 
          if (eerste && les) {  
            tussenurenPerTrack[i] += teller;
            teller = 0;
          }
        }//for
        for (z = 0; z < MaxNrTracks; z++) {
          if (tussenurenPerTrack[z] > 1) {
            return false;
          }
        }
      }  
    }
  }
  return true;

}


bool Rooster::minUrenGretig (int tijdslot, int zaal, int trackTeller[],
                             int rooster[MaxNrTijdsloten][MaxNrZalen])
{ //cout << "minUrenGretig" << endl;
  int dag = (tijdslot / nrUrenPerDag);
  int i, j, z;
  resetInt (trackTeller, MaxNrTracks);
  for (i = (dag * nrUrenPerDag); i <= tijdslot; i++) { 
    for (z = 0; z < nrZalen; z++){
      if (!(i == tijdslot && z >= zaal)){   
        if (rooster[i][z] != -1 ) {
          for (j = 0; j < vakken[rooster[i][z]].getAantalTracks(); j++){
            trackTeller[vakken[rooster[i][z]].getTrack(j)]++;
          }
        }
      }
    }
  }
  for (i = 0; i < MaxNrTracks; i++){
    if (trackTeller[i] == 1 && vakkenPerTrack[i] != 1) {
      return false;
    }
  }
  return true;
}


bool Rooster::geeftNuCollege(int docent, int zaal, int tijdslot, 
                             int rooster[MaxNrTijdsloten][MaxNrZalen])
{ //cout << "geeftNuCollege" << endl;
  int j;
  for (j = 0; j < nrZalen; j++){
    if (j != zaal && rooster[tijdslot][j] != -1 
    && vakken[rooster[tijdslot][j]].getDocentNummer() == docent) {
      return true;
    }
  }
  return false;
}

//aka twoGirlsOneCup
bool Rooster::tweeZalenEenTrack (int zaal, int tijdslot, int vak,
                                 int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ //cout << "tweeZalenEenTrack" << endl;
  int z;
  for (z = 0; z < zaal; z++) {
    if (z != zaal && rooster[tijdslot][z] != -1 
       && zelfdeTrack (vakken[vak], vakken[rooster[tijdslot][z]])){
      //cout << "Twee vakken van dezelfde track op 1 tijdstip." << endl;
      return true;
    }
  }
  return false;
}

/*
void Rooster::bepaalRoosterGretig (int rooster[MaxNrTijdsloten][MaxNrZalen])
{ cout << "bepaalRoosterGretig" << endl;
  int i = 0, j = 0; 
  int r, s, k; 
  int hulpi, hulpj;
  int trackTeller[MaxNrTracks];
  int tussenurenPerTrack[MaxNrTracks];
  bool ok = false; 
  int teller = 0;
  int grootste = -1;
  int besteVak = -1;
  while (rooster[i][j] != -1 && i < nrTijdsloten) {
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
  if (i >= nrTijdsloten) {
    return;
  }
  hulpi = i;
  hulpj = j;
  cout << "i en j: " << i << " " << j << ", " << rooster[i][j] << endl;
  for (r = 0; r < nrDocenten; r++) {
    //cout << i << " " << j << endl;
    if (docenten[r].zitErin(i)) {
      for (s = 0; s < nrVakken; s++) {
        //cout << i << " " << j << endl;
        if (vakken[s].getDocentNummer() == docenten[r].getNummer() 
            && !vakken[s].getIngeroosterd()) {
          //cout << i << " " << j << endl;
          if (!geeftNuCollege(s, j, i, rooster) && !tweeZalenEenTrack(j, i, s, rooster)) {
            if(!geeftAlCollege(r, i, j, rooster)) {
              teller++;
            }
            //cout << i << " " << j << endl;
            if (!minUrenGretig(i, j, trackTeller, rooster)) {
              for (k = 0; k < MaxNrTracks; k++) {
                if (trackTeller[k] == 1 && vakken[s].zoekTrack(k)) {
                  teller++;
                }
              }
            }
            //cout << i << " " << j << endl;
            if (aantalTussenurenGretig(i, j, s, tussenurenPerTrack, rooster)) {
              teller++;
            }
          }
        }
        //cout << i << " " << j << endl;
        if (teller > grootste) {
          grootste = teller;
          besteVak = s;
        }
        //cout << i << " " << j << endl;
        teller = 0;
      }//for
      //cout << "rooster ervoor: " << i << " " << j << " " << rooster[hulpi][hulpj] << endl;
      if (grootste != -1 && !vakken[besteVak].getIngeroosterd()) {
        cout << "besteVak: " << besteVak << endl
             << "grootste: " << grootste << endl 
             << "op " << hulpi << ", " << hulpj << endl;  
        rooster[hulpi][hulpj] = besteVak;
        vakken[besteVak].setIngeroosterd(1);
      }
      else {
        cout << "else: hulpi en hulpj " << hulpi << hulpj << endl;
        rooster[hulpi][hulpj] = 100;
      }
      //cout << "rooster erna: " << hulpi << " " << hulpj << " " << rooster[hulpi][hulpj] << endl;
      bepaalRoosterGretig(rooster);
    }
    if (rooster[hulpi][hulpj] == -1) {
      cout << "hulpi en hulpj (" << hulpi << ", " << hulpj << ")" << endl;
      rooster[hulpi][hulpj] = 100;
      bepaalRoosterGretig(rooster);
    }
  } 
}  // bepaalRoosterGretig
*/

int Rooster::besteScore (int tijdslot, int zaal, int docent, int vak, 
                         int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int teller = 0;
  int i;
  int trackTeller[MaxNrTracks];
  int tussenurenPerTrack[MaxNrTracks];
  if (!geeftAlCollege(docent, tijdslot, zaal, rooster)) {
      teller++;
    }
  if (!minUrenGretig(tijdslot, zaal, trackTeller, rooster)) {
    for (i = 0; i < MaxNrTracks; i++) {
      if (trackTeller[i] == 1 && vakken[vak].zoekTrack(i)) {
      teller++;
      }
    }
  }
  if (aantalTussenurenGretig(tijdslot, zaal, vak, tussenurenPerTrack, rooster)) {
    teller++;
  }

  return teller;
}

void Rooster::bepaalRoosterGretig (int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int i, j, r, s;
  int beste ;
  int tijdslot;
  int zaal;
  //int trackTeller[MaxNrTracks];
  //int tussenurenPerTrack[MaxNrTracks];
  for (s = 0; s < nrVakken; s++) {
      vakken[s].setIngeroosterd(0);
    }
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
                if (!geeftNuCollege(r, j, i, rooster) && !tweeZalenEenTrack(j, i, s, rooster)) {
                  //cout << "besteScore: " << besteScore(i, j, r, s, rooster) << endl;
                  if (besteScore(i, j, r, s, rooster) > beste){
                    beste = besteScore(i, j, r, s, rooster);
                    tijdslot = i;
                    zaal = j; 
                  }
                }                
              }
            }
          }
        }
      }
    }
    cout << "tijdslot: " << tijdslot << endl;
    cout << "zaal: " << zaal << endl;
    cout << "vak: " << s << endl;
    rooster[tijdslot][zaal] = s;
    vakken[s].setIngeroosterd(1);
  }
  return;
}