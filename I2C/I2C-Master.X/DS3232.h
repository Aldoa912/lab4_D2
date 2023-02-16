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
int leer_seg(void);
int leer_min(void);
int leer_hora(void);
int leer_dia (void);
int leer_mes (void);
int leer_anio (void);
void enviar_fecha(void);





#endif	/* DS3232_H */

