/* ========================================
 *
 * Copyright ÉQUIPE '1E', 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF TEAM '1E'.
 * Renato Castillo          1962797
 * Karl-Philippe Beaudet    1958657
 * Richema Métallus         1953911
 * Tasnim Ahmed             1958545
 * ========================================
*/
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// TODO : S'assurer de l'affichage d'une resistance sur Putty
// TODO : Integrer cette composante du multimetre au Voltmetre par une interface

// Pour l'instant essayer de tester avec des resistances du FreeSoC

///////////////////////////// FUNCTIONS BODY /////////////////////////////

////////////////////////
// Cette fonction permet d'initialiser le UART et selectioner un mode du multimetre
////////////////////////
void UART_initialisation() 
{
    UART_Start();
    // Affichage du MENU
    UART_PutString("== MULTIMETRE == \n \r");
    UART_PutString("  0 - Mode Voltmetre \n \r");
    UART_PutString("  1 - Mode Amperemetre \n \r");
    UART_PutString("  2 - Mode Ohmmetre \n \r");
    UART_PutString("- Veuillez choisir un mode - \n \r");
    CyDelay(4000);
}

////////////////////////
// Cette fonction permet l'utilisation du voltmetre 
////////////////////////

void mode_Ohmetre()
{
    int courant = 0;
    int resistance = 0;
    int voltage = 0;
    char val_resistance[10];
    uint DAC_valeur = 0xff;
    int compte=4095;
    
    DAC_Start();
    SAR_ADC_Start();
    DAC_valeur= 0xff;
    DAC_SetValue(DAC_valeur);
    SAR_ADC_StartConvert();
    while ((DAC_valeur > 0) && (compte >=4000))
    {
        DAC_valeur=DAC_valeur - 0x01;
        DAC_SetValue(DAC_valeur);
        CyDelay(10);
    }
        if (SAR_ADC_IsEndConversion(SAR_ADC_WAIT_FOR_RESULT)!=0)
        {
            compte= SAR_ADC_GetResult16(0);
        }
    
    
}

//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// MAIN LOOP /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


int main(void)
{
    // Variables générales
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    FreeRTOS_Start();
    
    for(;;) 
    {
       
    }
} ///////////////////=========== main loop Ends Here ===============/////////////////////////

/* [] END OF FILE */
