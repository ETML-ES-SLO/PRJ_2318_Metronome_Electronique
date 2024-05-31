//* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _Gest_TFT_2318_H    /* Guard against multiple inclusion */
#define _Gest_TFT_2318_H

#include <sys/attribs.h>
#include "system_definitions.h"
#include "app.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
}
#endif

void TFT_affResult (int Integration_Time, bool TimedOut);
void TFT_Init (void);
void TFT_MeasureBackGround(void);
void TFT_Cursor_MenuPrincipale ();
void TFT_Menu_Principal (void);
void TFT_PressOkToContinue (void);
void TFT_CablirationInfo(void);
void TFT_AquEnCours (void);
void TFT_Aff_DemoIO (void);
void TFT_DemoIO_Refresh (int PWM_Value);
void TFT_Options(bool Integration_Auto, int Integration_Time);
void TFT_Options_Refresh(bool Integration_Auto);
void TFT_Options_Cursor(bool PosCursor);
void TFT_Options_Aff_Menu_Integration(int Integration_Time);
void TFT_Change_Integration_Confirm (void);
void TFT_Cursor_Modif_Integration (int positionCursor);
void TFT_Change_Integration_Confirm ();
void TFT_Change_Integration_Refresh (int Integration_Time);
void TFT_Change_Integration_Min_Set (void);
void TFT_Menu_Sauvegarde (void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
