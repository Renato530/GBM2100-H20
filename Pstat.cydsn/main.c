/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>


int main(void)
{
    int32 adcResult;
    float adcVolt;
    float adcAmp;
    float R_2;
    char result_Amp[20];
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    FreeRTOS_Start();
    UART_Start();
    ADC_Start();
    UART_PutString("- Mode Amperemetre -\n\r");
    ADC_StartConvert();
    
    vTaskStartScheduler();
    for(;;) 
    {
        ADC_IsEndConversion(ADC_RETURN_STATUS);
        adcResult=ADC_GetResult32();
        adcVolt=ADC_CountsTo_mVolts(adcResult);
        adcAmp = adcVolt/R_2;
        sprintf(result_Amp,"%+1.3f A",adcAmp);
        UART_PutString(result_Amp);
        CyDelay(1000);
    }
}

/* [] END OF FILE */
