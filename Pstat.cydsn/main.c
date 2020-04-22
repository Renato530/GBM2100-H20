/* ========================================
 *
 * Copyright ÉQUIPE '1E', 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF TEAM '1E'.
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

// TODO : S'assurer de l'affichage d'une resistance sur Putty
// TODO : Integrer cette composante du multimetre au Voltmetre par une interface
// TODO : Remplacer les chiffre (valeurs qui sortent de nulpart) par des variables explicatives

// Pour l'instant essayer de tester avec des resistances du FreeSoC

///////////////////////////// FUNCTIONS BODY /////////////////////////////

////////////////////////
// Cette fonction permet d'initialiser le UART et selectioner un mode du multimetre
////////////////////////
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

void mode_Ohmetre()
{
    // Déclaration des variables
    int courant = 0;
    int resistance = 0;
    int voltage = 0;
    char val_resistance[10];
    unsigned int DAC_valeur = 0xff;
    int v_input=4095;
    
    // Initialisation des composantes
    DAC_Start();
    SAR_ADC_Start();
    DAC_valeur= 0xff;
    DAC_SetValue(DAC_valeur);
    SAR_ADC_StartConvert();
    
    
    while ((DAC_valeur > 0) && (v_input >=4000))
    {
        DAC_valeur=DAC_valeur - 0x01;
        DAC_SetValue(DAC_valeur);
        CyDelay(3);
        if (SAR_ADC_IsEndConversion(SAR_ADC_WAIT_FOR_RESULT)!=0)
        {
            v_input= SAR_ADC_GetResult16();
        }
        CyDelay(2);

    }
    if (v_input < 4000)
    {
        DAC_SetValue(DAC_valeur);
        CyDelay(1);
        courant = DAC_valeur*8;
        voltage=v_input*1000/2;
        resistance= voltage/courant; 
        resistance -=464;
        //resistance=(resistance-927)/0.875;
        if (resistance <= 0) 
        {
            resistance = 0;
        }
        if (resistance > 500000) {resistance *=1.05;}
        if(resistance < 500000)
        {
            UART_PutString("-> Resistance : "); 
            sprintf(val_resistance,"%d",resistance);
            UART_PutString(val_resistance);
            UART_PutString (" Ohms\n\r");
            CyDelay(100);
        }
        else
        {
            UART_PutString (" ==========\n\r");
            UART_PutString (" Aucune resistance presente\n\r");
            CyDelay(100);
        }
        CyDelay(100);
        
    }
    
      
    
}

//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// MAIN LOOP /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


int main(void)
{
    // Variables générales
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    char8 input; 
    FreeRTOS_Start();
    SAR_ADC_Start();
    //LCD_Start();
   
    // Fonctions ecran LED
    // LCD_Position(0,0);
    // LCD_PrintString("Voltmetre");
    // LCD_ClearDisplay();
    
    SAR_ADC_StartConvert();
    //xTaskCreate(UART_initialisation,"InUART",200,(void*)0, tskIDLE_PRIORITY,&mTache1); // Creation d'un task pour le FreeRTOS
    
    // Affichage du message d'accueil
    UART_Start();
    UART_PutString("******************** Bienvenue au multimetre de l'equipe 1e *******************\n\r ");
     UART_PutString("******************************************************************************\n\r ");
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
                // On reste dans le mode Voltmètre tant qu'on appuie pas sur une touche sur le clavier
                inputTemp = 0;
                while(inputTemp == 0)
                {
                    //mode_Voltmetre();
                    CyDelay(100);
                    inputTemp=UART_GetChar();
                    if (!inputTemp)
                    {
                        inputTemp=0;
                    }
                }
                break;
                
            case '1':
                UART_PutString("- Mode Amperemetre (Appuyez sur ENTER pour quitter) - \n \r ");
                inputTemp = 0;
                while(inputTemp == 0)
                {
                    //mode_Amperemetre();
                    CyDelay(500);
                    inputTemp=UART_GetChar();
                    if (!inputTemp)
                    {
                        inputTemp=0;
                    }
                }
                break;

            case '2':
                UART_PutString("- Mode Ohmmetre (Appuyez sur ENTER pour quitter) - \n \r ");
                inputTemp = 0;
                while(inputTemp == 0)
                {
                    mode_Ohmetre();
                    CyDelay(100);
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
