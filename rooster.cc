// Implementatie van klasse Rooster
// Makers: Lisanne Wallaard (s2865459), Bart den Boef (s2829452)
// Vak: Algoritmiek
// Tweede programmeeropdracht: Rooster
// Studierichting: Kunstmatige Intelligentie
// Jaar van aankomst: 2020
// C++, 7.5.2021, GNU GCC Compiler

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

// Leest de file in die meegegeven is in de header
// Uit de file worden alle variabelen voor het rooster gehaald
bool Rooster::leesIn (const char* invoerNaam)
{ int i, j; // for loop
  ifstream fin; // voor het inlezen van de file
  bool verschillendeTracks[MaxNrTracks]; // om het aantal verschillende tracks 
                                         // bij te houden
  int tijdsloten0[MaxNrTijdsloten]; // de tijdsloten waarop
                                    // een docent les kan geven
  int aantalTijdsloten0; // aantal tijdsloten dat een docent les kan geven
  string naam0; // naam van een vak
  int docentNummer0, // nummer van docent
      aantalTracks0; // aantal tracks dat een vak heeft
  int tracks0[MaxNrTracks]; // array met de tracks die een vak heeft
  resetInt (vakkenPerTrack, MaxNrTracks);
  resetBool (verschillendeTracks, MaxNrTracks);

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

      if (verschillendeTracks[tracks0[j]] == false) {
        verschillendeTracks[tracks0[j]] = true;
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

// Drukt alle ingelezen informatie van een rooster af naar het scherm
void Rooster::drukAf ()
{ int i, j; // for loop

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

// checkt of 'docent' het meegegeven vak 'vak' geeft
// - true, als de docent het vak geeft
// - false, als dat niet zo is
bool Rooster::zelfdeDocent (int docent, Vak vak) 
{ 
  if (docent == vak.getDocentNummer()) {
    return true;
  }//if

  return false;

}  // zelfdeDocent

//*************************************************************************

// Zet alle waardes van een bool array op false
void Rooster::resetBool (bool A[], int n)
{ int i; // for loop

  for (i = 0; i < n; i++){
    A[i] = false;
  }//for

}  // resetBool

//*************************************************************************

// Zet alle waardes van een int array op 0
void Rooster::resetInt (int A[], int n)
{ int i; // for loop

  for (i = 0; i < n; i++){
    A[i] = 0;
  }//for

}  // resetInt

//*************************************************************************

// Controleert of er een track is die in vak A en vak B voorkomt
// - true, als er een gemeenschappelijke track is
// - false, als dat niet zo is
bool Rooster::zelfdeTrack (Vak A, Vak B)
{ int i, j; // for loop

  for (i = 0; i < A.getAantalTracks(); i++) {
    for (j = 0; j < B.getAantalTracks(); j++) {
      if (A.getTrack(i) == B.getTrack(j)) {
        return true;

      }//if
    }//for
  }//for

  return false;

}  // zelfdeTrack

//*************************************************************************

// Controleert op het meegegeven 2D array 'rooster' of 'docent' al les geeft
// op de huidige dag, 'tijdslot' wordt gebruikt om de huidige dag te berekenen.
// De functie retourneert:
// - true, als de docent al college geeft op de huidige dag
// - false, als de docent nog geen college geeft op de huidige dag
bool Rooster::geeftAlCollege(int docent, int tijdslot,
                             int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int dag = tijdslot / nrUrenPerDag; // de huidige dag
  int i, j; // for loop

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

//*************************************************************************

// Controleert of de docenten van de meegegeven track wel op dezelfde dag les
// kunnen geven.
// - Retourneert true als de docenten op dezelfde dag les kunnen geven
// - Retourneert false als dat niet het geval is
bool Rooster::lesOpZelfdeDag (int track) 
{ int i, j; // for loop
  pair<bool,int> dagen[nrDagen]; // hulparray, .first wordt true als er een
                                 // docent dan les kan geven, .seconde bevat
                                 // desbetreffende docent
  int docent; // hulpvar, voor de docent
  int dag; // hulpvar, voor de dag
  
  for (i = 0; i < nrDagen; i++) {
    dagen[i].first = false;
    dagen[i].second = -1;
  }//for

  for (i = 0; i < nrVakken; i++) {
    if (vakken[i].zoekTrack(track)) {
      docent = vakken[i].getDocentNummer();

      for (j = 0; j < docenten[docent].getAantalTijdsloten(); j++) {
        dag = docenten[docent].getTijdslot(j) / nrUrenPerDag;

        if (!dagen[dag].first) {
          dagen[dag].first = true;
          dagen[dag].second = docent;
        }//if
        else if (dagen[dag].first && dagen[dag].second != docent) {
          return true;
        }//else if

      }//for
    }//if
  }//for

  return false;

}  // lesOpZelfdeDag

//*************************************************************************

// Controleert of een track meer dan 1 verschillende docent heeft
// De functie retourneert:
// - true, als er maar 1 docent is bij een track
// - false, als een track meer dan 1 docent heeft
bool Rooster::trackHeeftEenDocent (int track) 
{ int i; // for loop
  int docent = -1; // onthoud welke docent we hebben gezien

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

//*************************************************************************

// Controleert of er op de meegegeven dag, op het meegegeven rooster, een 
// track is die op die dag maar 1 vak aanbiedt
// retourneert:
// - true, als er een track met maar 1 vak op die dag is
// - false, als die er niet is
bool Rooster::minUren (int dag, int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int i, j, z; // for loop
  int trackTeller[MaxNrTracks]; // array waarin het aantal vakken per track
                                // op de dag wordt opgeslagen
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
             && !trackHeeftEenDocent(i) && lesOpZelfdeDag(i)) {
      return false;
    }
  }//for

  return true;

}  // minUren

//*************************************************************************

// Hulpfunctie bij het checken van tussenuur: kijkt of we voor een 
// gegeven track op een gegeven uur een les vinden van die track
// 'eerste' wordt true als we een vak van 'track' tegenkomen, anders false
// 'begin' wordt gebruikt om het tijdslot te onthouden waar eerste true werd
// 'track' is de track waar voor de lessen gezocht worden
// 'tijdslot' is het tijdslot waar gekeken wordt voor de lessen
void Rooster::eersteLes (bool & eerste, int & begin, int track, int tijdslot,
                         int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int z; // for loop

  for (z = 0; z < nrZalen; z++){
    if (rooster[tijdslot][z] != -1 && !eerste) {
      if (vakken[rooster[tijdslot][z]].zoekTrack(track)) {
        eerste = true;
        begin = tijdslot;
      }//if
    }//if
  }//for

}  // eersteLes

//*************************************************************************

// Als hier geen les gevonden wordt, wordt de teller opgehoogd 
// 'teller' zijn het aantal potentiele tussenuren
// 'track' is de track waarvoor gekeken wordt, op tijdslot 'tijdslot'
// 'tweede' wordt true als er een les gevonden wordt
void Rooster::tweedeLes (int track, int tijdslot, bool & tweede, int & teller,
                         int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int z; // for loop

  for (z = 0; z < nrZalen; z++) {
    if (vakken[rooster[tijdslot][z]].zoekTrack(track)) {
      tweede = true;
    }//if
  }//for

  if (!tweede) {
    teller++;
  }//if
  
}  // tweedeLes

//*************************************************************************

// Controleert of er op de meegegeven dag 'dag' niet meer dan 1 tussenuur
// voor een track is
// De functie retourneert:
// - true, als er niet meer dan 1 tussenuur per track op de dag is
// - false, als er meer dan 1 tussenuur voor een track op de dag is
bool Rooster::aantalTussenuren (int dag, 
                                int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int i, j; // for loop
  bool eerste = false; // wordt true als er een eerste les tegen is gekomen
  bool tweede = false; // wordt true als er een tweede les tegen is gekomen 
  int tussenuur, // het aantal tussenuren voor een track
      teller, // het aantal potentiële tussenuren
      begin = -1; // hulpvariabele voor het onthouden van een tijdslot

  for (i = 0; i < MaxNrTracks; i++) {
    if(vakkenPerTrack[i] != 0 && vakkenPerTrack[i] != 1){
      tussenuur = 0;
      teller = 0;
      for (j = (dag * nrUrenPerDag); j < ((dag+1) * nrUrenPerDag); j++) {
        tweede = false;
        if (j < nrTijdsloten) {
          
          //eerste les tegenkomen
          eersteLes(eerste, begin, i, j, rooster);
          
          //tweede les tegengekomen
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

//*************************************************************************

// Controleert of er op het gegeven tijdslot geen vakken gegeven worden
// die een track gemeenschappelijk hebben met 'vak'
// 'tijdslot' is het tijdslot waarop gecontroleerd moet worden
// op rooster['tijdslot']['zaal'] hoeft niet gecontroleerd te worden, want
// daar wordt mogelijk het vak 'vak' geplaatst
// De functie retourneert:
// - true, als er een track is met twee vakken op dit uur
// - false, als dit niet het geval is
bool Rooster::zelfdeTrackOpUur (int tijdslot, int zaal, int vak, 
                                int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int j; // for loop

  for (j = 0; j < nrZalen; j++) {
    if (j != zaal && rooster[tijdslot][j] != -1) {
      if (zelfdeTrack(vakken[rooster[tijdslot][j]], vakken[vak])) {
        return true;

      }//if
    }//if
  }//for

  return false; 

}  // zelfdeTrackOpUur

//*************************************************************************

// Controleert of de dag waarin de meegegeven 'tijdslot' al vol is.
// als hij vol is, controleert hij het aantal tussenuren op die dag en 
// of er niet een track is met maar 1 vak op die dag
// de functie retourneert:
// - true, als de dag nog niet vol is, of als hij vol is maar aan de 
// voorwaarden voldoet
// - false, als de dag vol is en niet voldoet aan de voorwaarden
bool Rooster::dagIsOke (int tijdslot, int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int i, j; // for loop
  int dag = tijdslot / nrUrenPerDag; // de dag waar tijdslot in valt

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

//*************************************************************************

// Wrapper functie, roept de prive functie resetVakkenPriv aan
void Rooster::resetVakken ()
{
  resetVakkenPriv();

}  // resetVakken

//*************************************************************************

// Zet voor alle vakken de membervariabele ingeroosterd op false
void Rooster::resetVakkenPriv () 
{ int i; // for loop

  for (i = 0; i < MaxNrVakken; i++) {
    vakken[i].setIngeroosterd(0);
  }//for

}  // resetVakkenPriv

//*************************************************************************

// Bepaalt een rooster, rekening houdend met de eisen zoals beschreven in de
// opdracht. Het aantal bekeken deelroosters wordt bijgehouden in 
// 'aantalDeelrooster'. 
// Als een vak wordt ingeroosterd, wordt de membervariabele 'ingeroosterd' op
// true gezet
// De functie retourneert:
// - true, als er een rooster gevonden is, dit wordt in de 2D array rooster 
// gestopt
// - false, als er geen rooster gevonden kan worden
bool Rooster::bepaalRooster (int rooster[MaxNrTijdsloten][MaxNrZalen],
                             long long &aantalDeelroosters) 
{ int i, // for loop, tijdslot
      j, // zaal
      r, // docent
      s; // vak
  aantalDeelroosters++;

  for (s = 0; s < nrVakken; s++) {
    if (!vakken[s].getIngeroosterd()) {

      for (r = 0; r < nrDocenten; r++) {
        if (vakken[s].getDocentNummer() == r) { 

          for (i = 0; i < nrTijdsloten; i++) {
            for (j = 0; j < nrZalen; j++) {

              if (docenten[r].zitErin(i) && rooster[i][j] == -1) {
                if (!zelfdeTrackOpUur(i, j, s, rooster) 
                    && !geeftAlCollege(r, i, rooster)) {
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
          }//if

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

// Bepaalt een minimaal rooster wat nog steeds aan de eisen voldoet
// Het aantal bekeken deelroosters wordt bijgehouden in 'aantalDeelroosters'
// De functie retourneert: 
// - true, als er een rooster gevonden is, deze wordt opgeslagen in de 2D
// array 'rooster'
// - false, als er geen rooster gevonden is
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

// Drukt het meegegeven rooster af naar het scherm
void Rooster::drukAfRooster (int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int i, j; // for loop

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

// Hulpfunctie voor het berekenen van de tussenuren voor het gretige algoritme
// op tijdslot 'j' wordt gekeken of er een vak is wat een een track gelijk heeft
// met meegegeven 'vak'
// op rooster['tijdslot']['zaal'] hoeft niet gekeken te worden, hier wordt
// mogelijk een vak geplaatst
// als er een tweede vak gevonden is wordt 'tweede' true, en wordt de 
// meegegeven teller opgehoofd, dit zijn de potentiële tussenuren
void Rooster::tweedeLesGretig (int tijdslot, int zaal, int vak, int track, 
                               int j, bool & tweede, int & teller,
                               int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int z; // for loop

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

//*************************************************************************

// Controleert of er op de desbetreffende dag niet een track is met meer 
// dan 1 tussenuur. 'tijdslot' wordt gebruikt voor het berekenen van de dag. 
// 'zaal' en 'vak' worden meegegeven aan tweedeLesGretig.
// In tussenurenPerTrack[] wordt per track het aantal tussenuren opgeslagen.
// 2D rooster wordt meegegeven aan eersteLes en tweedeLesGretig. 
bool Rooster::aantalTussenurenGretig (int tijdslot, int zaal, int vak, 
                                      int tussenurenPerTrack[],
                                      int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int i, // for loop, loopt over tracks
      j, // loopt over tijdsloten
      z, // loopt ook over tracks
      dag = (tijdslot / nrUrenPerDag), // dag waar tijdslot in valt
      teller, // aantal potentiele tussenuren
      begin; // hulpvariabele voor waar de eerste les gevonden is
  bool eerste = false; // wordt true als een eerste les gevonden is
  bool tweede = false; // wordt true als er een tweede les gevonden is
  resetInt(tussenurenPerTrack, MaxNrTracks);

  for (i = 0; i < MaxNrTracks; i++) {
    if(vakkenPerTrack[i] != 0 && vakkenPerTrack[i] != 1){
      teller = 0;
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
  }//for

  return true;

}  // aantalTussenUrenGretig

//*************************************************************************

// Controleert of er een track is, die overeenkomt met de track van 
// het vak dat je wilt plaatsen, met precies 1 vak op de huidige 
// dag. 'tijdslot' wordt gebruikt om de dag te berekenen.
// In de array trackTeller[] wordt opgeslagen hoevaak een track les heeft
// op een dag. De functie retourneert:
// - true, als er geen track is met precies 1 vak op de dag
// - false, als er wel een track is met precies 1 vak op de dag
bool Rooster::minUrenGretig (int tijdslot, int trackTeller[],
                             int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int dag = (tijdslot / nrUrenPerDag), // de huidige dag
      i, // for loop, loopt over tijdsloten
      j, // loopt over tracks van een vak
      z; // loopt over zalen
  resetInt (trackTeller, MaxNrTracks);

  for (i = (dag * nrUrenPerDag); i <= tijdslot; i++) { 
    for (z = 0; z < nrZalen; z++){     
         
      if (rooster[i][z] != -1 ) {    

        for (j = 0; j < vakken[rooster[i][z]].getAantalTracks(); j++){
          trackTeller[vakken[rooster[i][z]].getTrack(j)]++; 
        }//for

      }//if
      
    }//for
  }//for

  for (i = 0; i < MaxNrTracks; i++){
    if (trackTeller[i] == 1 && vakkenPerTrack[i] != 1) {
      return false;

    }//if
  }//for

  return true;

}  // minUrenGretig

//*************************************************************************

// Controleert of de meegegeven docent les geeft op het meegegeven tijdslot
// bij de meegegeven zaal hoeft niet gecontroleerd te worden, omdat hier
// mogelijk een vak wordt geplaatst
// De functie retourneert: 
// - true, als de docent op dit uur college geeft
// - false, als de docent op dit uur geen college geeft
bool Rooster::geeftNuCollege(int docent, int zaal, int tijdslot, 
                             int rooster[MaxNrTijdsloten][MaxNrZalen])
{ int j; // for loop

  for (j = 0; j < nrZalen; j++){
    if (j != zaal && rooster[tijdslot][j] != -1 
        && vakken[rooster[tijdslot][j]].getDocentNummer() == docent) {
      return true;

    }//if
  }//for

  return false;

}  // geeftNuCollege

//*************************************************************************

// Berekent aan hoeveel voorwaardes het rooster zou voldoen, wanneer
// het meegegeven vak met docent, op de meegegeven tijdslot en zaal zou
// worden geplaatst
// De score wordt geretourneerd 
int Rooster::besteScore (int tijdslot, int zaal, int docent, int vak, 
                         int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int teller = 0; // aan hoeveel voorwaardes voldoet dit deelrooster
  int i; // for loop
  int trackTeller[MaxNrTracks]; // hoevaak elke track op een dag voorkomt
  int tussenurenPerTrack[MaxNrTracks]; // het aantal tussenuren per track
                                       // op een dag

  if (!geeftAlCollege(docent, tijdslot, rooster)) {
    teller++;
  }//if
  if (!minUrenGretig(tijdslot, trackTeller, rooster)) {
    for (i = 0; i < MaxNrTracks; i++) {
      if (trackTeller[i] == 1 && vakken[vak].zoekTrack(i)) {
        teller++;
      }//if
    }//for
  }//if
  if (aantalTussenurenGretig(tijdslot, zaal, vak, 
                             tussenurenPerTrack, rooster)) {
    teller++;
  }//if

  return teller;

}  // besteScore

//*************************************************************************

// Bepaalt op gretige wijze een rooster, wat aan zoveel mogelijk voorwaarden
// voldoet. Op elk punt wordt gekeken wat het beste deelrooster is, en die 
// wordt gekozen
// Als een vak wordt ingeroosterd, wordt de membervariabele 'ingeroosterd' op
// true gezet
// Als een vak ergens is neergezet, wordt deze keuze niet meer herzien
void Rooster::bepaalRoosterGretig (int rooster[MaxNrTijdsloten][MaxNrZalen]) 
{ int i, j, r, s; // for loop
  int beste, // de score van het beste deelrooster
      tijdslot, // hulpvariabele om het tijdslot te onthouden
                // van het beste deelrooster
      zaal; // hulpvariabele om de zaal te onthouden van het beste deelrooster

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