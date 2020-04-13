/* ========================================
 *
 * Copyright GBM2100 Équipe 1e, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Équipe 1e.
 * Renato Castillo 1962797
 * Karl-Philippe Beaudet xxxxxxx
 * Richema Métallus xxxxxxx
 * Tasnim Ahmed xxxxxxx
 * ========================================
*/
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"

float x,y=0;
char result[15]={'\0'};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    FreeRTOS_Start();
    ADC_SAR_Start();
    UART_Start();
    
    
//    xTaskCreate(...);
    
    vTaskStartScheduler();
    for(;;) 
    {
        ADC_SAR_StartConvert();
        ADC_SAR_IsEndConversion(ADC_SAR_WAIT_FOR_RESULT);
        x=ADC_SAR_GetResult16(0);
        float32 y=ADC_SAR_CountsTo_mVolts(x);
        UART_PutString("Voltage \n");
        sprintf(result,"%.2f",y);
        
         
        
    }
}

/* [] END OF FILE */
