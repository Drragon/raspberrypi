#include "lcd.h"

#define I2C_ADDR 0x27

#define LCD_WIDTH 16
// Define some device constants
#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

//const int LINE1 = 0x80;
//const int LINE2 = 0xC0;

//#define LINE1 0x80 // 1st line
//#define LINE2 0xC0 // 2nd line

#define LCD_BACKLIGHT 0x08  // On
// LCD_BACKLIGHT = 0x00  # Off

#define ENABLE 0b00000100 // Enable bit
int fd; 
const int eDelay = 1;

void display(char topString[], char bottomString[]){

  if (strlen(topString) != LCD_WIDTH || strlen(bottomString) != LCD_WIDTH)
    return;
}

void setupLCD(){ 
  fd = wiringPiI2CSetup(I2C_ADDR);

  lcdByte(0x33, LCD_CMD); //Init
  lcdByte(0x32, LCD_CMD); //Init
  lcdByte(0x06, LCD_CMD); //Curso move direction
  lcdByte(0x0C, LCD_CMD); //Display on, Cursor Off, Blink Off
  lcdByte(0x28, LCD_CMD); //Data length, number of lines, font size
  lcdByte(0x01, LCD_CMD); //clear display
  delay(eDelay);
}

void lcdByte(char bits, int mode){
  int highBits = mode | (bits & 0xF0) | LCD_BACKLIGHT;
  int lowBits = mode | (bits<<4) & 0xF0 |LCD_BACKLIGHT;
  
  //High bits
  wiringPiI2CReadReg8(fd, highBits);
  lcd_toggle_enable(highBits);

  //Low bits
  wiringPiI2CReadReg8(fd, lowBits);
  lcd_toggle_enable(lowBits);
}

void lcd_toggle_enable(int bits){
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(500);
}

// float to string
void typeFloat(float myFloat)   {
  char buffer[20];
  sprintf(buffer, "%4.2f",  myFloat);
  typeln(buffer);
}

// int to string
void typeInt(int i)   {
  char array1[20];
  sprintf(array1, "%d",  i);
  typeln(array1);
}

// clr lcd go home loc 0x80
void ClrLcd(void)   {
  lcdByte(0x01, LCD_CMD);
  lcdByte(0x02, LCD_CMD);
}

// go to location on LCD
void lcdLoc(int line)   {
  lcdByte(line, LCD_CMD);
}

// out char to LCD at current position
void typeChar(char val)   {

  lcdByte(val, LCD_CHR);
}


// this allows use of any size string
void typeln(const char *s)   {

  while ( *s ) lcdByte(*(s++), LCD_CHR);

}

//Bounce any "word" of 18 length randomly within the confines of the screen 
void boop(char word[]){
  int boopSpot;
  int lineNo;
  int line;
  char theWord[40];

  srand (time(NULL));

  strcpy(theWord, word);
  int wordLength = strlen(theWord);

  for (;;){
    boopSpot = rand()%(17-wordLength);
    lineNo = rand()%2;

    switch(lineNo){
      case 0:
        line = LINE1;
        break;
      case 1:
        line = LINE2;
    }


    for (int i = 0; i < boopSpot;i++){
      lcdLoc(line+i);
      typeChar(' ');
    }
    lcdLoc(line+boopSpot);
    typeln(theWord);
    for (int i = boopSpot + wordLength; i<=16;i++){
      lcdLoc(line+i);
      typeChar(' ');
    }
    delay(300);
    ClrLcd();
    delay(100);
  }
}   
