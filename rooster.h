// Definitie van klasse Rooster
// Makers: Lisanne Wallaard (s2865459), Bart den Boef (s2829452)
// Vak: Algoritmiek
// Tweede programmeeropdracht: Rooster
// Studierichting: Kunstmatige Intelligentie
// Jaar van aankomst: 2020
// C++, 7.5.2021, GNU GCC Compiler

#ifndef RoosterHVar  // voorkom dat dit bestand meerdere keren
#define RoosterHVar  // ge-include wordt

#include "docent.h"
#include "vak.h"
#include "constantes.h"

class Rooster
{ public:

    // Default constructor
    Rooster ();

    // Lees een instantie in uit invoernaam.
    // Controleer daarbij of het bestand wel te openen is.
    // Pre:
    // * het aantal dagen, het aantal uren per dag, het aantal zalen,
    //   het aantal docenten, het aantal tijdsloten per docent,
    //   die tijdsloten zelf, het aantal vakken, de nummers van de docent
    //   van een vak, het aantal tracks en de tracks zelf die je inleest
    //   vallen binnen de gegeven grenzen (dat hoef je dus niet meer
    //   te controleren).
    // Retourneer:
    // * true, als het bestand te openen was.
    //   In dat geval is alle ingelezen informatie in het object opgeslagen.
    // * false, anders
    bool leesIn (const char* invoerNaam);

    // Druk de informatie van de instantie af op het scherm.
    void drukAf ();

    // Bepaal zo mogelijk een rooster voor de verschillende tracks,
    // rekening houdend met de beschikbaarheid van de docenten,
    // en de eisen aan de tracks.
    // Retourneer:
    // * true, als het lukt om een rooster te bepalen
    // * false, als het niet lukt om een rooster te bepalen
    // Post:
    // * als het lukt om een rooster te bepalen, bevat parameter `rooster'
    //   zo'n rooster. Dan geldt: rooster[s][z] =
    //   - het nummer van het vak dat op tijdslot s (in de week) en zaal z
    //     is ingeroosterd
    //   - -1 als er geen vak op tijdslot s en zaal z is ingeroosterd
    // * aantalDeelroosters is gelijk aan het aantal deelroosters dat we
    //   hebben gezien bij het bepalen van een rooster
    bool bepaalRooster (int rooster[MaxNrTijdsloten][MaxNrZalen],
                            long long &aantalDeelroosters);

    // Bepaal zo mogelijk een rooster voor de verschillende tracks,
    // rekening houdend met de beschikbaarheid van de docenten,
    // en de eisen aan de tracks. Als er een rooster te vinden is,
    // bepaal dan een zo kort mogelijk rooster (een rooster dat zo vroeg
    // mogelijk (qua tijdslot in de week) klaar is).
    // Retourneer:
    // * true, als het lukt om een rooster te bepalen
    // * false, als het niet lukt om een rooster te bepalen
    // Post:
    // * als het lukt om een rooster te bepalen, bevat parameter `rooster'
    //   een zo kort mogelijk rooster. Dan geldt: rooster[s][z] =
    //   - het nummer van het vak dat op tijdslot s (in de week) en zaal z
    //     is ingeroosterd
    //   - -1 als er geen vak op tijdslot s en zaal z is ingeroosterd
    // * aantalDeelroosters is gelijk aan het aantal deelroosters dat we
    //   hebben gezien bij het bepalen van een rooster
    bool bepaalMinRooster (int rooster[MaxNrTijdsloten][MaxNrZalen],
                            long long &aantalDeelroosters);

    // Druk parameter rooster overzichtelijk af op het scherm
    // (dag, tijd, zaal, naam van vak, nummer van docent).
    // Pre:
    // * er is al een instantie ingelezen, en parameter rooster
    //   bevat een rooster voor die instantie
    void drukAfRooster (int rooster[MaxNrTijdsloten][MaxNrZalen]);

    // Bepaal op een gretige manier een rooster voor de ingelezen vakken,
    // docenten en tracks. Als het niet lukt om aan alle eisen voor een
    // geldig rooster te voldoen, probeer er dan `zo goed mogelijk' aan
    // te voldoen.
    // Pre:
    // * het aantal vakken is <= het aantal combinaties (tijdslot,zaal),
    //   zodat daadwerkelijk alle vakken te geven zijn (los van onze andere,
    //   logische eisen aan een rooster)
    // Post:
    // * rooster bevat een rooster voor alle ingelezen vakken.
    void bepaalRoosterGretig (int rooster[MaxNrTijdsloten][MaxNrZalen]);
    
