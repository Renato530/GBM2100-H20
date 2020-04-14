/* ========================================
 *
 * Copyright GBM2100 Équipe 1e, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Équipe 1e.
 * Renato Castillo 1962797
 * Karl-Philippe Beaudet 1958657
 * Richema Métallus xxxxxxx
 * Tasnim Ahmed xxxxxxx
 * ========================================
*/

#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"

float x=0; // x étant le résultat obtenu de la composante ADC et leur assignée une valeur initial nulle
float y=0; // y étant la conversion de x en millivolts
char result[15]={'\0'}; //louer un espace pour le string de l'affichage via Putty

int main(void)
{
    // CyGlobalIntEnable; aucune interruption
    FreeRTOS_Start();
    UART_Start();
    ADC_SAR_Start();
    
    // xTaskCreate(...);
    vTaskStartScheduler();
    ADC_SAR_StartConvert();
    
    for(;;) 
    {
        ADC_SAR_IsEndConversion(ADC_SAR_WAIT_FOR_RESULT);
        x=ADC_SAR_GetResult16(0); // Retourne la conversion à x pour le channel '0'
        y=ADC_SAR_CountsTo_mVolts(x); //conversion du résultats de l'ADC origninallement en bit en mvolts 
        UART_PutString("Voltage \n"); 
        sprintf(result,"%.2f",y); //affichage de résultat en mvolts via UART et Putty
    }
}

/* [] END OF FILE */
