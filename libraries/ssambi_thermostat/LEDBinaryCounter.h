/*
  LEDBinaryCounter.h - Library to display binary numbers on LEDs.
  Created by Stefano Sambi, 2013
*/
#ifndef ssambi_thermostat_LEDBinaryCounter
#define ssambi_thermostat_LEDBinaryCounter

#include "Arduino.h"

class LEDBinaryCounter
{
  public:
    LEDBinaryCounter(short pin0, short pin1, short pin2, short pin3, short pin4);
    void setValue(int value);
  private:
    short _pin0;
	short _pin1;
	short _pin2;
	short _pin3;
	short _pin4;
};

#endif