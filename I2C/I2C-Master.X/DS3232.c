#include "DS3232.h"
#include "I2C.h"


void enviar_hora(void){
    
    I2C_Master_Start();            //Incia comunicaión I2C
    I2C_Master_Write(0xD0);        //Escoje dirección del reloj
    I2C_Master_Write(0x00);        //Posición de los segundos
    I2C_Master_Write(sec);         //Posición donde va leer
    I2C_Master_Write(min);         //Posición donde va leer
    I2C_Master_Write(hora);        //Posición donde va leer
    I2C_Master_Stop();             //Detiene la comunicaión I2C
}

int leer_seg(void){
    
    I2C_Master_Start();            //Incia comunicaión I2C
    I2C_Master_Write(0xD0);        //Escoje dirección del reloj
    I2C_Master_Write(0x00);        //Posición donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniación I2C
    I2C_Master_Write(0xD1);        //Leer posición
    sec = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    sec = (sec>>4)*10 + (sec & 0x0F);
    return sec;
}

int leer_min(void){
    
    I2C_Master_Start();            //Incia comunicaión I2C
    I2C_Master_Write(0xD0);        //Escoje dirección del reloj
    I2C_Master_Write(0x01);        //Posición donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniación I2C
    I2C_Master_Write(0xD1);        //Leer posición
    min = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    min = (min>>4)*10 + (min & 0x0F);
    return min;
}

int leer_hora(void){
    
    I2C_Master_Start();            //Incia comunicaión I2C
    I2C_Master_Write(0xD0);        //Escoje dirección del reloj
    I2C_Master_Write(0x02);        //Posición donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniación I2C
    I2C_Master_Write(0xD1);        //Leer posición
    hora = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    hora = (hora>>4)*10 + (hora & 0x0F);
    return hora;
}

int leer_dia(void){
    
    I2C_Master_Start();            //Incia comunicaión I2C
    I2C_Master_Write(0xD0);        //Escoje dirección del reloj
    I2C_Master_Write(0x04);        //Posición donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniación I2C
    I2C_Master_Write(0xD1);        //Leer posición
    dia = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    dia = (dia>>4)*10 + (dia & 0x0F);
    return dia;
}

int leer_mes(void){
    
    I2C_Master_Start();            //Incia comunicaión I2C
    I2C_Master_Write(0xD0);        //Escoje dirección del reloj
    I2C_Master_Write(0x05);        //Posición donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniación I2C
    I2C_Master_Write(0xD1);        //Leer posición
    mes = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    mes = (mes>>4)*10 + (mes & 0x0F);
    return mes;
}

int leer_anio(void){
    
    I2C_Master_Start();            //Incia comunicaión I2C
    I2C_Master_Write(0xD0);        //Escoje dirección del reloj
    I2C_Master_Write(0x06);        //Posición donde va leer
    I2C_Master_RepeatedStart();          //Reinicia la comuniación I2C
    I2C_Master_Write(0xD1);        //Leer posición
    anio = I2C_Master_Read(0x00);      //lee posicion de reloj
    I2C_Master_Stop();             //Termina comunicaion I2C
    anio = (anio>>4)*10 + (anio & 0x0F);
    return hora;
}

void enviar_fecha(void){
    
    I2C_Master_Start();            //Incia comunicaión I2C
    I2C_Master_Write(0xD0);        //Escoje dirección del reloj
    I2C_Master_Write(0x04);        //Posición de los segundos
    I2C_Master_Write(dia);         //Posición donde va leer
    I2C_Master_Write(mes);         //Posición donde va leer
    I2C_Master_Write(anio);        //Posición donde va leer
    I2C_Master_Stop();             //Detiene la comunicaión I2C
}



//void leer_fecha(void){
//    
//    I2C_start();            //Incia comunicaión I2C
//    I2C_write(0xD0);        //Escoje dirección del reloj
//    I2C_write(0x04);        //Posición donde va leer
//    I2C_restart();          //Reinicia la comuniación I2C
//    I2C_write(0xD1);        //Leer posición
//    dia = I2C_read();      //lee posicion de reloj
//    I2C_ack();
//    mes = I2C_read();      //lee posicion de reloj
//    I2C_ack();
//    anio = I2C_read();      //lee posicion de reloj
//    I2C_nack();
//    I2C_stop();             //Termina comunicaion I2C
//}

