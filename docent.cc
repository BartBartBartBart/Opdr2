#include "docent.h"

using namespace std;

Docent::Docent ()
{ 

}

void Docent::setWaardes (int nummer0, int tijdsloten0[], int aantalTijdsloten0)
{ int i;
  nummer = nummer0; 
  aantalTijdsloten = aantalTijdsloten0;

  for (i = 0; i < aantalTijdsloten; i++) {
    tijdsloten[i] = tijdsloten0[i];
  }

}

int Docent::getNummer () 
{
  return nummer;  
}

int Docent::getAantalTijdsloten ()
{
  return aantalTijdsloten;
}

int Docent::getTijdslot (int i) 
{
  return tijdsloten[i];
}

bool Docent::zitErin (int getal) 
{ int i;
  for (i = 0; i < aantalTijdsloten; i++) {
    if (tijdsloten[i] == getal) {
      return true;
    }
  }
  return false;
}