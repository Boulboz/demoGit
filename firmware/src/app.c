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
#include "Mc32DriverLcd.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

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
    appData.state = APP_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    //Variables locales 
    static bool First_LED_Off = true ; 
    static S_ADCResults Result;
    static uint8_t chennillard = 0;
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            lcd_init();
            //affichage pour état init 
            lcd_bl_on();
            printf_lcd("Tp0 Led+AD 2022-23");
            lcd_gotoxy(1,2);
            printf_lcd("David Loic");
            
            BSP_InitADC10();
            //allumage des toutes les leds
            BSP_LEDOn(BSP_LED_0);
            BSP_LEDOn(BSP_LED_1);
            BSP_LEDOn(BSP_LED_2);
            BSP_LEDOn(BSP_LED_3);
            BSP_LEDOn(BSP_LED_4);
            BSP_LEDOn(BSP_LED_5);
            BSP_LEDOn(BSP_LED_6);
            BSP_LEDOn(BSP_LED_7);
            
            DRV_TMR0_Start();
            //va dans l'état attente
            appData.state = APP_STATE_WAIT;
            
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            if(First_LED_Off == true )
            {
            //toutes les LEDs éteintes
            BSP_LEDOff(BSP_LED_0);
            BSP_LEDOff(BSP_LED_1);
            BSP_LEDOff(BSP_LED_2);
            BSP_LEDOff(BSP_LED_3);
            BSP_LEDOff(BSP_LED_4);
            BSP_LEDOff(BSP_LED_5);
            BSP_LEDOff(BSP_LED_6);
            BSP_LEDOff(BSP_LED_7);    
            First_LED_Off = false; 
            }
            //prise des resultats de l'ADC
            Result = BSP_ReadAllADC();
            //déplace l'écriture pour le LCD afin de 
            lcd_gotoxy(1,3);
            printf_lcd("CH0=%4d CH1=%4d",Result.Chan0,Result.Chan1);
            
            
            //switch chenillard 
            //permet de lire la valeur que nous incrémentons afin 
            //de passer d'une LED à l'autre
            switch(chennillard)
            {
                case 0 :
                    BSP_LEDOn(BSP_LED_0);
                    BSP_LEDOff(BSP_LED_7);  
                    break;
                case 1 :
                    BSP_LEDOn(BSP_LED_1);
                    BSP_LEDOff(BSP_LED_0);
                    break;
                case 2 :
                    BSP_LEDOff(BSP_LED_1);
                    BSP_LEDOn(BSP_LED_2);
                    break;
                case 3 :
                    BSP_LEDOff(BSP_LED_2);
                    BSP_LEDOn(BSP_LED_3);
                    break;
                case 4 :
                    BSP_LEDOff(BSP_LED_3);
                    BSP_LEDOn(BSP_LED_4);
                    break;
                case 5 :
                    BSP_LEDOff(BSP_LED_4);
                    BSP_LEDOn(BSP_LED_5);
                    break;
                case 6 :
                    BSP_LEDOff(BSP_LED_5);
                    BSP_LEDOn(BSP_LED_6);
                    break;
                case 7 :
                    BSP_LEDOff(BSP_LED_6);
                    BSP_LEDOn(BSP_LED_7);
                    break;
                
            }
            //incrémentation chenillard
            chennillard++;
            //remise a 0 du chenillard
            if(chennillard >7)
            {
                chennillard = 0;
                
            }
            //retour dans l'état attente
            appData.state = APP_STATE_WAIT;
            break;
        }
        //état attente
        case APP_STATE_WAIT :
        {
            //attend intéruption du timmer 
            break;
        }
        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}
void APP_UpdateState (APP_STATES NewState)
{
    appData.state = NewState ;
    
}
 

/*******************************************************************************
 End of File
 */
