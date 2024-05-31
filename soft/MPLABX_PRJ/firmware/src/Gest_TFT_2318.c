/* ************************************************************************** */
/** Descriptive Spectrogram_Gest_CoreTimer

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */
#include "Gest_TFT_2318.h"
#include "DriverLCD.h"
#include "DefineLCD.h"

//Initialisation du Touchscreen
void TFT_Init (void)
{
    tft_begin(); 
    setRotation(1); //Pivote de 90°
    
    tft_fillScreen(ILI9341_MAGENTA); 
}


void TFT_Menu_Principal (void)
{
    //Affichage du nombre de BPM
    tft_setTextSize(4);
    tft_setCursor(90,250);
    tft_setTextColor(ILI9341_BLACK);
//    tft_writeString("%d", nbBPM); //nbBPM défini par l'utilisateur avec le PEC12 BPM ********************************************************************************
    tft_setTextSize(2);
    tft_setCursor(130,230);
    tft_setTextColor(ILI9341_BLACK);
    tft_writeString("BPM");
    
    //Affichage des temps par mesure (16 temps)
    //Dessiner 16 petits carrés vides qui seront remplis après chaque temps par mesure
    
    //Ecrire le nombre de temps par mesure choisi par l'utilisateur via le PEC12 Mode
    
    
    //Affichage du mode utilisé actuellement
    tft_setTextSize(2);
    tft_setCursor(200,50);
    tft_setTextColor(ILI9341_BLACK);
//    tft_writeString("%s", mode); *************************************************************************************************************************************
    
}

void TFT_affResult (int Integration_Time, bool TimedOut)
{
//   int I = 0;
//   int MaxValue = 0;
   int LongueurDOndeMax = 0;
   char C_LongueurDOndeMax [10];
   char LongueurDOndeDominante [34];
//   for (I = 0; I < 288; I ++)
//   {
//      tft_drawFastVLine((17+I),60+(131-((Tableau_Resultat [I] * 131) / (0xFFFF-Compensation))),131-(131-((Tableau_Resultat [I] * 131) / (0xFFFF-Compensation))),0xF0EC);
//   }
//   
//   for (I = 0; I < 288; I ++)
//   {
//       if(Tableau_Resultat [I] > MaxValue)
//       {
//           MaxValue = Tableau_Resultat [I];
//           LongueurDOndeMax = (I * 1.77)+ 340;
//       }
//   }   
   Integration_Time = Integration_Time*20;
   sprintf(C_LongueurDOndeMax,"%5d [us]",Integration_Time);
   sprintf(LongueurDOndeDominante,"dominant %3d [nm]",LongueurDOndeMax);
   tft_setTextSize(1);
   tft_setCursor(15,213);
   tft_setTextColor(ILI9341_BLACK);
   tft_writeString(LongueurDOndeDominante);
   tft_setCursor(150,213);
   tft_writeString(C_LongueurDOndeMax);
   if (TimedOut)
   {
        tft_setCursor(210,213);
        tft_writeString("Timed Out !");
   }
}

void TFT_Cursor_MenuPrincipale (void)
{
//    static int LastCursorPos = 0;
//    tft_setTextSize(4);
//    switch (MenuSelected)
//    {
//        case SELECTED_NONE:
//        {
//            if(LastCursorPos != 0)
//            {
//                //clear L'ancien Curseur 
//                tft_fillRect(40,LastCursorPos,20,28,0x221F);             
//            }
//            break;
//        }
//        case SELECTED_Aquisition:
//        {
//            if(LastCursorPos != 0)
//            {
//                //clear L'ancien Curseur 
//                tft_fillRect(40,LastCursorPos,20,28,0x221F);  
//            }
//            tft_setCursor(40,50);
//            tft_writeString(">");
//            LastCursorPos = 50;
//            break;
//        }
//        case SELECTED_Calibration:
//        {
//            if(LastCursorPos != 0)
//            {
//                //clear L'ancien Curseur 
//                tft_fillRect(40,LastCursorPos,20,28,0x221F);  
//            }
//            tft_setCursor(40,100);
//            tft_writeString(">");
//            LastCursorPos = 100;
//            break;
//        }
//        case SELECTED_Options:
//        {
//            if(LastCursorPos != 0)
//            {
//                //clear L'ancien Curseur 
//                tft_fillRect(40,LastCursorPos,20,28,0x221F);  
//            }
//             tft_setCursor(40,150);
//            tft_writeString(">");
//            LastCursorPos = 150;
//            break;
//        }
//        case SELECTED_DEMOIO:
//        {
//            if(LastCursorPos != 0)
//            {
//                //clear L'ancien Curseur 
//                tft_fillRect(40,LastCursorPos,20,28,0x221F);  
//            }
//            tft_setCursor(40,200);
//            tft_writeString(">");
//            LastCursorPos = 200;
//            break;
//        }
//    }
}
    
    
void TFT_CablirationInfo(void)
{
    tft_setTextColor(ILI9341_BLACK);
    tft_fillRect(10,10,300,220,ILI9341_WHITE);
    tft_setCursor(40,50);
    tft_setTextSize(2);
    tft_writeString("Couvrez le capteur");
    tft_setCursor(40,100);
    tft_writeString("Puis");
    tft_setCursor(40,150);
    tft_writeString("Pressez sur OK!");
}

