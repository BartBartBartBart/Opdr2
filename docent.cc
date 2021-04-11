#include "docent.h"

using namespace std;

Docent::Docent (int nummer0, int uren0[], int aantalUren0)
{ int i;
  nummer = nummer0; 
  aantalUren = aantalUren0;

  for (i = 0; i < aantalUren; i++) {
    uren[i] = uren0[i];
  }
}