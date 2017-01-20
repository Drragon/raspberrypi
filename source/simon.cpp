#include <iostream>
#include "simon.h"

using namespace std;

void playSimon(int LED[], int noOfLEDs, int buttons[], int noOfButtons, int maxRounds){
  int pattern[20];
  int counter;
  bool correct;
  int buttonPressed = -1;  
  
  for (;;){
    counter = 0;
    correct = true;

    while (counter < maxRounds && correct == true){
      srand (time(NULL));
      pattern[counter] = rand() % noOfLEDs;
      	//Write out pattern
      for (int i = 0; i <=counter;i++){
        delay(400);
	digitalWrite(LED[pattern[i]], HIGH);
	delay (600);
 	digitalWrite(LED[pattern[i]], LOW);
      }

      //Read in pattern
      for(int j = 0; j <= counter; j++){
        buttonPressed = -1;
        while (buttonPressed==-1){
	  for (int i=0; i < noOfButtons;i++){
	    if (!digitalRead(buttons[i])){
		buttonPressed = i;
                break;
            }
	  }
	}  
	delay(400);

      //Check if correct or not
      //Incorrect button
        if (buttonPressed != pattern[j]){
	  correct = false;
          for (int i = 0; i<3;i++){
	    digitalWrite(LED[2],HIGH);
	    delay(300);
	    digitalWrite(LED[2],LOW);
	    delay(300);
          }
	  break;
        }
     //Correct button combination
      }
      if (!correct)
        break;
      counter++;

      for (int i = 0; i<noOfLEDs;i++){
       digitalWrite(LED[i], HIGH);
      }
      delay(300);
      for (int i = 0; i<noOfLEDs;i++){
        digitalWrite(LED[i], LOW);
      }
      delay(300);
     

      //Game won
      if (counter >= maxRounds){
        for (int j=0; j < 4; j++){
	  for (int i=0; i < noOfLEDs; i++){
            digitalWrite(LED[i], HIGH);
            delay(100);
            digitalWrite(LED[i], LOW);
          }
          for (int i=noOfLEDs-1;i>=0;i--){
	    digitalWrite(LED[i], HIGH);
            delay(100);
            digitalWrite(LED[i], LOW);
          }      
          delay(100);
        }
        break;
      }
    } 
  }
} 
