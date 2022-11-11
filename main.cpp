/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#define fmin 100.0
#define fmax 220.0
#define ledPeriod 100000


AnalogIn int_temp(ADC_TEMP);
AnalogIn potenciometro(A0);
PwmOut led(D5);
PwmOut buzzer(D2);

#define WAIT_TIME_MS 100


int main()
{
    //Establecer la tensión de referencia
    int_temp.set_reference_voltage(3.3);
    
    led.pulsewidth_us(ledPeriod);
    buzzer.period(1/fmin);
    buzzer.write(0.50f);  // 50% duty cycle

    while (true)
    {
        //Ejemplos de leer una señal analógica
        float datof=int_temp.read(); //Lee el dato en flotante entre 0 y 1.0. Para 0V 0 y para 3.3V 1.0
        float datoV=int_temp.read_voltage(); //Lee el dato en voltios. De 0 a Vref, 3.3V
        int datoI=int_temp.read_u16(); //Lee el dato en entero como si el ADC fuese de 16bits, aunque no lo sea.
        float temp=((datoV - 0.76)/2.5) + 25;

        //Ejemplos de generar una señal de PWM
        float angulotenciometro=potenciometro.read()*360;
        led.pulsewidth_us(angulotenciometro/360.0*ledPeriod);
        float frecuencia=angulotenciometro/360*(fmax-fmin)+fmin;
        buzzer.period(1/frecuencia);

        printf("El dato leido entre 0 y 1 es: %f\n",datof);
        printf("El dato leido en voltios entre 0 y 3.3 es: %f\n",datoV);
        printf("El dato leido del ADC de 16bits es: %d\n",datoI);
        printf("La temperatura es es: %fCº\n",temp);
        printf("El angulo del potenciometro es: %f\n",angulotenciometro);
        printf("Frecuencia tono: %f\n",frecuencia);
        printf("*************************************\n");

        thread_sleep_for(WAIT_TIME_MS);
    }
}
