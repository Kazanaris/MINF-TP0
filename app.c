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
#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "Mc32DriverAdc.h"
#include "Mc32DriverLcd.h"
#include "bsp.h"

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
    //Initialisation du LCD
    lcd_init();
    lcd_bl_on();
    //Initialisation ADC via BSP
    BSP_InitADC10();
}

/*******************************************************************************
  Function:
    void APP_UpdateState ( APP_STATES newState )

  Remarks:
    See prototype in app.h.
 */
void APP_UpdateState ( APP_STATES NewState )
{
    appData.state = NewState;
}

/*******************************************************************************
  Function:
    void LedOn ( void )

  Remarks:
    See prototype in app.h.
 */

void LedOn ( void )
{
    LED0_W = 0;
    LED1_W = 0;
    LED2_W = 0;
    LED3_W = 0;
    LED4_W = 0;
    LED5_W = 0;
    LED6_W = 0;
    LED7_W = 0;
}

/*******************************************************************************
  Function:
    void LedOff ( void )

  Remarks:
    See prototype in app.h.
 */

void LedOff ( void )
{
    LED0_W = 1;
    LED1_W = 1;
    LED2_W = 1;
    LED3_W = 1;
    LED4_W = 1;
    LED5_W = 1;
    LED6_W = 1;
    LED7_W = 1;
}

/*******************************************************************************
  Function:
    void Chenillard (  )

  Remarks:
    See prototype in app.h.
 */
void Chenillard( void )
{
    static uint8_t current_led = 0;

    switch (current_led)
    {
        case 0:
            LED0_W = 0;
            LED7_W = 1;
            break;
                
        case 1:
            LED1_W = 0;
            LED0_W = 1;
            break;
                
        case 2:
            LED2_W = 0;
            LED1_W = 1;
            break;
                
        case 3:
            LED3_W = 0;
            LED2_W = 1;
            break;
                
        case 4:
            LED4_W = 0;
            LED3_W = 1;
            break;
                
        case 5:
            LED5_W = 0;
            LED4_W = 1;
            break;
                
        case 6:
            LED6_W = 0;
            LED5_W = 1;
            break;
                
        case 7:
            LED7_W = 0;
            LED6_W = 1;
            break;
    }
    current_led = (current_led + 1);
    
    
    if (current_led == 8)
    {
        current_led = 0;
    }
    
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    static bool FlagLed = false; 
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            //Start Timer
            DRV_TMR0_Start();
            APP_Initialize();
            printf_lcd("Tp0 Led+AD <2025>");
            lcd_gotoxy(1,2);
            printf_lcd("Kirian Gruber");
            LedOn();
            //mise à jour de l'état
            appData.state = APP_STATE_WAIT;
            break;
        }
        
        case APP_STATE_WAIT:
        {
            //Ne Rien Faire
            break;
        }
        
        case APP_STATE_SERVICE_TASKS:
        {
            static bool LedOffFirstTime = true;
            static uint8_t compteurChenillard = 0;
            //Lecture des 2 potentiomètres 
            appData.adcRes = BSP_ReadAllADC();
            //Affichage de la valeur brute des ADC des potentiomètres
            lcd_gotoxy(1,3);
            printf_lcd("Ch0 %4d / Ch1 %4d",
                    appData.adcRes.Chan0, appData.adcRes.Chan1);
            //éteindre toutes les LEDs
            if(LedOffFirstTime == true)
            {
               LedOff();
               LedOffFirstTime = false;
            }
            
             
           
            
            //appel de la fonction chenillard
            if (compteurChenillard == 0)
            {
               Chenillard();
               compteurChenillard ++;
            }
            else
            {
                compteurChenillard = 0;
            }
            //mise à jour de l'état
            appData.state = APP_STATE_WAIT;
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
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

 

/*******************************************************************************
 End of File
 */
