/*
  ThermostatButton.cpp - Library for buttons used to increment/decrement the temperature target in thermostat.
  Created by Stefano Sambi, 2013
*/

#include "Arduino.h"
#include "ThermostatButton.h"

#define BUTTON_STATE_UNPRESSED 0
#define BUTTON_STATE_DEBOUNCING 1
#define BUTTON_STATE_PRESSED 2

ThermostatButton::ThermostatButton(int pin, int debounceDelay)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _debounceDelay = debounceDelay;
  
  _buttonState = BUTTON_STATE_UNPRESSED;
  _lastDebounceTime = 0;
}

bool ThermostatButton::isOneShotPressed()
{
  int buttonValue = digitalRead(_pin);
  if (buttonValue == HIGH) {
    
    if (_buttonState == BUTTON_STATE_UNPRESSED) {
      _lastDebounceTime = millis();
      _buttonState = BUTTON_STATE_DEBOUNCING;
    }
    
    if (_buttonState == BUTTON_STATE_DEBOUNCING && (millis() - _lastDebounceTime) > _debounceDelay) {     
      // reset
      _buttonState = BUTTON_STATE_PRESSED;
	  
	  return true;
    }
  } else {
    _buttonState = BUTTON_STATE_UNPRESSED;
  }
  
  return false;
}
