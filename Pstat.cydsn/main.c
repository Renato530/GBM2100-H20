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

///////////////////////////// FUNCTIONS BODY /////////////////////////////
void UART_initialisation() 
{
    UART_Start();
    UART_PutString("- Bienvenue au multimetre de l'equipe 1e - \n\r ");
    CyDelay(2000);
    UART_PutString("- Veuillez choisir un mode - \n \r");
    CyDelay(4000);
   
}

void mode_Amp () // Configuration de l'amperemetre
{
    UART_PutString("- Mode Amperemetre -\n\r");
    int32 adcResult;
    float adcVolt;
    float adcAmp;
    float R_2;
    char result_Amp[20];
    ADC_IsEndConversion(ADC_RETURN_STATUS);
    adcResult=ADC_GetResult32();
    adcVolt=ADC_CountsTo_mVolts(adcResult);
    adcAmp = adcVolt/R_2;
    sprintf(result_Amp,"%+1.3f A",adcAmp);
    UART_PutString(result_Amp);
}

//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// MAIN LOOP /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    FreeRTOS_Start();
    ADC_Start();
    ADC_StartConvert();
<<<<<<< HEAD
    char8 input;
    
//    xTaskCreate(...);
=======
>>>>>>> 22cdea4bf6039fb3f0446c18485d7f3278cc903a
    
    vTaskStartScheduler();
    for(;;) 
    {
       UART_initialisation();
       input=UART_GetChar(); // Permet de savoir le mode choisi
       if (input=='1')
        {
            mode_Amp();
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
