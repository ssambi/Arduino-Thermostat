// OneWire library from http://www.pjrc.com/teensy/td_libs_OneWire.html
#include <OneWire.h>
// DallasTemperature library from http://milesburton.com/Dallas_Temperature_Control_Library
#include <DallasTemperature.h>

// my own libraries
#include <ThermostatButton.h>
#include <LEDBinaryCounter.h>

// DS18B20 (onewire temperature sensor) data line pin
#define ONE_WIRE_BUS 10

// Relay pin
#define RELAY_PIN 2

// Pins for the buttons to control the target temperature
#define BUTTON_MINUS_PIN 11
#define BUTTON_PLUS_PIN 12

// Pins for the LEDs binary counter
#define LED_BIT0 7
#define LED_BIT1 6
#define LED_BIT2 5
#define LED_BIT3 4
#define LED_BIT4 3

// histeresis used to control the temperature (in celsius degrees)
#define HISTERESIS 1

// initial target temperature
#define INITIAL_TARGET_TEMP 20

// Setup the temperature sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Setup the buttons to control the target temperature
ThermostatButton minusButton(BUTTON_MINUS_PIN, 100);
ThermostatButton plusButton(BUTTON_PLUS_PIN, 100);

// Setup the LEDs binary counter
LEDBinaryCounter ledCounter(LED_BIT0, LED_BIT1, LED_BIT2, LED_BIT3, LED_BIT4);

// target temperature
int targetTemperature;

// status of the relay output
int relayStatus = LOW;

// time of the last temperature request
long lastTemperatureRequest = 0;

// current temperature detected (in celsius degrees)
float currentTemperature = 0;

// last time when the button was pressed
long lastButtonPressed = 0;

// boolean to control if the LEDs binary counter must show the target temperature or the current temperature
boolean showTargetTemperature = false;

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);
  
  // serial port used to debug
  Serial.begin(9600);4

  // Setup the temperature sensor
  sensors.begin(); 
  
  // debug for temperature sensor
  Serial.print("Parasite power: "); 
  if (sensors.isParasitePowerMode()) 
    Serial.println("ON");
  else 
    Serial.println("OFF");
  
  Serial.print("Resolution: "); 
  Serial.println(sensors.getResolution());
  
  // initial target temperature
  targetTemperature = INITIAL_TARGET_TEMP;
}


void loop()
{
  
  // controller for the buttons
  if (minusButton.isOneShotPressed()) {
    targetTemperature--;
    buttonPressed();
  }
  if (plusButton.isOneShotPressed()) {
    targetTemperature++;
    buttonPressed();
  }
  
  // the target temperature must be shown for 5 seconds after the button were pressed
  showTargetTemperature = lastButtonPressed != 0 && (lastButtonPressed + 5000 > millis());  
  
  // request the temperature to the sensor and after 1 second fetch the temperature value
  if (lastTemperatureRequest + 1000 > millis()) {
    currentTemperature = getActualTemperature();
    
    // consider the target temperature histeresis
    float targetTemperatureWithHisteresis;
    if (relayStatus == 1) {
      targetTemperatureWithHisteresis = targetTemperature - HISTERESIS;
    } else {
      targetTemperatureWithHisteresis = targetTemperature + HISTERESIS;
    }
    
    // command the relay output based on current and target temperatures
    if (currentTemperature > targetTemperatureWithHisteresis) {
      relayStatus = 1;
    } else {
      relayStatus = 0;
    }
    digitalWrite(RELAY_PIN, relayStatus);
    
  } else {
    // request of temperature to the temperature sensor
    requestTemperature();
    lastTemperatureRequest = millis();
  }
  
  // show the target temperature (or the current temperature, based on 'showTargetTemperature' value) on LEDs binary counter
  if (!showTargetTemperature) {
    int currentT = round(currentTemperature);
    //Serial.println(currentT); 
    
    ledCounter.setValue(currentT);
    //setBinaryLED(currentT);
  } else {
    ledCounter.setValue(targetTemperature);
    //setBinaryLED(targetTemperature); 
  }
  
}

// set state when a button is pressed
void buttonPressed() {
  showTargetTemperature = true;
  lastButtonPressed = millis();
  Serial.print("targetTemperature = ");
  Serial.println(targetTemperature);
}

// request the temperature to the sensor
void requestTemperature() {
  //Serial.print("Requesting temperature");
  sensors.requestTemperatures();
  //Serial.println("DONE");
}

// fetch the temperature value from the sensor
float getActualTemperature() {
  float currentTemperature = sensors.getTempCByIndex(0);
  
  //Serial.print("Temperature: ");
  //Serial.println(currentTemperature);
  
  return currentTemperature;
}


