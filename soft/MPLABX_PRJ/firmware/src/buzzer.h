/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    ETML-ES

  File Name:
    buzzer.h

  Author:
    Julien Decrausaz
  
  Description:
    
*******************************************************************************/

#ifndef _EXAMPLE_FILE_NAME_H    /* Guard against multiple inclusion */
#define _EXAMPLE_FILE_NAME_H

//============================================================================//
//                                  INCLUDES                                  //
//============================================================================//
    
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

/******************************************************************************/



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

//#define DO3	152905
//#define DO_3	144300
//#define RE3	136193
//#define RE_3	128576
//#define MI3	121359
//#define FA3	114548
//#define FA_3	108108
//#define SOL3	102041
//#define SOL_3	96316
//#define LA3	90909
//#define LA_3	85800
//#define SI3	80988
//#define DO4	76438
//#define DO_4	72150
//#define RE4	68108
//#define RE_4	64278
//#define MI4	60670
//#define FA4	57266
//#define FA_4	54054
//#define SOL4	51020
//#define SOL_4	48158
//#define LA4	45455
//#define LA_4	42905
//#define SI4	40494

#define DO5	38223
#define DO_5	36078
#define RE5	34051
#define RE_5	32141
#define MI5	30338
#define FA5	28635
#define FA_5	27027
#define SOL5	25510
#define SOL_5	24079
#define LA5	22727
#define LA_5	21451
#define SI5	20248
#define DO6	19111
#define DO_6	18038
#define RE6	17026
#define RE_6	16071
#define MI6	15169
#define FA6	14317
#define FA_6	13514
#define SOL6	12755
#define SOL_6	12039
#define LA6	11364
#define LA_6	10726
#define SI6	10124
    
const uint16_t notes[] = {DO5, DO_5, RE5, RE_5, MI5, FA5, FA_5, SOL5, SOL_5, LA5, LA_5, SI5, DO6, DO_6, RE6, RE_6, MI6, FA6, FA_6, SOL6, SOL_6, LA6, LA_6, SI6};
                            


    
//============================================================================//
//                            FUNCTION PROTOTYPES                             //
//============================================================================//


/******************************************************************************/






    
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