    // Wrapper functie voor resetVakkenPriv()
    void resetVakken ();

  private:
    
    Docent docenten[MaxNrDocenten]; // array met alle docenten
    Vak vakken[MaxNrVakken]; // array met alle vakken
    int vakkenPerTrack[MaxNrTracks]; // array met het aantal vakken per track
    
    // Controleert of docent een vak geeft
    bool zelfdeDocent (int docent, Vak vak);

    // 3 reset functies
    void resetBool (bool A[], int n);
    void resetInt (int A[], int n);
    void resetVakkenPriv ();

    // Controleert of vak A en B een gezamenlijke track bevatten
    bool zelfdeTrack (Vak A, Vak B);

    // Controleert of een docent al lesgeeft op een tijdslot
    bool geeftAlCollege (int docent, int tijdslot, 
                         int rooster[MaxNrTijdsloten][MaxNrZalen]);

    // Controleert of docenten van een track op dezelfde dag les kunnen geven
    bool lesOpZelfdeDag (int track);

    // Controleert of een track meer dan 1 docent heeft
    bool trackHeeftEenDocent (int track);

    // Controleert of een track niet maar 1 vak op een dag aanbiedt
    bool minUren (int dag, int rooster[MaxNrTijdsloten][MaxNrZalen]);

    // 2 hulpfuncties voor aantalTussenuren
    void eersteLes (bool & eerste, int & begin, int track, int tijdslot,
                    int rooster[MaxNrTijdsloten][MaxNrZalen]);
    void tweedeLes (int track, int tijdslot, bool & tweede, int & teller, 
                    int rooster[MaxNrTijdsloten][MaxNrZalen]);

    // Controleert of er geen track is met meer dan 1 tussenuur op een dag
    bool aantalTussenuren (int dag, int rooster[MaxNrTijdsloten][MaxNrZalen]);

    // Controleert of een track niet 2 vakken op 1 uur heeft
    bool zelfdeTrackOpUur (int tijdslot, int zaal, int vak, 
                           int rooster[MaxNrTijdsloten][MaxNrZalen]);

    // Hulpfunctie voor het backtracking-element
    bool dagIsOke (int tijdslot, int rooster[MaxNrTijdsloten][MaxNrZalen]);

    // Hulpfunctie voor aantalTussenurenGretig
    void tweedeLesGretig (int tijdslot, int zaal, int vak, int track, 
                          int j, bool & tweede, int & teller,
                          int rooster[MaxNrTijdsloten][MaxNrZalen]);

    // Controleert het aantal tussenuren op een dag voor bepaalRoosterGretig
    bool aantalTussenurenGretig (int tijdslot, int zaal, int vak, 
                                 int tussenurenPerTrack[MaxNrTracks], 
                                 int rooster[MaxNrTijdsloten][MaxNrZalen]);

    // Controleert het aantal uren dat een track aanbiedt op een dag
    // voor bepaalRoosterGretig
    bool minUrenGretig (int tijdslot, int trackTeller[], 
                        int rooster[MaxNrTijdsloten][MaxNrZalen]);

    // Controleert of een docent lesgeeft op een bepaald tijdstip
    bool geeftNuCollege (int docent, int zaal, int tijdslot, 
                         int rooster[MaxNrTijdsloten][MaxNrZalen]);
                         
    // Kijkt aan hoeveel voorwaardes een deelrooster voldoet 
    // voor bepaalRoosterGretig
    int besteScore (int tijdslot, int zaal, int docent, int vak, 
                    int rooster[MaxNrTijdsloten][MaxNrZalen]);
    
    
    

    int nrDagen,       // aantal dagen in het rooster
        nrUrenPerDag,  // aantal uren per dag
        nrZalen,       // aantal beschikbare zalen
        nrDocenten,    // aantal docenten
        nrVakken,      // aantal vakken
        nrTracks,      // aantal verschillende tracks
        nrTijdsloten;  // aantal tijdsloten
};

#endif

