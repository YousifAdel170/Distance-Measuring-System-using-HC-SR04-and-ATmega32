/******************************************************************************
 * Module: LCD
 * File Name: lcd.c
 * Description: Source file for the LCD driver
 * Author: Yousif Adel
 *******************************************************************************/
#include "gpio.h"
#include "lcd.h"
#include <util/delay.h>		/* For the delay functions */
#include "common_macros.h"	/* For GET_BIT Macro */
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */

/*
	 Steps to initiate LCD 4-bit
		 1. setup the direction of the pins  RS,E as OUTPUT
		 2. setup the direction of DB4 .... DB7 as OUTPUT pins
		 3. send command LCD_TWO_LINES_FOUR_BITS_MODE_INIT1 [0x32]  , LCD_TWO_LINES_FOUR_BITS_MODE_INIT2 [0x33]
		 4. send command LCD_TWO_LINES_FOUR_BITS_MODE [0x28] 	(4-bit , 2 lines , 5x7 dots)
		 5. send command to remove cursor
		 6. send command to clear the LCD at the beginning
	 Steps to initiate LCD 8-bit
		 1. setup the direction of the pins  RS,E as OUTPUT
	 	 2. setup the direction of the port as OUPUT Port
	 	 3. send command LCD_TWO_LINES_EIGHT_BITS_MODE [0x38] 	(8-bit , 2 lines , 5x7 dots)
	 	 4. send command to remove cursor
		 5. send command to clear the LCD at the beginning
 */
void LCD_init()
{
	/* Configure the direction for RS and E pins as output pins */
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);
	_delay_ms(20);		/* LCD Power ON delay always > 15ms */

#if (LCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins in the data port as output pins */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#elif (LCD_DATA_BITS_MODE == 8)
	/* Configure the data port as output port */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);
	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif

	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}


/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(uint8 command)
{
	/* Instruction Mode RS=0 */
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	/* delay for processing Tas = 50ns */
	_delay_ms(1);
	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	/* delay for processing Tpw - Tdsw = 290 - 100 = 190ns */
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
#elif (LCD_DATA_BITS_MODE == 8)
	/* out the required command to the data bus D0 --> D7  whatever port initialize in lcd.h file*/
	GPIO_writePort(LCD_DATA_PORT_ID,command);
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
#endif
}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(uint8 data)
{
	/* Instruction Mode RS = 1 */
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
	/* delay for processing Tas = 50ns */
	_delay_ms(1);
	/* Enable LCD E=1 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	/* delay for processing Tpw - Tdsw = 190ns */
	_delay_ms(1);
#if (LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,7));
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	/* delay for processing Tpw - Tdsw = 190ns */
	_delay_ms(1);
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,3));
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
#elif (LCD_DATA_BITS_MODE == 8)
	/* put the required data to the data bus D0 --> D7  whatever port initialize in lcd.h file*/
	GPIO_writePort(LCD_DATA_PORT_ID,data);
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);
	/* Disable LCD E=0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	/* delay for processing Th = 13ns */
	_delay_ms(1);
#endif
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str)
{
	for(uint8 i=0; Str[i] != '\0' ;i++)
		LCD_displayCharacter(Str[i]);

	/***************** Another Method ***********************
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
	 *********************************************************/
	/***************** Another Method ***********************
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
	 *********************************************************/
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
	case 0:
		lcd_memory_address = col;
		break;
	case 1:
		lcd_memory_address = col + 0x40;
		break;
	case 2:
		lcd_memory_address = col + 0x10;
		break;
	case 3:
		lcd_memory_address = col + 0x50;
		break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_integerToString(int data)
{
	/* String to hold the ASCII result */
	char buff[16];
	/* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	itoa(data,buff,10);
	/*if i want to convert to hex use 16 instead of 10
	  if i want to convert to binary use 2 instead of 2*/
	LCD_displayString(buff); /* Display the string */
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* Send clear display command */
}
