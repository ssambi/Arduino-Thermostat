/*
  LEDBinaryCounter.cpp - Library to display binary numbers on LEDs.
  Created by Stefano Sambi, 2013
*/

#include "Arduino.h"
#include "LEDBinaryCounter.h"

LEDBinaryCounter::LEDBinaryCounter(short pin0, short pin1, short pin2, short pin3, short pin4)
{
  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  
  _pin0 = pin0;
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  _pin4 = pin4;
}

void LEDBinaryCounter::setValue(int value) {
   int v = min(31, max(0, value));
  
  if ((v & 1) == 1) {
    digitalWrite(_pin0, HIGH);
  } else {
    digitalWrite(_pin0, LOW);
  }
  if ((v & 2) == 2) {
    digitalWrite(_pin1, HIGH);
  } else {
    digitalWrite(_pin1, LOW);
  }
  if ((v & 4) == 4) {
    digitalWrite(_pin2, HIGH);
  } else {
    digitalWrite(_pin2, LOW);
  }
  if ((v & 8) == 8) {
    digitalWrite(_pin3, HIGH);
  } else {
    digitalWrite(_pin3, LOW);
  }
  if ((v & 16) == 16) {
    digitalWrite(_pin4, HIGH);
  } else {
    digitalWrite(_pin4, LOW);
  }
}
