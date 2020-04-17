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

// TODO: Integrer l'Ohmetre
// TODO: Integrer l'Amperemetre
// TODO: Tester le Volmetre
// TODO: Tester l'Ohmetre
// TODO: Tester l'Amperemetre

#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"

// TaskHandle_t mTache1 = NULL; // Variable pour l'utilisation du FreeRTOS


///////////////////////////// FUNCTIONS BODY /////////////////////////////

////////////////////////
// Cette fonction permet d'initialiser le UART et selectioner un mode du multimetre
////////////////////////
void UART_initialisation() 
{
    UART_Start();
    UART_PutString("- Bienvenue au multimetre de l'equipe 1e - \n\r ");
    CyDelay(2000);
    UART_PutString("- Veuillez choisir un mode - \n \r");
    CyDelay(4000);
   
}

////////////////////////
// Cette fonction permet l'utilisation du voltmetre 
////////////////////////

//TODO: Integrer FreeRTOS
//TODO: Envoyer les donnes via MATLAB (affichage tableau, graphique...)
void mode_Voltmetre() 
{
    UART_PutString("- Mode Voltmetre - \n\r ");
    // Declaration des variables
    float dac_bin=0; // x étant le résultat obtenu de la composante ADC et leur assignée une valeur initial nulle
    float dac_volt=0; // y étant la conversion de x en millivolts
    char result_volts[15]={'\0'}; //louer un espace pour le string de l'affichage via Putty
    
    ADC_SAR_IsEndConversion(ADC_SAR_WAIT_FOR_RESULT); // Vérification de la conversion
    
    dac_bin=ADC_SAR_GetResult16(0); // Retourne la conversion à x pour le channel '0'
    
    dac_volt=ADC_SAR_CountsTo_mVolts(dac_bin); //conversion du résultats de l'ADC origninallement en bit en mvolts
         
    if (dac_volt <=0) // Condition pour retourner un potentiel positif via notre multimètre
    {
        dac_volt=0;
    }
    
    UART_PutString("- Voltage - \n\r"); 
    sprintf(result_volts,"%.2f",dac_volt); //affichage de résultat en mvolts via UART et Putty
    UART_PutString (" mV\n\r");
    
} // Ceci est une tache qui correspond au mode Voltmetre de notre multimetre (utile pour l'implementation de plusieurs outils dans le multimetre)
//////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// MAIN LOOP /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    
    char8 input;
    // CyGlobalIntEnable; aucune interruption
    FreeRTOS_Start();
    ADC_SAR_Start();
    //LCD_Start();
   
    // Fonctions ecran LED
    //LCD_Position(0,0);
    //LCD_PrintString("Voltmetre");
    //LCD_ClearDisplay();
    
    ADC_SAR_StartConvert();
    //xTaskCreate(UART_initialisation,"InUART",200,(void*)0, tskIDLE_PRIORITY,&mTache1); // Creation d'un task pour le FreeRTOS
    
    
    
    for(;;) 
    {
        UART_initialisation();
        input=UART_GetChar(); // Permet de savoir le mode choisi
        if (input=='0')
        {
            mode_Voltmetre();
        }
        else
        {
            UART_PutString("-No mode selected-\n\r");
        }
        CyDelay(3000);
    }
} ///////////////////=========== main loop Ends Here ===============/////////////////////////

/* [] END OF FILE */
