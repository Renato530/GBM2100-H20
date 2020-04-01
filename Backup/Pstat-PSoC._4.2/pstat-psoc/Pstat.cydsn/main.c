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


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    FreeRTOS_Start();
    
//    xTaskCreate(...);
    
    vTaskStartScheduler();
    for(;;) {}
}

/* [] END OF FILE */
