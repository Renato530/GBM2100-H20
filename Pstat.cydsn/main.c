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
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

volatile uint32_t t_10us=0;


///////////////////////////// FUNCTIONS BODY /////////////////////////////

CY_ISR(Timing_ISR_Handler)
{
    Timer_ReadStatusRegister();
    t_10us++;
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
    UART_PutString("||  3 - Mode Capacimetre ||\n \r");
    UART_PutString("=========================== \n \r");
    UART_PutString("- Veuillez choisir un mode - \n \r");
    UART_PutString("=========================== \n \r");
    CyDelay(300);
}


void mode_Capacimetre()
{
    uint32_t DAC_valeur = 0xff;
    char capacitance[10];
    DAC_Stop();
    int32 adc_conversion=0;
    
    if (ADC_SAR_IsEndConversion(ADC_SAR_RETURN_STATUS)!=0)
    {
        adc_conversion = ADC_SAR_GetResult16();
    }
    DAC_Start();
    DAC_valeur = 0x64; // injection d'un courant de 0.8 mA
    DAC_SetValue(DAC_valeur);
   
    int32 adc_max = 2048;
    while (adc_conversion < adc_max)
    {
        if (ADC_SAR_IsEndConversion(ADC_SAR_RETURN_STATUS)!=0)
        {
            adc_conversion=ADC_SAR_GetResult16();
        }
    }
        
    CyGlobalIntDisable;
    DAC_SetValue(0x00);
    DAC_Stop();
    while (adc_conversion > 256)
    {
        float charge = DAC_valeur*8;
        uint32 temps = t_10us/100;
        float voltage = adc_max/2;
        float capacitance_nf= 1000*8*((charge*temps)/voltage);
        sprintf(capacitance,"%.2f",capacitance_nf);
        UART_PutString("-> Capacitance : "); 
        UART_PutString(capacitance);
        UART_PutString("nF \n\r");
        if(ADC_SAR_IsEndConversion(ADC_SAR_RETURN_STATUS)!=0)
        {
            adc_conversion=ADC_SAR_GetResult16();
    
        }
    }
}

//////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// MAIN LOOP /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    FreeRTOS_Start();
    ADC_SAR_Start();
    ADC_SAR_StartConvert();
    DAC_Start();
    Timer_Start();
    Timing_ISR_StartEx(Timing_ISR_Handler);
    
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
                    //mode_Voltmetre();
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
            case '3':
                UART_PutString("- Mode Capacimetre (Appuyez sur ENTER pour quitter) - \n\r ");
                CyDelay(500);
                inputTemp = 0;
                while(inputTemp == 0)
                {
                    mode_Capacimetre();
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
}
///////////////////=========== main loop Ends Here ===============/////////////////////////

/* [] END OF FILE */
