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
#include <stdlib.h>
#include <math.h>

//////////////////////////// VARIABLES ///////////////////////////////////

int ready=0; 
int close = 1;

//////////////////////////////////////////////////////////////////////////

///////////////////////////// FUNCTIONS BODY /////////////////////////////

////////////////////////
// Cette fonction permet d'initialiser le UART et selectioner un mode du multimetre
////////////////////////

CY_ISR(Interruption_Rx)
{
    char verify;
    verify = UART_GetChar();
    if (verify =='1')
    {
        ready =1;
        close=0;
        LED_Write(1);
    }
    else if (verify=='c')
    {
        ready=0;
        close=1;
        LED_Write(0);
    }
}

void UART_initialisation() 
{
    UART_Start();
    // Affichage du MENU
    UART_PutString(" \n \r");
    UART_PutString("=========================== \n \r");
    UART_PutString("======= MULTIMETRE ======== \n \r");
    UART_PutString("=========================== \n \r");
    UART_PutString("||  0 - Mode Voltmetre   ||\n \r");
    UART_PutString("||  1 - Mode Amperemetre ||\n \r");
    UART_PutString("||  2 - Mode Ohmmetre    ||\n \r");
    UART_PutString("=========================== \n \r");
    UART_PutString("- Veuillez choisir un mode - \n \r");
    UART_PutString("=========================== \n \r");
    CyDelay(300);
}

////////////////////////
// Cette fonction permet l'utilisation du voltmetre 
////////////////////////

//TODO: Integrer FreeRTOS
//TODO: Envoyer les donnes via MATLAB (affichage tableau, graphique...)
void mode_Voltmetre() 
{
    //UART_PutString("- Mode Voltmetre (Appuyez sur nimporte quelle touche pour quitter) - \n\r ");
    // Declaration des variables
    int32 dac_bin=0; // x étant le résultat obtenu de la composante ADC et leur assignée une valeur initial nulle
    float32 dac_volt=0; // y étant la conversion de x en millivolts
    char result_volts[15]={'\0'}; //louer un espace pour le string de l'affichage via Putty
    
    if (ADC_SAR_IsEndConversion(ADC_SAR_WAIT_FOR_RESULT) !=0) // Verficiation de la conversion
    {
        dac_bin=ADC_SAR_GetResult16(0); // Retourne la conversion à x pour le channel '0'
    
        dac_volt=ADC_SAR_CountsTo_mVolts(dac_bin); //conversion du résultats de l'ADC origninallement en bit en mvolts
         
        if (dac_volt <=0) // Condition pour retourner un potentiel positif via notre multimètre
        {
            dac_volt=0;
        }
        dac_bin=ADC_SAR_GetResult16(0); // Retourne la conversion à x pour le channel '0' 
        dac_volt=ADC_SAR_CountsTo_mVolts(dac_bin); //conversion du résultats de l'ADC origninallement en bit en mvolts
        UART_PutString("-> Voltage : "); 
        sprintf(result_volts,"%.2f",dac_volt); //affichage de résultat en mvolts via UART et Putty
        if ((ready==1)&&(close==0))
        {
            UART_ClearTxBuffer();
            UART_PutString(result_volts);
            //UART_PutString (" mV\n\r");
            
            CyDelay(20);
            UART_ClearTxBuffer();
        }
        else if ((ready==0) && (close==1))
        {
            UART_ClearTxBuffer();
        }
        
    }
} // Ceci est une tache qui correspond au mode Voltmetre de notre multimetre (utile pour l'implementation de plusieurs outils dans le multimetre)
//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// MAIN LOOP /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    
    FreeRTOS_Start();
    ADC_SAR_Start();
    //LCD_Start();
    CyGlobalIntEnable;
    intRx_StartEx(Interruption_Rx);
   
    // Fonctions ecran LED
    // LCD_Position(0,0);
    // LCD_PrintString("Voltmetre");
    // LCD_ClearDisplay();
    
    ADC_SAR_StartConvert();
    //xTaskCreate(UART_initialisation,"InUART",200,(void*)0, tskIDLE_PRIORITY,&mTache1); // Creation d'un task pour le FreeRTOS
    
    int frequence_echatillonage = 10; // Hz
    int periode_echatillonage=1000/frequence_echatillonage; // mS
    char input;
    
    // Affichage du message d'accueil
    UART_Start();
    UART_PutString("************* Bienvenue au multimetre de l'equipe 1e *************\n\r ");
    UART_PutString("******************************************************************\n\r ");
    CyDelay(2000);
    
    for(;;) 
    {
        UART_initialisation();
        input='\0';
        
        while (!input){
             input=UART_GetChar(); // Permet de savoir le mode choisi
        }
        
        char8 inputTemp;
        switch (input)
        {
            case '0':
                UART_PutString("- Mode Voltmetre (Appuyez sur ENTER pour quitter) - \n \r ");
                CyDelay(500);
                // On reste dans le mode Voltmètre tant qu'on appuie pas sur une touche sur le clavier
                inputTemp = 0;
                while(inputTemp == 0)
                {
                    mode_Voltmetre();
                    CyDelay(periode_echatillonage);
                    inputTemp=UART_GetChar();
                    if (!inputTemp)
                    {
                        inputTemp=0;
                    }
                }
                break;
                
            case '1':
                UART_PutString("- Mode Amperemetre (Appuyez sur ENTER pour quitter) - \n\r ");
                CyDelay(500);
                inputTemp = 0;
                while(inputTemp == 0)
                {
                    //mode_Amperemetre();
                    CyDelay(periode_echatillonage);
                    inputTemp=UART_GetChar();
                    if (!inputTemp)
                    {
                        inputTemp=0;
                    }
                }
                break;

            case '2':
                UART_PutString("- Mode Ohmmetre (Appuyez sur ENTER pour quitter) - \n\r ");
                CyDelay(500);
                inputTemp = 0;
                while(inputTemp == 0)
                {
                    //mode_Ohmmetre();
                    CyDelay(periode_echatillonage);
                    inputTemp=UART_GetChar();
                    if (!inputTemp)
                    {
                        inputTemp=0;
                    }
                }
                break;    
            default:
                UART_PutString("- Error: No mode selected -\n\r");
        }

        CyDelay(1000);
    }
} ///////////////////=========== main loop Ends Here ===============/////////////////////////

/* [] END OF FILE */
