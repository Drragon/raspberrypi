#include <wiringPi.h>
#include <string.h>
#include <stdlib.h>
#include <csignal>

bool exists(int argument, int LED[], int noOfLEDs);
void cleanUp(int signum);
  
int LED[] = {0,2,3,21};
int noOfLEDs = 4;

int main(int argc, char *argv[]){
  wiringPiSetup();
  for(int i = 0; i < noOfLEDs;i++){
    pinMode(LED[i], OUTPUT);
  }
  signal(SIGINT, cleanUp);
  signal(SIGTERM, cleanUp);
  int speed = 500;
  int runSpeed = 200;
  int argument1;
  if (argc == 3){
    speed = atoi(argv[2]);
  }
  if (argc > 1){
    if (!strcmp(argv[1], "all")){
      for(;;){
        for (int i = 0;i<noOfLEDs;i++){
          digitalWrite(LED[i], 1);
        }
        delay(speed);
        for (int i = 0;i<noOfLEDs;i++){
          digitalWrite(LED[i],0);
        }
        delay(speed);
      }
    }
    else if (!strcmp(argv[1], "runright")){
      if (argc == 3)
	runSpeed = atoi(argv[2]);
      for(;;){
	for (int i = 0; i < noOfLEDs; i++){
	  digitalWrite(LED[i], 1);
	  delay(runSpeed);
          digitalWrite(LED[i], 0);
        }
      }        
    }
    else if (!strcmp(argv[1], "runleft")){
      if (argc == 3)
	runSpeed = atoi(argv[2]);
      for(;;){
	for (int i = noOfLEDs-1; i >= 0; i--){
	  digitalWrite(LED[i], 1);
	  delay(runSpeed);
          digitalWrite(LED[i], 0);
        }
      }        
    }
    else{
      argument1 = atoi(argv[1]);
      if (exists(argument1, LED, noOfLEDs)){
        for(;;){
          digitalWrite(argument1,1);
          delay(speed);
          digitalWrite(argument1,0);
          delay(speed);
        }
      }
    }
  }  
  else{
    for(;;){
      digitalWrite(LED[0], 1);
      delay(speed);
      digitalWrite(LED[0], 0);
      delay(speed);
    }
  }   

  return 0;
}

bool exists(int argument, int LED[], int noOfLEDs){
  for (int i = 0;i < noOfLEDs; i++){
    if (argument==LED[i])
	return true;
  }
  return false;
}

void cleanUp(int signum){
  for (int i = 0; i < noOfLEDs; i++){
    digitalWrite(LED[i], 0);
  }
  exit(signum);
}

