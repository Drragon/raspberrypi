#include "lcd.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){
  setupLCD();
  if (argc == 2)
    boop(argv[1]);
  else{
    char word[]="boop!";
    boop (word);
  }
  return 0;
}
