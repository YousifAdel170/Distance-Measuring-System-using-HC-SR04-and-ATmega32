/*
 ================================================================================================
 Name        : measure_distance_application.c
 Author      : Yousif Adel
 Description : Measure the distance using Ultrasonic sensor
 Date 		 : 20/10/2023
 ================================================================================================
 */
#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */
#include <util/delay.h>

/* Create configuration structure for ICU driver */
ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};

/*
 • Description
	➢ This is function used to adjust the readings [when sensor gets 100 it will display 100 on LCD].
 • Inputs: uint16 distance
 • Return: None
 */
void Ultrasonic_LCD_adjustAndDisplay(uint16 distance)
{
	if(distance>100)
	{
		if(distance >=133)
		{
			LCD_integerToString(distance-1);
		}
		else
		{
			LCD_integerToString(distance);
		}
	}
	else
	{
		if(distance <= 36)
		{
			LCD_integerToString(distance+1);
		}
		else
		{
			LCD_integerToString(distance);
		}
		/* In case the digital value is three or two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');
	}
}
int main(void)
{

	/* create variable to store the distance that sensor get it*/
	uint16 distance = 0;

	/* Initialize the ultrasonic sensor and ICU driver */
	Ultrasonic_init();

	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	/* Initialize the LCD driver */
	LCD_init();
	LCD_displayString("Distance= ");
	while(1)
	{
		distance = Ultrasonic_readDistance();
		LCD_moveCursor(0,10);

		Ultrasonic_LCD_adjustAndDisplay(distance);
		LCD_displayString("cm   ");

		/* delay to break the functions calling*/
		_delay_ms(100);
	}
}
