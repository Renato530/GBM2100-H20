/* ========================================
 *
 * Copyright ÉQUIPE 1E, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF TEAM 1E.
 * Renato Castillo 1962797 
 * Karl-Philippe Beaudet 1958657
 * Richema Métellus XXXXXXX
 * Tasnim Ahmed XXXXXXX
 * ========================================
*/
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    FreeRTOS_Start();
    DAC_Start();
    SAR_ADC_Start();
    SAR_ADC_StartConvert();
    UART_Start();
    
    
//    xTaskCreate(...);
    
    vTaskStartScheduler();
    for(;;) {}
}

/* [] END OF FILE */
