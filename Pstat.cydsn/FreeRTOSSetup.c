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


extern cyisraddress CyRamVectors[];
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void vPortSVCHandler(void);

void FreeRTOS_Start(void);
static void panic();


/* You can use a breakpoint here to debug for StackOverflow */
void vApplicationStackOverflowHook(
    __attribute__((unused)) TaskHandle_t *pxTask, 
    __attribute__((unused)) signed char *pcTaskName ) 
{
    panic();
}

/* You can use a breakpoint here to debug for Heap problems */
void vApplicationMallocFailedHook (void)  
{
    panic();
}


/* Make sure you can detect critical situations */
static void panic() {
    taskDISABLE_INTERRUPTS();
    for (;;) {
        LED_Write(~LED_Read());
        CyDelay(100);
    }
}


void FreeRTOS_Start(void)
{
    /* Install the OS Interrupt Handlers. */
    CyRamVectors[11] = (cyisraddress) vPortSVCHandler;
    CyRamVectors[14] = (cyisraddress) xPortPendSVHandler;
    CyRamVectors[15] = (cyisraddress) xPortSysTickHandler;
}




/* [] END OF FILE */
