/* ========================================
 *
 * Copyright GBM2100 Équipe 1E, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Équipe 1E.
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

volatile uint32_t t_10us=0;


///////////////////////////// FUNCTIONS BODY /////////////////////////////

void UART_initialisation() 
{
    UART_Start();
    UART_PutString("- Bienvenue au multimetre de l'equipe 1e - \n\r ");
    CyDelay(2000);
    UART_PutString("- Veuillez choisir un mode - \n \r");
    CyDelay(4000);
   
}

void mode_Capacimetre()
{
    char capacitance[10];
    DAC_Stop();
    float adcResult;
    ADC_SAR_IsEndConversion(ADC_SAR_RETURN_STATUS);
    adcResult = ADC_SAR_GetResult16();
    UART_PutString("- Mode Capacimetre - \n\r");
    DAC_Start();
   
    int n=0;
    uint16 ADC_lvl = 2048;
    while (adcResult < ADC_lvl)
    {
        if (n==0)
        {
            UART_PutString("- Mesure en cours - \n\r");
            n++;
            CyGlobalIntDisable;
            t_10us=0;
            CyGlobalIntEnable;
        }
        ADC_SAR_IsEndConversion(ADC_SAR_RETURN_STATUS);
        adcResult=ADC_SAR_GetResult16();
        CyGlobalIntDisable;
        DAC_SetValue(0x00);
        DAC_Stop();
        while (adcResult > 256)
        {
            float Q = 200*8;
            uint32 temps = t_10us/100;
            float voltage = ADC_lvl/2.0;
            double capacitance_nf= 1000*8*((Q*temps)/voltage);
            uint32 Cap_nF = capacitance_nf;
            sprintf(capacitance,"%lu",Cap_nF);
            UART_PutString(capacitance);
            UART_PutString("\n nF \n\r");
            ADC_SAR_IsEndConversion(ADC_SAR_RETURN_STATUS);
            adcResult=ADC_SAR_GetResult16();
        }
        if (UART_GetChar()!='2')
        {
            UART_initialisation();
        }
    }
   
    
}

//////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// MAIN LOOP /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    char8 input;
    CyGlobalIntEnable; /* Enable global interrupts. */
    FreeRTOS_Start();
    UART_Start();
    DAC_Start();
    ADC_SAR_Start();
   
    
    
//    xTaskCreate(...);
    
    vTaskStartScheduler();
    for(;;) 
    {
        UART_initialisation();
        input=UART_GetChar(); // Permet de savoir le mode choisi
        if (input=='2')
        {
            mode_Capacimetre();
        }
        else
        {
            UART_PutString("-No mode selected-\n\r");
        }
        CyDelay(3000);
    }
}
///////////////////=========== main loop Ends Here ===============/////////////////////////

/* [] END OF FILE */
