#include "DS3232.h"
#include "I2C.h"


void enviar_hora(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x00);        //Posici�n de los segundos
    I2C_Master_Write(sec);         //Posici�n donde va leer
    I2C_Master_Write(min);         //Posici�n donde va leer
    I2C_Master_Write(hora);        //Posici�n donde va leer
    I2C_Master_Stop();             //Detiene la comunicai�n I2C
}

uint8_t leer_seg(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x00);        //Posici�n donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniaci�n I2C
    I2C_Master_Write(0xD1);        //Leer posici�n
    sec = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
}

uint8_t leer_min(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x00);        //Posici�n donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniaci�n I2C
    I2C_Master_Write(0xD1);        //Leer posici�n
    min = I2C_Master_Read(0x01);      //lee posicion de reloj
   
    I2C_Master_Stop();             //Termina comunicaion I2C
}

uint8_t leer_hora(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x00);        //Posici�n donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniaci�n I2C
    I2C_Master_Write(0xD1);        //Leer posici�n
    sec = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Write(0);
    min = I2C_Master_Read(0x01);      //lee posicion de reloj
    I2C_Master_Write(0);
    hora = I2C_Master_Read(0x02);      //lee posicion de reloj
    I2C_Master_Write(1);
    I2C_Master_Stop();             //Termina comunicaion I2C
}

void enviar_fecha(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x04);        //Posici�n de los segundos
    I2C_Master_Write(dia);         //Posici�n donde va leer
    I2C_Master_Write(mes);         //Posici�n donde va leer
    I2C_Master_Write(anio);        //Posici�n donde va leer
    I2C_Master_Stop();             //Detiene la comunicai�n I2C
}

void leer_fecha(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x04);        //Posici�n donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniaci�n I2C
    I2C_Master_Write(0xD1);        //Leer posici�n
    dia = I2C_Master_Read(0x04);      //lee posicion de reloj
    I2C_Master_Write(0);
    mes = I2C_Master_Read(0x05);      //lee posicion de reloj
    I2C_Master_Write(0);
    anio = I2C_Master_Read(0x06);      //lee posicion de reloj
    I2C_Master_Write(1);
    I2C_Master_Stop();             //Termina comunicaion I2C
}
