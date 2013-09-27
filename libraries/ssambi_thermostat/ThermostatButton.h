/*
  ThermostatButton.h - Library for buttons used to increment/decrement the temperature target in thermostat.
  Created by Stefano Sambi, 2013
*/
#ifndef ssambi_thermostat_Button
#define ssambi_thermostat_Button

#include "Arduino.h"

class ThermostatButton
{
  public:
    ThermostatButton(int pin, int debounceDelay);
    bool isOneShotPressed();
  private:
    int _pin;
	int _debounceDelay;
	int _buttonState;
	long _lastDebounceTime;
};

#endif