/* 
 * File:   DS3232.h
 * Author: aldoa
 *
 * Created on 10 de febrero de 2023, 12:33 PM
 */

#ifndef DS3232_H
#define	DS3232_H
#include <xc.h>
int sec;
int min;
int hora;
int dia;
int mes;
int anio;

void enviar_hora(void);
uint8_t leer_seg(void);
uint8_t leer_min(void);
uint8_t leer_hora(void);
void enviar_fecha(void);
void leer_fecha(void);




#endif	/* DS3232_H */

