// Hoofdprogramma voor oplossing voor tweede programmeeropdracht Algoritmiek,
// voorjaar 2021: Rooster.
//
// Biedt de gebruiker een menustructuur om
// * een instantie van Rooster in te lezen, en daarvoor roosters te maken.
//   (een geldig rooster, een zo kort mogelijk rooster, een gretig rooster)
//
// Lisanne Wallaard (s2865459), Bart den Boef (s2829452)

#include <iostream>
#include <ctime>  // voor clock() en clock_t
#include "constantes.h"
#include "standaard.h"
#include "rooster.h"
#include "docent.h"
#include "vak.h"
using namespace std;
const int MaxBestandsNaamLengte = 30; // maximale lengte van een bestandsnaam

//*************************************************************************

//infoblokje van programma
void infoBlokje ()
{
  cout << "Welkom bij de tweede programmeeropdracht van het vak Algoritmiek: "
       << "Rooster." << endl
       << "Gemaakt door: Lisanne Wallaard (s2865459) en "
       << "Bart den Boef (s2829452)." << endl
       << "Met dit programma kunt u op meerdere manieren een rooster "
       << "opbouwen: met backtracking of op gretige wijze. " << endl
       << "Bij bepaalRooster en bepaalMinRooster voldoet het rooster aan een"
       << " aantal reeds gespecifieerde eisen. " << endl 
       << "Bij bepaalRoosterGretig hoeft dit niet het geval te zijn." << endl
       << "bepaalMinRooster bepaalt een rooster dat zo vroeg mogelijk in de "
       << "week klaar is. " << endl
       << endl;

}  // infoblokje

//*************************************************************************

// Schrijf het menu voor een instantie op het scherm,
// en vraag een keuze van de gebruiker.
// Retourneer: de keuze van de gebruiker
int keuzeUitMenu ()
{ int keuze;

  cout << endl;
  cout << "1. Een rooster bepalen (backtracking)" << endl;
  cout << "2. Een zo kort mogelijk rooster bepalen (backtracking)" << endl;
  cout << "3. Een rooster bepalen (gretig)" << endl;
  cout << "4. Stoppen met deze instantie" << endl;
  cout << endl;
  cout << "Maak een keuze: ";
  cin >> keuze;

  return keuze;

}  // keuzeUitMenu

//*************************************************************************

// Bied de gebruiker een menu om roosters te bepalen voor instantie r1:
// een rooster (met backtracking), een zo kort mogelijk rooster (met
// backtracking), en een rooster (met een gretig algoritme).
// Roep vervolgens r1 aan voor het gekozen soort rooster.
// Herhaal dit totdat de gebruiker aangeeft te willen stoppen.
void menuVoorInstantie (Rooster *r1)
{ int keuze,
      rooster[MaxNrTijdsloten][MaxNrZalen];
  int i, j;
  for (i = 0; i < MaxNrTijdsloten; i++) {
    for (j = 0; j < MaxNrZalen; j++) {
      rooster[i][j] = -1;
    }
  }
  long long aantalDeelroosters;  // aantal deelroosters dat we hebben
                                 // opgebouwd
  clock_t t1, t2;
  bool br;  // lukt het om een (minimaal) rooster te bepalen
            // met backtracking?

  keuze = 0;
  while (keuze!=4)
  {
    keuze = keuzeUitMenu ();

    switch (keuze)
    { case 1:
      case 2: t1 = clock ();
              cout << endl;
              if (keuze==1)
              { cout << "bepaalRooster" << endl;
                for (i = 0; i < MaxNrTijdsloten; i++) {
                  for (j = 0; j < MaxNrZalen; j++) {
                    rooster[i][j] = -1;
                  }
                }
                r1 -> resetVakken();
                aantalDeelroosters = 0;
                br = r1->bepaalRooster (rooster, aantalDeelroosters);
              }
              else
              { cout << "bepaalMinRooster" << endl;
                for (i = 0; i < MaxNrTijdsloten; i++) {
                  for (j = 0; j < MaxNrZalen; j++) {
                    rooster[i][j] = -1;
                  }
                }
                aantalDeelroosters = 0;
                r1 -> resetVakken();
                br = r1->bepaalMinRooster (rooster, aantalDeelroosters);
              }

              if (br)
                r1 -> drukAfRooster (rooster);
              else
              { cout << endl;
                cout << "Helaas, we vonden geen geldig rooster";
              }
              t2 = clock ();
              cout << endl;
              cout << "We hebben hiervoor " << aantalDeelroosters
                   << " deelroosters opgebouwd." << endl;
              cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
               << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;
              break;
      case 3: cout << endl;
              cout << "bepaalRoosterGretig" << endl;
              for (i = 0; i < MaxNrTijdsloten; i++) {
                for (j = 0; j < MaxNrZalen; j++) {
                  rooster[i][j] = -1;
                }
              }
              r1 -> resetVakken();
              r1 -> bepaalRoosterGretig (rooster);
              r1 -> drukAfRooster (rooster);
              break;
      case 4: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }  // switch

  }  // while

}  // menuVoorInstantie

//*************************************************************************

void hoofdmenu ()
{ Rooster *r1;  // pointer, om makkeijk nieuwe objecten te kunnen maken
                // en weer weg te gooien
  int keuze;
  char invoernaam[MaxBestandsNaamLengte+1];

  do
  {
    cout << endl;
    cout << "1. Een instantie inlezen en verwerken" << endl;
    cout << "2. Stoppen" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;
    switch (keuze)
    { case 1: r1 = new Rooster ();
              cout << "Geef de naam van het tekstbestand met de invoer: ";
              cin >> invoernaam;
              if (r1 -> leesIn (invoernaam))
              { r1 -> drukAf ();
                menuVoorInstantie (r1);
              }
              delete r1;  // netjes opruimen
              break;
      case 2: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }

  } while (keuze!=2);

}  // hoofdmenu

//*************************************************************************
  
int main ()
{ infoBlokje();
  hoofdmenu ();

  return 0;

}
