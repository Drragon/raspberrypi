#ifndef LCD_H
#define LCD_H

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>

const int LINE1 = 0x80;
const int LINE2 = 0xC0;


void display(char topString[], char bottomString[]);
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line); //move cursor
void ClrLcd(void); // clr LCD return home
void typeln(const char *s);
void typeChar(char val);
void lcdByte(char bits, int mode);
void lcd_toggle_enable(int bits);
void setupLCD();
void boop(char word[]);
#endif

