// Implementatie van de klasse Vak
// Makers: Lisanne Wallaard (s2865459), Bart den Boef (s2829452)
// Vak: Algoritmiek
// Tweede programmeeropdracht: Rooster
// Studierichting: Kunstmatige Intelligentie
// Jaar van aankomst: 2020
// C++, 7.5.2021, GNU GCC Compiler

#include "vak.h"

using namespace std;

//*************************************************************************

// Default constructor
Vak::Vak ()
{ 
  ingeroosterd = false;

} // Vak

//*************************************************************************

// - docentNummer0 wordt ingelezen naar docentNummer
// - tracks0[] wordt gekopieerd naar tracks[]
// - aantalTracks0 wordt gekopieerd naar aantalTracks
// - naam0 wordt gekopieerd naar naam
void Vak::setWaardes(int docentNummer0, int tracks0[], 
                     int aantalTracks0, string naam0)
{ int i; // for loop
  naam = naam0;
  docentNummer = docentNummer0;
  aantalTracks = aantalTracks0;
  
  for (i = 0; i < aantalTracks; i++) {
    tracks[i] = tracks0[i];
  }//for

}  // setWaardes

//*************************************************************************

// Get-functie, retourneert naam
string Vak::getNaam () 
{
  return naam;

}  // getNaam

//*************************************************************************

// Get-functie, retourneert docentNummer
int Vak::getDocentNummer () 
{
  return docentNummer;

}  // getDocentNummer

//*************************************************************************

// Get-functie, retourneert aantalTracks
int Vak::getAantalTracks ()
{
  return aantalTracks;

}  // getAantalTracks

//*************************************************************************

// Get-functie, retourneert de track uit de array tracks[] op plek i
int Vak::getTrack (int i)
{
  return tracks[i];

}  // getTrack

//*************************************************************************

// Zoekt de meegegeven track 'track' op in de array tracks[]
// - true, als track in tracks[] zit
// - false, als dat niet zo is
bool Vak::zoekTrack (int track) 
{ int i; // for loop

  for (i = 0; i < aantalTracks; i++) {
    if (tracks[i] == track) {
      return true;

    }//if
  }//for

  return false;

}  // zoekTrack

//*************************************************************************

// Get-functie, retourneert de bool 'ingeroosterd'
bool Vak::getIngeroosterd () 
{
  return ingeroosterd;

}  // getIngeroosterd

//*************************************************************************

// Set-functie voor ingeroosterd, als 
// - i = 1, ingeroosterd wordt true
// - i = 0, ingeroosterd wordt false
void Vak::setIngeroosterd (int i)
{ if (i == 0){
    ingeroosterd = false;
  }//if
  else if (i == 1) {
    ingeroosterd = true;
  }//else if

}  // setIngeroosterd