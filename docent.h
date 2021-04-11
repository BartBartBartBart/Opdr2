// Definitie van de klasse Docent

#ifndef DocentHVar  // voorkom dat dit bestand meerdere keren
#define DocentHVar  // ge-include wordt

class Docent
{ public:
    Docent(itn nummer0, int uren0[], int aantalUren0);

  private:
    int nummer;
    int aantalUren;
    int uren[aantalUren];

}

#endif