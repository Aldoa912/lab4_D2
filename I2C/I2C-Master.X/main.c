/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de uso de I2C Master
 * Created on 17 de febrero de 2020, 10:32 AM
 */
//*****************************************************************************
// Palabra de configuración
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include <xc.h>
#include "ADC.h"
#include "LCD.h"
//#include "DS3232.h"

//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000

//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
uint8_t ADC;
char centenas;
char decenas;
char unidad;
int sec;
int min;
int hora;
int dia;
int mes;
int anio;
void setup(void);
void leer_hora(void);

//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("ADC     Fecha");
    while(1){

        //Split the into char to display on lcd
//         char sec_0 = sec%10;
//         char sec_1 = (sec/10);
//         char min_0 = min%10;
//         char min_1 = min/10;
//         char hour_0 = hora%10;
//         char hour_1 = hora/10;
//         char date_0 = dia%10;
//         char date_1 = dia/10;
//         char month_0 = mes%10;
//         char month_1 = mes/10;
//         char year_0 = anio%10;
//         char year_1 = anio/10;
        
        I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(PORTB);
        I2C_Master_Stop();
        __delay_us(250);
       
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        ADC = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_us(250);
        
        leer_hora();
        
        centenas = (ADC/100);
        decenas = (ADC/10)%10;
        unidad = ADC%10;

        Lcd_Set_Cursor(2,1);
        Lcd_Write_Char(centenas + 48);
        Lcd_Write_Char(decenas + 48);
        Lcd_Write_Char(unidad + 48);
        
        Lcd_Set_Cursor(2,8);
        Lcd_Write_Char(sec+48);


    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    OSCCONbits.IRCF = 0b111;        
    OSCCONbits.SCS = 1;
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
}

void leer_hora(void){
    
    I2C_Master_Start();            //Incia comunicaión I2C
    I2C_Master_Write(0xD0);        //Escoje dirección del reloj
    I2C_Master_Write(0x00);        //Posición donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniación I2C
    I2C_Master_Write(0xD1);        //Leer posición
    sec = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Write(0);
    min = I2C_Master_Read(0x01);      //lee posicion de reloj
    I2C_Master_Write(0);
    hora = I2C_Master_Read(0x02);      //lee posicion de reloj
    I2C_Master_Write(1);
    I2C_Master_Stop();             //Termina comunicaion I2C
}