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
// TODO: Tester l'Amperemetre

#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"




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

//TODO: Integrer FreeRTOS
//TODO: Envoyer les donnes via MATLAB (affichage tableau, graphique...)
void mode_Voltmetre() 
{
    AMux_FastSelect(0);
    //UART_PutString("- Mode Voltmetre (Appuyez sur nimporte quelle touche pour quitter) - \n\r ");
    // Declaration des variables
    float dac_bin=0; // x étant le résultat obtenu de la composante ADC et leur assignée une valeur initial nulle
    float dac_volt=0; // y étant la conversion de x en millivolts
    char result_volts[15]={'\0'}; //louer un espace pour le string de l'affichage via Putty
    
    if (ADC_SAR_IsEndConversion(ADC_SAR_WAIT_FOR_RESULT) !=0) // Verficiation de la conversion
    {
        dac_bin=ADC_SAR_GetResult16(); // Retourne la conversion à x pour le channel '0'
    
        dac_volt=ADC_SAR_CountsTo_mVolts(dac_bin); //conversion du résultats de l'ADC origninallement en bit en mvolts
        
        if (dac_volt <=0) // Condition pour retourner un potentiel positif via notre multimètre
        {
            dac_volt=0;
        }
        dac_bin=ADC_SAR_GetResult16(); // Retourne la conversion à x pour le channel '0' 
        dac_volt=ADC_SAR_CountsTo_mVolts(dac_bin); //conversion du résultats de l'ADC origninallement en bit en mvolts
        dac_volt=dac_volt/1000; // Conversion des mVolts en volts
        UART_PutString("-> Voltage : "); 
        sprintf(result_volts,"%.3f",dac_volt); //affichage de résultat en mvolts via UART et Putty
        UART_PutString(result_volts);
        UART_PutString (" V\n\r");
    }
} // Ceci est une tache qui correspond au mode Voltmetre de notre multimetre (utile pour l'implementation de plusieurs outils dans le multimetre)

////////////////////////
// Cette fonction permet l'utilisation du ohmetre 
////////////////////////

void mode_Ohmetre()
{
    AMux_FastSelect(1);
    // Déclaration des variables
    int courant = 0;
    float resistance = 0;
    int voltage = 0;
    char val_resistance[10];
    unsigned int DAC_valeur = 0xff;
    int v_input=4095;
    
    // Initialisation des composantes
    DAC_Start();
    ADC_SAR_Start();
    DAC_valeur= 0xff;
    DAC_SetValue(DAC_valeur);
    ADC_SAR_StartConvert();
    
    
    while ((DAC_valeur > 0) && (v_input >=4000))
    {
        DAC_valeur=DAC_valeur - 0x01;
        DAC_SetValue(DAC_valeur);
        CyDelay(3);
        if (ADC_SAR_IsEndConversion(ADC_SAR_WAIT_FOR_RESULT)!=0)
        {
            v_input= ADC_SAR_GetResult16();
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
        resistance -=470;
        if (resistance <= 0) 
        {
            resistance = 0;
        }
        
        else if (resistance > 10000) {resistance *=1.1;}
        if(resistance < 250000)
        {
            UART_PutString("|| Resistance || "); 
            sprintf(val_resistance,"%f",resistance);
            UART_PutString(val_resistance);
            UART_PutString (" Ohms||\n\r");
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

////////////////////////
// Cette fonction permet l'utilisation de l'amperemetre 
////////////////////////

//////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// MAIN LOOP /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    
    FreeRTOS_Start();
    AMux_Start();
    ADC_SAR_Start();
    ADC_SAR_StartConvert();
    
    
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
                    mode_Ohmetre();
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

