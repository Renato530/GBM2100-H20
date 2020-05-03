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
 * Richema Métellus         1953911
 * Tasnim Ahmed             1958545
 * ========================================
*/


#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"

// Variable options permettent de définir les unitées des fonctions du multimetre
volatile int optionVoltmetre=0; // Volts
volatile int optionAmperemetre=1; // miliAmperes
volatile int optionOhmmetre=0; // Ohms
volatile int frequence_echatillonage=10; //Hz
volatile int periode_echatillonage;

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
    UART_PutString("||  1 - Mode Voltmetre   ||\n \r");
    UART_PutString("||  2 - Mode Amperemetre ||\n \r");
    UART_PutString("||  3 - Mode Ohmmetre    ||\n \r");
    UART_PutString("||  4 - Mode Capacimetre ||\n \r");
    UART_PutString("||  5 - Parametres       ||\n \r");
    UART_PutString("=========================== \n \r");
    UART_PutString("- Veuillez choisir un mode - \n \r");
    UART_PutString("=========================== \n \r");
    CyDelay(300);
}

void MenuOptionVoltmetre()
{
    UART_PutString(" \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("============= Unite voltage ============= \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("||  1 - Volts (V)                      || \n \r");
    UART_PutString("||  2 - Milivolts (mV)                 || \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("- Veuillez choisir une options - \n \r");
    UART_PutString("========================================= \n \r");
    char input='\0';
        
    while (!input){
        input=UART_GetChar(); // Permet de savoir le mode choisi
    }
    
    switch(input)
    {
        case '1':
            optionVoltmetre=0;
            UART_PutString(" Unitees selectionnees: V \n \r");
            break;
        
        case '2':
            optionVoltmetre=1;
            UART_PutString(" Unitees selectionnees: mV \n \r");
            break;
        
        default:
            UART_PutString(" - Erreur - \n \r");
            break;
    }
}

void MenuOptionAmperemetre()
{
    UART_PutString(" \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("============= Unite courant ============= \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("||  1 - Amperes (A)                    || \n \r");
    UART_PutString("||  2 - Miliamperes (mA)               || \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("- Veuillez choisir une options - \n \r");
    UART_PutString("========================================= \n \r");
    char input='\0';
        
    while (!input){
        input=UART_GetChar(); // Permet de savoir le mode choisi
    }
    
    switch(input)
    {
        case '1':
            optionAmperemetre=0;
            UART_PutString(" Unitees selectionnees: A \n \r");
            break;
        
        case '2':
            optionAmperemetre=1;
            UART_PutString(" Unitees selectionnees: mA \n \r");
            break;
        
        default:
            UART_PutString(" - Erreur - \n \r");
            break;
    }
}

void MenuOptionOhmmetre()
{
    UART_PutString(" \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("============ Unite resistance =========== \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("||  1 - Ohms                           || \n \r");
    UART_PutString("||  2 - KiloOhms                       || \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("- Veuillez choisir une options - \n \r");
    UART_PutString("========================================= \n \r");
    char input='\0';
        
    while (!input){
        input=UART_GetChar(); // Permet de savoir le mode choisi
    }
    
    switch(input)
    {
        case '1':
            optionOhmmetre=0;
            UART_PutString(" Unitees selectionnees: Ohms \n \r");
            break;
        
        case '2':
            optionOhmmetre=1;
            UART_PutString(" Unitees selectionnees: kOhms \n \r");
            break;
        
        default:
            UART_PutString(" - Erreur - \n \r");
            break;
    }
}

void MenuFrequenceEchatillonage()
{
    UART_PutString(" \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("========= Frequence Echatillonage ======= \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("||  1 - 1  Hz (1/sec)                  || \n \r");
    UART_PutString("||  2 - 2  Hz (2/sec)                  || \n \r");
    UART_PutString("||  3 - 5  Hz (5/sec)                  || \n \r");
    UART_PutString("||  4 - 10 Hz (10/sec)                 || \n \r");
    UART_PutString("||  5 - 20 Hz (20/sec)                 || \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("- Veuillez choisir une options - \n \r");
    UART_PutString("========================================= \n \r");
    char input='\0';
        
    while (!input){
        input=UART_GetChar(); // Permet de savoir le mode choisi
    }
    
    switch(input)
    {
        case '1':
            frequence_echatillonage=1;
            UART_PutString(" Frequence d'echatillonage selectionnee: 1 Hz \n \r");
            break;
        
        case '2':
            frequence_echatillonage=2;
            UART_PutString(" Frequence d'echatillonage selectionnee: 2 Hz \n \r");
            break;
        
        case '3':
            frequence_echatillonage=5;
            UART_PutString(" Frequence d'echatillonage selectionnee: 5 Hz \n \r");
            break;
        
        case '4':
            frequence_echatillonage=10;
            UART_PutString(" Frequence d'echatillonage selectionnee: 10 Hz \n \r");
            break;
        
        case '5':
            frequence_echatillonage=20;
            UART_PutString(" Frequence d'echatillonage selectionnee: 20 Hz \n \r");
            break;
        
        default:
            UART_PutString(" - Erreur - \n \r");
            break;
    }
}

void MenuParametres(){
    UART_PutString(" \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("============== Parametres =============== \n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("||  1 - Frequence d'echatillonage     ||\n \r");
    UART_PutString("||  2 - Unitees Voltage               ||\n \r");
    UART_PutString("||  3 - Unitees Courant               ||\n \r");
    UART_PutString("||  4 - Unitees Resistance            ||\n \r");
    UART_PutString("||  5 - Quitter le menu de parametres ||\n \r");
    UART_PutString("========================================= \n \r");
    UART_PutString("- Veuillez choisir une options - \n \r");
    UART_PutString("========================================= \n \r");
                
    char input='\0';
        
    while (!input){
        input=UART_GetChar(); // Permet de savoir le mode choisi
    }
     
    switch(input)
    {
        case '1':
            MenuFrequenceEchatillonage();
            UART_PutString("- Menu frequence echantillonage quitte -\n\r");
            break;
        
        case '2':
            MenuOptionVoltmetre();
            UART_PutString("- Menu voltmetre quitte -\n\r");
            break;
                    
        case '3':
            MenuOptionAmperemetre();
            UART_PutString("- Menu amperemetre quitte -\n\r");
            break;
                    
        case '4':
            MenuOptionOhmmetre();
            UART_PutString("- Menu ohmmetre quitte -\n\r");
            break;
                    
        default:
            UART_PutString("- Menu parametres quitte -\n\r");
        }   
}

////////////////////////
// Cette fonction permet l'utilisation du voltmetre 
////////////////////////
void mode_Voltmetre() 
{
    AMux_FastSelect(0);
    
    // Declaration des variables
    int adc_bin=0; // x étant le résultat obtenu de la composante ADC et leur assignée une valeur initial nulle
    float adc_volt=0; // y étant la conversion de x en millivolts
    char result_volts[15]={'\0'}; //louer un espace pour le string de l'affichage via Putty
    
    if (ADC_SAR_IsEndConversion(ADC_SAR_WAIT_FOR_RESULT) !=0) // Verficiation de la conversion
    {
        adc_bin=ADC_SAR_GetResult16(); // Retourne la conversion à x pour le channel '0'
        adc_volt=ADC_SAR_CountsTo_Volts(adc_bin); //conversion du résultats de l'ADC origninallement en bit en volts
        if (adc_volt <=0) // Condition pour retourner un potentiel positif via notre multimètre
        {
            adc_volt=0;
        }
        
        
        if (optionVoltmetre==0)
        {
            UART_PutString("|| Voltage || ");
            sprintf(result_volts,"%.3f",adc_volt); //affichage de résultat en Volts via UART et Putty
            UART_PutString(result_volts);
            UART_PutString (" V ||\n\r");
        }
        
        else{
            adc_volt=adc_volt*1000;
            UART_PutString("|| Voltage || ");
            sprintf(result_volts,"%.0f",adc_volt); //affichage de résultat en mVolts via UART et Putty
            UART_PutString(result_volts);
            UART_PutString (" mV ||\n\r");
        }
    }
} 

////////////////////////
// Cette fonction permet l'utilisation du ohmetre 
////////////////////////
void mode_Ohmetre()
{
    AMux_FastSelect(1);
    
    // Déclaration des variables
    int courant = 0; //
    float resistance = 0; //
    int voltage = 0; //
    char val_resistance[10]; // 
    unsigned int DAC_valeur = 0xff; //
    int v_input=4095; //
    
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
            if (optionOhmmetre==0)
            {
                UART_PutString("|| Resistance || "); 
                sprintf(val_resistance,"%f",resistance); // affichage du résultat en Ohms via UART et Putty
                UART_PutString(val_resistance);
                UART_PutString (" Ohms||\n\r"); 
            }

            else{
                resistance=resistance/1000;
                UART_PutString("|| Resistance || "); 
                sprintf(val_resistance,"%f",resistance); // affichage du résultat kOhms via UART et Putty
                UART_PutString(val_resistance);
                UART_PutString (" kOhms||\n\r"); 
            }
            
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

void mode_Amperemetre () 
{
    ADC_Start(); // initialisation de la composante ADC
    int32 adcResult; 
    float adcVolt;
    float adcAmp;
    int R_2=100; // resistance de reference en Ohms
    char result_Amp[20]; // louer un espace pour le string de l'affichage via Putty
    ADC_StartConvert(); // intitialisation de la composante de conversion du ADC
    
    if (ADC_IsEndConversion(ADC_RETURN_STATUS)!=0) // Vérification de la conversion
    {
        adcResult=ADC_GetResult32(); // retourne le résultat converti en 32-bit
        adcVolt=ADC_CountsTo_Volts(adcResult); // adcVolt prend ce résultat de l'ADC (adcResult) originallement en bits et le converti en Volts 
        adcAmp = adcVolt/R_2; // en A  (loi d'Ohm)
        if (optionAmperemetre==0)
        {
            UART_PutString("|| Courant || ");
            sprintf(result_Amp,"%.3f",adcAmp); // afiichage du résultat en A via UART et Putty
            UART_PutString(result_Amp);
            UART_PutString (" A||\n\r"); 
        }

        else{
            adcAmp=adcAmp*1000;
            UART_PutString("|| Courant || ");
            sprintf(result_Amp,"%.0f",adcAmp); // affichage du résultat en mA via UART et Putty
            UART_PutString(result_Amp);
            UART_PutString (" mA||\n\r"); 
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
    AMux_Start();
    ADC_SAR_Start();
    ADC_SAR_StartConvert();
    
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
            case '1':
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
                
            case '2':
                UART_PutString("- Mode Amperemetre (Appuyez sur ENTER pour quitter) - \n\r ");
                CyDelay(500);
                inputTemp = 0;
                while(inputTemp == 0)
                {
                    mode_Amperemetre();
                    CyDelay(periode_echatillonage);
                    inputTemp=UART_GetChar();
                    if (!inputTemp)
                    {
                        inputTemp=0;
                    }
                }
                break;

            case '3':
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
                
            case '4':
                UART_PutString("- Mode Capacimetre (Appuyez sur ENTER pour quitter) - \n\r ");
                CyDelay(500);
                inputTemp = 0;
                while(inputTemp == 0)
                {
                    //mode_Capacimetre();
                    CyDelay(periode_echatillonage);
                    inputTemp=UART_GetChar();
                    if (!inputTemp)
                    {
                        inputTemp=0;
                    }
                }
                break;
                
            case '5':
                MenuParametres();
                break;
            
                
            default:
                UART_PutString("- Error: No mode selected -\n\r");
        }
        periode_echatillonage=1000/frequence_echatillonage; // mS
        CyDelay(1000);
    }
} ///////////////////=========== main loop Ends Here ===============/////////////////////////

/* [] END OF FILE */

