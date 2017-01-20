#include <wiringPi.h>

int LED[] = {0,2,3,21};
int noOfLEDs = 4;
int button[] = {6,27,28,29};
int noOfButtons = 4;
bool buttonPressed[]={0,0,0,0};

int main(){
   wiringPiSetup();

   for (int i = 0; i < noOfButtons; i++){
     pinMode(button[i], INPUT);
     pullUpDnControl(button[i], PUD_UP);
   }
   for (int i = 0; i < noOfLEDs; i++){
     pinMode(LED[i], OUTPUT);
   }

   for(;;){
     for (int i=0;i<noOfButtons;i++){
       if (!digitalRead(button[i]) && !buttonPressed[i] ){
	 digitalWrite(LED[i], 1);
	 buttonPressed[i] = true;
       }
       else if (digitalRead(button[i]) && buttonPressed[i] ){
         digitalWrite(LED[i],0);
         buttonPressed[i] = false;
       }
     }
     delay(20);
   }
   return 0;
}
