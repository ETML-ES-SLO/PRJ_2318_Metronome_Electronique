#ifndef GesPEc12_h
#define GesPEc12_h

// GesPec12.h
// C. HUBER    14/05/2014
// Creation pour migration PIC32MX

// Fonctions pour la gestion du Pec12
//
//
// Principe : Il est nécessaire d'appeler cycliquement la fonction ScanPec12
//            avec un cycle de 1 ms
//
//  Pour la gestion du Pec12, il y a 9 fonctions à disposition :
//       Pec12IsPlus       true indique un nouveau incrément
//       Pec12IsMinus      true indique un nouveau décrément
//       Pec12IsOK         true indique action OK
//       Pec12IsESC        true indique action ESC
//       Pec12NoActivity   true indique abscence d'activité sur PEC12
//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incrément
//       Pec12ClearMinus   annule indication de décrément
//       Pec12ClearOK      annule indication action OK
//       Pec12ClearESC     annule indication action ESC
//
//
//---------------------------------------------------------------------------


// définitions des types qui seront utilisés dans cette application

#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------*/
/*                                PEC12 BPM                                   */
/*----------------------------------------------------------------------------*/
#define PEC12_BPM_A         PLIB_PORTS_PinGet(0, PEC12_BPM_A_PORT, PEC12_BPM_A_BIT)
#define PEC12_BPM_B         PLIB_PORTS_PinGet(0, PEC12_BPM_B_PORT, PEC12_BPM_B_BIT)
#define PEC12_BPM_PB        PLIB_PORTS_PinGet(0, PEC12_BPM_PB_PORT, PEC12_BPM_PB_BIT)

// Definitions pour fonction PLIB_PORTS
#define PEC12_BPM_A_PORT    PORT_CHANNEL_C
#define PEC12_BPM_A_BIT     PORTS_BIT_POS_1 //RC1
#define PEC12_BPM_B_PORT    PORT_CHANNEL_C
#define PEC12_BPM_B_BIT     PORTS_BIT_POS_2 //RC2
#define PEC12_BPM_PB_PORT   PORT_CHANNEL_C
#define PEC12_BPM_PB_BIT    PORTS_BIT_POS_0 //RC0

/*----------------------------------------------------------------------------*/
/*                                PEC12 MODE                                  */
/*----------------------------------------------------------------------------*/
#define PEC12_MODE_A        PLIB_PORTS_PinGet(0, PEC12_MODE_A_PORT, PEC12_MODE_A_BIT)
#define PEC12_MODE_B        PLIB_PORTS_PinGet(0, PEC12_MODE_B_PORT, PEC12_MODE_B_BIT)
#define PEC12_MODE_PB       PLIB_PORTS_PinGet(0, PEC12_MODE_PB_PORT, PEC12_MODE_PB_BIT)

// Definitions pour fonction PLIB_PORTS
#define PEC12_MODE_A_PORT   PORT_CHANNEL_C
#define PEC12_MODE_A_BIT    PORTS_BIT_POS_4 //RC4
#define PEC12_MODE_B_PORT   PORT_CHANNEL_C
#define PEC12_MODE_B_BIT    PORTS_BIT_POS_5 //RC5
#define PEC12_MODE_PB_PORT  PORT_CHANNEL_C
#define PEC12_MODE_PB_BIT   PORTS_BIT_POS_3 //RC3


// structure du descripteur du PEC
// Migration : remplacement bool par champ 1 bit
typedef struct {
            uint8_t Inc : 1;             // événement incrément
            uint8_t Dec : 1;             // événement décrément
            uint8_t OK  : 1;              // événement action OK
            uint8_t ESC : 1;             // événement action ESC
            uint8_t NoActivity: 1 ;      // Indication de non activité
            uint16_t PressDuration;   // Pour durée pression du P.B.
            uint16_t InactivityDuration;   // Pour durée inactivité
} S_Pec12_Descriptor;

//// structure pour l'action de auvegarde sur S9
//// Migration : remplacement bool par champ 1 bit
//typedef struct {
//            uint8_t OK : 1;             //événement d'appui sur S9
//}S_S9_Descriptor;


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Principe utilisation des fonctions
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//
// ScanPec12 (bool ValA, bool ValB, bool ValPB)
//              Routine effectuant la gestion du Pec12
//              recoit la valeur des signaux et du boutons
//
// s'appuie sur le descripteur global.
// Aprés l'appel le descripteur est mis à jour

// Comportement du PEC12
// =====================

// Attention 1 cran génère une pulse complète (les 4 combinaisons)
// D'ou traitement uniquement au flanc descendand de B

// Dans le sens horaire CW:
//     __________                      ________________
// B:            |____________________|
//     ___________________                       _________
// A:                     |_____________________|                    

// Dans le sens anti-horaire CCW:
//     ____________________                      _________
// B:                      |____________________|
//     __________                       __________________
// A:            |_____________________|        

void ScanPec12_BPM (bool ValA, bool ValB, bool ValPB);

void Pec12Init_BPM (void);

void ScanPec12_MODE (bool ValA, bool ValB, bool ValPB);

void Pec12Init_MODE (void);

//       Pec12IsPlus       true indique un nouveau incrément
bool Pec12IsPlus    (void);
//       Pec12IsMinus      true indique un nouveau décrément
bool Pec12IsMinus    (void);
//       Pec12IsOK         true indique action OK
bool Pec12IsOK    (void);
//       Pec12IsESC        true indique action ESC
bool Pec12IsESC    (void);
//       Pec12NoActivity   true indique abscence d'activité sur PEC12
bool Pec12NoActivity    (void);

//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incrément
void Pec12ClearPlus   (void);
//       Pec12ClearMinus   annule indication de décrément
void Pec12ClearMinus   (void);
//       Pec12ClearOK      annule indication action OK
void Pec12ClearOK   (void);
//       Pec12ClearESC     annule indication action ESC
void Pec12ClearESC   (void);
void Pec12ClearInactivity   (void);


#endif
