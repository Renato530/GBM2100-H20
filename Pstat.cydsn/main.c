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

CY_ISR(UART_Debut)
{
    UART_Timer_ReadStatusRegister();
    UART_Start();
    UART_PutString("Bienvenue \n\r");
    CyDelay(200);
    UART_PutString("Veuillez inserer la resistance\r\r");
}


int main(void)
{
    // Variables générales
    int courant = 0;
    int resistance = 0;
    int voltage = 0;
    char val_resistance[10];
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    FreeRTOS_Start();
    DAC_Start();
    SAR_ADC_Start();
    UART_Timer_Start();
    UART_interrupt_StartEx(UART_Debut);
    SAR_ADC_StartConvert();
    UART_PutString("Ohmetre \r\r");
    
    vTaskStartScheduler();
    for(;;) 
    {
        courant = 200; // uA 
        //while (SAR_ADC_IsEndConversion(SAR_ADC_RETURN_STATUS)) {} // TODO : Essayer de verifier si la conversion est fini pour faire le calcul
        voltage= SAR_ADC_CountsTo_uVolts(SAR_ADC_GetResult16()); // uV
        resistance = voltage/courant;
        sprintf(val_resistance,"%d",resistance);
        if (resistance!=0)
        {
            UART_PutString(val_resistance);
            UART_PutString("\n");
            UART_PutString("Ohms");
        }
        else 
        {
            UART_PutString("\r\r");
            UART_PutString("Veuillez inserer la resistance");
        }
    }
}

/* [] END OF FILE */
