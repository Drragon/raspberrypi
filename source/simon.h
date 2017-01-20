#ifndef SIMON_H
#define SIMON_H

#include <wiringPi.h>
#include <stdlib.h>
#include <time.h>

void playSimon(int LED[], int noOfLEDs, int buttons[], int noOfButtons, int maxRounds);

#endif