void TFT_PressOkToContinue (void)
{
    tft_setTextColor(ILI9341_BLACK);
    tft_fillRect(10,10,300,220,ILI9341_WHITE);
    tft_setCursor(40,50);
    tft_setTextSize(2);
    tft_writeString("Terminé");
    tft_setCursor(40,100);
    tft_writeString("Pressez sur OK"); 
    tft_setCursor(40,150);
    tft_writeString("pour continuer");     
}

void TFT_AquEnCours (void)
{
   tft_fillRect(10,10,300,220,ILI9341_WHITE);
   tft_setTextColor(ILI9341_BLACK);
   tft_setTextSize(3);
   tft_setCursor(60,50);
   tft_writeString("Acquisition");
   tft_setCursor(125,100);
   tft_writeString("en");
   tft_setCursor(100,150);
   tft_writeString("cours");   
}

void TFT_Aff_DemoIO (void)
{
    tft_fillRect(10,10,300,220,ILI9341_WHITE);
    tft_setTextColor(ILI9341_BLACK);
    tft_setTextSize(3);
    tft_setCursor(15,15);
    tft_writeString("DEMO I/O");
    tft_fillRect(70,70,10,10,ILI9341_BLACK);
    tft_fillRect(120,70,10,10,ILI9341_BLACK);
    tft_fillRect(170,70,10,10,ILI9341_BLACK);
    tft_fillRect(220,70,10,10,ILI9341_BLACK);  
    tft_setTextSize(1);
    tft_setCursor(55,60);
    tft_writeString("Input 1");
    tft_setCursor(105,60);
    tft_writeString("Input 2");
    tft_setCursor(155,60);
    tft_writeString("Input 3");
    tft_setCursor(205,60);
    tft_writeString("Input 4");
    tft_drawFastHLine(10,95,300,ILI9341_BLACK);
    tft_setTextSize(3);
    tft_setCursor(20,100);
    tft_writeString("PWM 1");
    tft_setCursor(200,100);
    tft_writeString("PWM 2");
}

void TFT_DemoIO_Refresh (int PWM_Value)
{
//    char c = '%';
//    static APP_Inputs OldInputs;
//    static int oldPWM_value = 0;
//    char str_value [5];
//    if (OldInputs.Input_1 != appInputs.Input_1)
//    {
//        if(appInputs.Input_1)
//        {
//            tft_fillRect(70,70,10,10,ILI9341_GREEN);
//        }
//        else
//        {
//            tft_fillRect(70,70,10,10,ILI9341_BLACK);
//        }
//    }
//    if (OldInputs.Input_2 != appInputs.Input_2)
//    {
//        if(appInputs.Input_2)
//        {
//            tft_fillRect(120,70,10,10,ILI9341_GREEN);
//        }
//        else
//        {
//            tft_fillRect(120,70,10,10,ILI9341_BLACK);
//        }
//    } 
//    if (OldInputs.Input_3 != appInputs.Input_3)
//    {
//        if(appInputs.Input_3)
//        {
//            tft_fillRect(170,70,10,10,ILI9341_GREEN);
//        }
//        else
//        {
//            tft_fillRect(170,70,10,10,ILI9341_BLACK);
//        }
//    }
//    if (OldInputs.Input_4 != appInputs.Input_4)
//    {
//        if(appInputs.Input_4)
//        {
//            tft_fillRect(220,70,10,10,ILI9341_GREEN);
//        }
//        else
//        {
//            tft_fillRect(220,70,10,10,ILI9341_BLACK);
//        }
//    }
//    OldInputs = appInputs;
//    
//    if (oldPWM_value != PWM_Value)
//    {
//        oldPWM_value = PWM_Value;
//        PWM_Value = (PWM_Value * 100)/65535;
//        sprintf(str_value,"%d %c",PWM_Value,c);
//        tft_setTextColor_F(ILI9341_BLACK,ILI9341_WHITE);
//        tft_setTextSize(3);
//        tft_setCursor(20,150);
//        tft_writeString(str_value);
//        tft_setCursor(230,150);
//        tft_writeString(str_value);
//    }
//           
}

