// GesPec12.c  Canevas pour réalisation  
// C. HUBER    09/02/2015

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

#include "GesPec12.h"
#include "Mc32Debounce.h"

// Descripteur des signaux BPM
S_SwitchDescriptor DescrA_BPM;
S_SwitchDescriptor DescrB_BPM;
S_SwitchDescriptor DescrPB_BPM;

// Descripteur des signaux MODE
S_SwitchDescriptor DescrA_MODE;
S_SwitchDescriptor DescrB_MODE;
S_SwitchDescriptor DescrPB_MODE;

// Structure pour les traitement du Pec12
S_Pec12_Descriptor Pec12;

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
// Après l'appel le descripteur est mis à jour

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



/*----------------------------------------------------------------------------*/
/*                                PEC12 BPM                                   */
/*----------------------------------------------------------------------------*/
void ScanPec12_BPM (bool ValA, bool ValB, bool ValPB)
{
   // Traitement antirebond sur A, B et PB
   DoDebounce (&DescrA_BPM, ValA);
   DoDebounce (&DescrB_BPM, ValB);
   DoDebounce (&DescrPB_BPM, ValPB);
   
   // Détection incrément
   if((DebounceIsPressed(&DescrB_BPM) == true) && (DebounceGetInput(&DescrA_BPM) == 1)) //Si flanc descendant sur B et signal A à l'état 1
   {
       Pec12.Inc = 1; //Incrémentation
       DebounceClearPressed(&DescrB_BPM);
   }
   // Détection décrément
   else if((DebounceIsPressed(&DescrB_BPM) == true) && (DebounceGetInput(&DescrA_BPM) == 0)) //Si flanc descendant sur B et signal A à l'état 0
   {
       Pec12.Dec = 1; //Décrémentation
       DebounceClearPressed(&DescrB_BPM);
   }
    
   // Traitement du PushButton
   if(DebounceIsPressed(&DescrPB_BPM) == true)
   {
       //Incrémente le compteur de temps d'appui du PEC12
       Pec12.PressDuration++;
   }
   else if (DebounceIsReleased(&DescrPB_BPM) == true)
   {
       //Si l'appui a duré 500ms ou moins -> OK, sinon ESC
       if(Pec12.PressDuration < 500)
       {
           Pec12.OK = 1;
       }
       else if (Pec12.PressDuration >= 500)
       {
           Pec12.ESC = 1;
       }
       
       //Clear des états d'appui et de relâche et remise du compteur de durée d'appui à 0
       Pec12.PressDuration = 0;
       DebounceClearPressed(&DescrPB_BPM);
       DebounceClearReleased(&DescrPB_BPM);
   }
 } // ScanPec12_BPM


void Pec12Init_BPM (void)
{
   // Initialisation des descripteurs de touches Pec12
   DebounceInit(&DescrA_BPM);
   DebounceInit(&DescrB_BPM);
   DebounceInit(&DescrPB_BPM);
   
   // Init de la structure PEC12
    Pec12.Inc = 0;             // événement incrément  
    Pec12.Dec = 0;             // événement décrément 
    Pec12.OK = 0;              // événement action OK
    Pec12.ESC = 0;             // événement action ESC
    Pec12.NoActivity = 0;      // Indication d'activité
    Pec12.PressDuration = 0;   // Pour durée pression du P.B.
    Pec12.InactivityDuration = 0; // Durée inactivité
  
 } // Pec12Init_BPM


/*----------------------------------------------------------------------------*/
/*                                PEC12 MODE                                  */
/*----------------------------------------------------------------------------*/
void ScanPec12_MODE (bool ValA, bool ValB, bool ValPB)
{
   // Traitement antirebond sur A, B et PB
   DoDebounce (&DescrA_MODE, ValA);
   DoDebounce (&DescrB_MODE, ValB);
   DoDebounce (&DescrPB_MODE, ValPB);
   
   // Détection incrément
   if((DebounceIsPressed(&DescrB_MODE) == true) && (DebounceGetInput(&DescrA_MODE) == 1)) //Si flanc descendant sur B et signal A à l'état 1
   {
       Pec12.Inc = 1; //Incrémentation
       DebounceClearPressed(&DescrB_MODE);
   }
   // Détection décrément
   else if((DebounceIsPressed(&DescrB_MODE) == true) && (DebounceGetInput(&DescrA_MODE) == 0)) //Si flanc descendant sur B et signal A à l'état 0
   {
       Pec12.Dec = 1; //Décrémentation
       DebounceClearPressed(&DescrB_MODE);
   }
    
   // Traitement du PushButton
   if(DebounceIsPressed(&DescrPB_MODE) == true)
   {
       //Incrémente le compteur de temps d'appui du PEC12
       Pec12.PressDuration++;
   }
   else if (DebounceIsReleased(&DescrPB_MODE) == true)
   {
       //Si l'appui a duré 500ms ou moins -> OK, sinon ESC
       if(Pec12.PressDuration < 500)
       {
           Pec12.OK = 1;
       }
       else if (Pec12.PressDuration >= 500)
       {
           Pec12.ESC = 1;
       }
       
       //Clear des états d'appui et de relâche et remise du compteur de durée d'appui à 0
       Pec12.PressDuration = 0;
       DebounceClearPressed(&DescrPB_MODE);
       DebounceClearReleased(&DescrPB_MODE);
   }
 } // ScanPec12_MODE

void Pec12Init_MODE (void)
{
   // Initialisation des descripteurs de touches Pec12
   DebounceInit(&DescrA_MODE);
   DebounceInit(&DescrB_MODE);
   DebounceInit(&DescrPB_MODE);
   
   // Init de la structure PEC12
    Pec12.Inc = 0;             // événement incrément  
    Pec12.Dec = 0;             // événement décrément 
    Pec12.OK = 0;              // événement action OK
    Pec12.ESC = 0;             // événement action ESC
    Pec12.NoActivity = 0;      // Indication d'activité
    Pec12.PressDuration = 0;   // Pour durée pression du P.B.
    Pec12.InactivityDuration = 0; // Durée inactivité
  
 } // Pec12Init_MODE


//       Pec12IsPlus       true indique un nouveau incrément
bool Pec12IsPlus    (void) {
   return (Pec12.Inc);
}

//       Pec12IsMinus      true indique un nouveau décrément
bool Pec12IsMinus    (void) {
   return (Pec12.Dec);
}

//       Pec12IsOK         true indique action OK
bool Pec12IsOK    (void) {
   return (Pec12.OK);
}

//       Pec12IsESC        true indique action ESC
bool Pec12IsESC    (void) {
   return (Pec12.ESC);
}

//       Pec12NoActivity   true indique abscence d'activité sur PEC12
bool Pec12NoActivity    (void) {
   return (Pec12.NoActivity);
}

//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incrément
void Pec12ClearPlus   (void) {
   Pec12.Inc = 0;
}

//       Pec12ClearMinus   annule indication de décrément
void Pec12ClearMinus   (void) {
   Pec12.Dec = 0;
}

//       Pec12ClearOK      annule indication action OK
void Pec12ClearOK   (void) {
   Pec12.OK = 0;
}

//       Pec12ClearESC     annule indication action ESC
void Pec12ClearESC   (void) {
   Pec12.ESC = 0;
}

void Pec12ClearInactivity   (void) {
  Pec12.NoActivity = 0;
  Pec12.InactivityDuration = 0;
}


