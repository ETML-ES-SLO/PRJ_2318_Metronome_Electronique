/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "Gest_TFT_2318.h"
#include "DefineLCD.h"
#include "buzzer.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define MAX_BPM 300
#define INIT_BPM 70
#define MIN_BPM 10
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;
MODE_STATES modeState;
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    APP_UpdateState(APP_STATE_INIT);
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */

    //Initialisation du SPI
//    DRV_SPI0_Initialize();
    
    //Initialisation des timers
//    DRV_TMR0_Initialize();
    
    //Initialisation de l'écran
    TFT_Init();
    
//    DRV_OC0_Initialize();
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
//    static uint32_t i = 0;
//    static uint32_t note = 0;
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            // Initialisation PEC12
            Pec12Init_BPM();
            Pec12Init_MODE();
            
            //Démarrage des timers
            DRV_TMR0_Start();
            DRV_TMR1_Start();
            
            DRV_OC0_Start();
            
            //Changement d'état
            APP_UpdateState(APP_STATE_WAIT);
            break;
        }
        
        case APP_STATE_WAIT:
        {
            //Ne rien écrire ici!
            break;
        }
        
        case APP_STATE_SERVICE_TASKS:
        {
            uint16_t actualBPM;
            BPM_Set(actualBPM);
//            //Changement de note toutes les secondes (do -> ré, ...)
//            //Compteur 1sec
//            i = (i + 1) % 1000;
//            
//            //A chaque début de nouvelle période, on passe à la note suivante
//            if (i == 0)
//            {
//                note = (note + 1) % 24;
//                
//                DRV_TMR1_PeriodValueSet(notes[note]);
//                DRV_OC0_PulseWidthSet(notes[note] / 2);
//            }
                
            
            
            APP_UpdateState(APP_STATE_WAIT);
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    } //end of state machine
} //end of APP_Tasks

//Fonction utilisée pour la mise à jour de l'état de la machine appData.state
void APP_UpdateState ( APP_STATES NewState )
{
    appData.state = NewState;
} //end of APP_UpdateState


//Changement des BPM
void BPM_Set(uint16_t nBPM)
{
    static BPMAdjustMode mode = UNITES;  // État initial
    
    // Variable contenant le nombre de BPMs (initialement 70)
    nBPM = INIT_BPM;
    
    // Changement d'état
    if (Pec12IsOK() == true) 
    {
        Pec12ClearOK();
        switch (mode) 
        {
            case UNITES:
                mode = DIZAINES;
                break;
            case DIZAINES:
                mode = CENTAINES;
                break;
            case CENTAINES:
                mode = UNITES;
                break;
        }
    }
    
    // Ajustement des BPM en fonction de l'état
    switch (mode) {
        case UNITES:
            if (Pec12IsPlus() == true) 
            {
                Pec12ClearPlus();
                if (nBPM < MAX_BPM) 
                {
                    nBPM++;
                } 
                else
                {
                    nBPM = MAX_BPM;
                }
            }
            if (Pec12IsMinus() == true) 
            {
                Pec12ClearMinus();
                if (nBPM > MIN_BPM) 
                {
                    nBPM--;
                } 
                else 
                {
                    nBPM = MIN_BPM;
                }
            }
            break;
            
        case DIZAINES:
            if (Pec12IsPlus() == true) 
            {
                Pec12ClearPlus();
                if (nBPM <= MAX_BPM - 10) 
                {
                    nBPM += 10;
                } 
                else 
                {
                    nBPM = MAX_BPM;
                }
            }
            if (Pec12IsMinus() == true) 
            {
                Pec12ClearMinus();
                if (nBPM >= MIN_BPM + 10) 
                {
                    nBPM -= 10;
                } 
                else 
                {
                    nBPM = MIN_BPM;
                }
            }
            break;
            
        case CENTAINES:
            if (Pec12IsPlus() == true) 
            {
                Pec12ClearPlus();
                if (nBPM <= MAX_BPM - 100)
                {
                    nBPM += 100;
                } 
                else 
                {
                    nBPM = MAX_BPM;
                }
            }
            if (Pec12IsMinus() == true) 
            {
                Pec12ClearMinus();
                if (nBPM >= MIN_BPM + 100) 
                {
                    nBPM -= 100;
                } 
                else 
                {
                    nBPM = MIN_BPM;
                }
            }
            break;
    }
    
    // On pourrait retourner le nombre de BPM ici si nécessaire
    // return nBPM;
}// end of BPM_Set







/*******************************************************************************
 End of File
 */