void TFT_Options(bool Integration_Auto, int Integration_Time)
{
    char integration [10];
    tft_setTextColor(ILI9341_WHITE);
    tft_fillRect(10,10,300,220,ILI9341_BLUE);
    tft_setTextSize(2);
    tft_setCursor(45,50);
    tft_writeString("Integration Auto"); 
    tft_fillRect(250,45,20,20,ILI9341_WHITE);
    tft_fillRect(252,47,16,16,ILI9341_BLUE);
    if(Integration_Auto)
    {
        tft_fillRect(254,49,12,12,ILI9341_WHITE);
        tft_setTextColor(ILI9341_DARKGREY);
    }
    tft_drawFastHLine(10,135,300,ILI9341_WHITE);
    tft_setCursor(45,100);
    tft_writeString("Changer Integration"); 
    tft_setCursor(45,150);
    tft_setTextColor(ILI9341_WHITE);
    tft_writeString("Valeur d'integration:"); 
    tft_setCursor(115,175);
    Integration_Time = Integration_Time * 20;
    sprintf(integration,"%d [us]",Integration_Time);
    tft_writeString(integration); 
}

void TFT_Options_Refresh(bool Integration_Auto)
{
    if(Integration_Auto)
    {
        tft_fillRect(254,49,12,12,ILI9341_WHITE);
        tft_setTextColor(ILI9341_DARKGREY);
        tft_setCursor(45,100);
        tft_writeString("Changer Integration"); 
    }
    else
    {
        tft_fillRect(254,49,12,12,ILI9341_BLUE);
        tft_setTextColor(ILI9341_WHITE);
        tft_setCursor(45,100);
        tft_writeString("Changer Integration"); 
    }
} 

void TFT_Options_Cursor(bool PosCursor)
{
    if(PosCursor)
    {
        tft_setTextSize(2);
        tft_setCursor(30,50);
        tft_fillRect(25,95,20,20,ILI9341_BLUE);
        tft_writeString(">"); 
    }
    else
    {
        tft_setTextSize(2);
        tft_setCursor(30,100);
        tft_fillRect(25,45,20,20,ILI9341_BLUE);
        tft_writeString(">"); 
    }
}

void TFT_Options_Aff_Menu_Integration(int Integration_Time)
{
    char value [8];
    int tmp;
    tmp = Integration_Time;
    tft_setTextColor(ILI9341_WHITE);
    tft_fillRect(10,10,300,220,ILI9341_BLUE);
    tft_setTextSize(2);
    tft_setCursor(20,20);
    tft_writeString("Changez la valeur");
    tft_setCursor(20,40);
    tft_writeString("d'integration");
    tft_setTextSize(4);
    sprintf(value,"%04d [us]",tmp);
    tft_setCursor(65,110);
    tft_writeString(value);
    tft_setCursor(65,142);
    tft_writeString("^");
}

void TFT_Cursor_Modif_Integration (int positionCursor)
{
    tft_fillRect(65,140,120,40,ILI9341_BLUE);
    switch (positionCursor)
    {
        case 1:
        {           
            tft_setCursor(65,142);
            tft_writeString("^");
        }
        break;
        case 2:
        {
            tft_setCursor(89,142);
            tft_writeString("^");
        }
        break;
        case 3 :
        {
            tft_setCursor(113,142);
            tft_writeString("^");
        }
        break;
        case 4 :
        {
            tft_setCursor(137,142);
            tft_writeString("^");
        }
        break;
    }
}

void TFT_Change_Integration_Confirm ()
{
    tft_fillRect(20,180,280,20,ILI9341_WHITE);
    tft_setTextColor(ILI9341_BLACK);
    tft_setTextSize(1);
    tft_setCursor(40,190);
    tft_writeString("Sauvegarde sur OK / annuler sur ESC");  
}

void TFT_Change_Integration_Refresh (int Integration_Time)
{
    char value [10];
    sprintf(value,"%04d [us]",Integration_Time);
    tft_setTextSize(4);
    tft_setCursor(65,110);
    tft_setTextColor_F(ILI9341_WHITE,ILI9341_BLUE); 
    tft_writeString(value);
}

void TFT_Change_Integration_Min_Set (void)
{
    tft_setTextSize(2);
    tft_setCursor(100,150);
    tft_setTextColor(ILI9341_WHITE); 
    tft_writeString("Minmum 147 [us] !");
}

void TFT_Menu_Sauvegarde (void)
{
    tft_fillRect(20,100,280,60,ILI9341_BLACK);
    tft_fillRect(25,105,270,50,ILI9341_WHITE);
    tft_setTextSize(2);
    tft_setCursor(70,110);
    tft_setTextColor(ILI9341_BLACK); 
    tft_writeString("Sauvegarde ?");
    tft_setCursor(30,130);
    tft_writeString("ESC: Non");
    tft_setCursor(200,130);
    tft_writeString("OK: Oui");
}