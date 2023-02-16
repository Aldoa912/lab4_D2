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
#include "DS3232.h"
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
char u_sec;
char d_sec;
char u_min;
char d_min;
char u_hora;
char d_hora;
char u_dia;
char d_dia;
char u_mes;
char d_mes;
char u_anio;
char d_anio;
char Fecha[];
int sec;
int min;
int hora;
int dia;
int mes;
int anio;
int flag;
int contador;
void setup(void);



void __interrupt () isr (void){
    if (INTCONbits.RBIF){
        if (PORTBbits.RB0 == 0){
            flag++;
            PORTAbits.RA0 = 1;
            if (flag == 2){
                flag = 0;
                PORTAbits.RA0 = 0;
            }

        }
        
        else if (PORTBbits.RB1 == 0 && flag == 1){
            contador++;
            if (contador == 3)
                contador = 0;
        }
        
        else if (PORTBbits.RB2 == 0 && flag == 1){
            if (contador == 0)
                dia++;
            else if (contador == 1)
                mes++;
            else if (contador == 2)
                anio++;
        }
        
        else if (PORTBbits.RB3 == 0 && flag == 1){
            if (contador == 0)
                dia--;
            else if (contador == 1)
                mes--;
            else if (contador == 2)
                anio--;
        }
 
        INTCONbits.RBIF = 0;
    }
    return;
}

//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("ADC");
    while(1){

       
        sec = leer_seg();
        min = leer_min();
        hora = leer_hora();
        dia = leer_dia();
        mes = leer_mes();
        anio = leer_anio();
        
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        ADC = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_us(250);
        
        centenas = (ADC/100);
        decenas = (ADC/10)%10;
        unidad = ADC%10;

        Lcd_Set_Cursor(2,1);
        Lcd_Write_Char(centenas + 48);
        Lcd_Write_Char(decenas + 48);
        Lcd_Write_Char(unidad + 48);
        
        
        u_hora = hora%10;
        d_hora = (hora/10)%10;
        
        Lcd_Set_Cursor(1,7);
        Lcd_Write_Char(d_hora+48);
        Lcd_Write_Char(u_hora+48);
        Lcd_Write_Char(':');
        
        
        u_min = min%10;
        d_min = (min/10)%10;
        
        Lcd_Write_Char(d_min+48);
        Lcd_Write_Char(u_min+48);
        Lcd_Write_Char(':');
        
        
        u_sec = sec%10;
        d_sec = (sec/10)%10;
        
        Lcd_Write_Char(d_sec+48);
        Lcd_Write_Char(u_sec+48);
        
        
        u_dia = dia%10;
        d_dia = (dia/10)%10;
        
        Lcd_Set_Cursor(2,7);
        Lcd_Write_Char(d_dia+48);
        Lcd_Write_Char(u_dia+48);
        Lcd_Write_Char('/');
        
        u_mes = mes%10;
        d_mes = (mes/10)%10;
        
        Lcd_Write_Char(d_mes+48);
        Lcd_Write_Char(u_mes+48);
        Lcd_Write_Char('/');
        
        u_anio = anio%10;
        d_anio = (anio/10)%10;
        
        Lcd_Write_String("20");
        Lcd_Write_Char(d_anio+48);
        Lcd_Write_Char(u_anio+48);
        
        while (flag == 1){
            
            enviar_fecha();
        
            I2C_Master_Start();
            I2C_Master_Write(0x51);
            ADC = I2C_Master_Read(0);
            I2C_Master_Stop();
            __delay_us(250);

            centenas = (ADC/100);
            decenas = (ADC/10)%10;
            unidad = ADC%10;

            Lcd_Set_Cursor(2,1);
            Lcd_Write_Char(centenas + 48);
            Lcd_Write_Char(decenas + 48);
            Lcd_Write_Char(unidad + 48);

            u_dia = dia%10;
            d_dia = (dia/10)%10;

            Lcd_Set_Cursor(2,7);
            Lcd_Write_Char(d_dia+48);
            Lcd_Write_Char(u_dia+48);
            Lcd_Write_Char('/');

            u_mes = mes%10;
            d_mes = (mes/10)%10;

            Lcd_Write_Char(d_mes+48);
            Lcd_Write_Char(u_mes+48);
            Lcd_Write_Char('/');

            u_anio = anio%10;
            d_anio = (anio/10)%10;

            Lcd_Write_String("20");
            Lcd_Write_Char(d_anio+48);
            Lcd_Write_Char(u_anio+48);

        
        }

    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0b00001111;
    TRISD = 0;
    TRISA = 0;
    PORTB = 0;
    PORTD = 0;
    PORTA = 0;
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    WPUBbits.WPUB2 = 1;
    WPUBbits.WPUB3 = 1;
    
    IOCB = 0b00001111;
    
//    INTCONbits.PEIE = 1;
    INTCONbits.RBIF = 0;
    INTCONbits.RBIE = 1;
    INTCONbits.GIE = 1;
    
    OSCCONbits.IRCF = 0b111;        
    OSCCONbits.SCS = 1;
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
}

