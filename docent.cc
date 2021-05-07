// Implementatie van de klasse Docent
// Makers: Lisanne Wallaard (s2865459), Bart den Boef (s2829452)
// Vak: Algoritmiek
// Tweede programmeeropdracht: Rooster
// Studierichting: Kunstmatige Intelligentie
// Jaar van aankomst: 2020
// C++, 7.5.2021, GNU GCC Compiler

#include "docent.h"

using namespace std;

//*************************************************************************

// Default constuctor
Docent::Docent ()
{ 

}  // Docent

//*************************************************************************

// Leest de meegegeven waardes in
// - nummer0 is het nummer van de docent, dat wordt naar nummer gekopieerd
// - tijdsloten0[] is een array waar alle tijdsloten in zitten waarop de docent kan
// lesgeven, die wordt naar tijdsloten[] gekopieerd
// - aantalTijdsloten0 is het aantal tijdsloten dat in tijdsloten0 zit,
// wordt gekopieerd naar tijdsloten[]
void Docent::setWaardes (int nummer0, int tijdsloten0[], int aantalTijdsloten0)
{ int i; // for loop
  nummer = nummer0; 
  aantalTijdsloten = aantalTijdsloten0;

  for (i = 0; i < aantalTijdsloten; i++) {
    tijdsloten[i] = tijdsloten0[i];
  }//for

}  // setWaardes

//*************************************************************************

// Get-functie, retourneert het docent nummer
int Docent::getNummer () 
{
  return nummer;  

}  // getNummer

//*************************************************************************

// Get-functie, retourneert het aantalTijdsloten
int Docent::getAantalTijdsloten ()
{
  return aantalTijdsloten;

}  // getAantalTijdsloten

//*************************************************************************

// Get-functie, retourneert het tijdslot uit de array tijdsloten[] op plek i
int Docent::getTijdslot (int i) 
{
  return tijdsloten[i];

}  // getTijdslot

//*************************************************************************

// Controleert of het tijdslot dat meegegeven wordt in de array tijdsloten[] zit
// - true, als hij erin zit
// - false, als hij er niet in zit
bool Docent::zitErin (int tijdslot) 
{ int i; // for loop

  for (i = 0; i < aantalTijdsloten; i++) {
    if (tijdsloten[i] == tijdslot) {
      return true;

    }//if
  }//for

  return false;

}  // zitErin