#include <wiringPi.h>

int main(){
  wiringPiSetup();
  int LED[] = {0,2,3,21};
  int noOfLEDs = 4;
  for (int i = 0; i < noOfLEDs;i++){
    pinMode(LED[i], OUTPUT);
    digitalWrite(LED[i],0);
  }
  return 0;
}
	
