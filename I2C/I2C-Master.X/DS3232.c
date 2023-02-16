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

int leer_seg(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x00);        //Posici�n donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniaci�n I2C
    I2C_Master_Write(0xD1);        //Leer posici�n
    sec = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    sec = (sec>>4)*10 + (sec & 0x0F);
    return sec;
}

int leer_min(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x01);        //Posici�n donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniaci�n I2C
    I2C_Master_Write(0xD1);        //Leer posici�n
    min = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    min = (min>>4)*10 + (min & 0x0F);
    return min;
}

int leer_hora(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x02);        //Posici�n donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniaci�n I2C
    I2C_Master_Write(0xD1);        //Leer posici�n
    hora = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    hora = (hora>>4)*10 + (hora & 0x0F);
    return hora;
}

int leer_dia(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x04);        //Posici�n donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniaci�n I2C
    I2C_Master_Write(0xD1);        //Leer posici�n
    dia = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    dia = (dia>>4)*10 + (dia & 0x0F);
    return dia;
}

int leer_mes(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x05);        //Posici�n donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniaci�n I2C
    I2C_Master_Write(0xD1);        //Leer posici�n
    mes = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    mes = (mes>>4)*10 + (mes & 0x0F);
    return mes;
}

int leer_anio(void){
    
    I2C_Master_Start();            //Incia comunicai�n I2C
    I2C_Master_Write(0xD0);        //Escoje direcci�n del reloj
    I2C_Master_Write(0x06);        //Posici�n donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniaci�n I2C
    I2C_Master_Write(0xD1);        //Leer posici�n
    anio = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    anio = (anio>>4)*10 + (anio & 0x0F);
    return hora;
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



//void leer_fecha(void){
//    
//    I2C_start();            //Incia comunicai�n I2C
//    I2C_write(0xD0);        //Escoje direcci�n del reloj
//    I2C_write(0x04);        //Posici�n donde va leer
//    I2C_restart();          //Reinicia la comuniaci�n I2C
//    I2C_write(0xD1);        //Leer posici�n
//    dia = I2C_read();      //lee posicion de reloj
//    I2C_ack();
//    mes = I2C_read();      //lee posicion de reloj
//    I2C_ack();
//    anio = I2C_read();      //lee posicion de reloj
//    I2C_nack();
//    I2C_stop();             //Termina comunicaion I2C
//}

