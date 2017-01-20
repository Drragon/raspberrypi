#include <wiringPi.h>
#include "simon.h"

int rounds = 10;

int main(int argc, char* argv[]){
  wiringPiSetup();
  if (argc==2)
    rounds = atoi(argv[1]);
  int LED[] = {0,2,3,21};
  int noOfLEDs = 4;
  int button[] = {6,27,28,29};
  int noOfButtons = 4;
  system("sudo /home/pi/buttonInput &");

  for(int i = 0; i < noOfLEDs;i++){
    pinMode(LED[i], OUTPUT);
    pinMode(button[i], INPUT);
    pullUpDnControl(button[i], PUD_UP);
  }
  playSimon(LED, noOfLEDs, button, noOfButtons, rounds);
  return 0;  
}

  
