#include "Arduino.h"
#include "./linetraceSensor.hpp"


linetraceSensor::linetraceSensor(int pin){
	pinMode(pin, INPUT);
	_pin = pin;
}

void linetraceSensor::reload(){ // 0 white
	val = digitalRead(_pin);
}

bool linetraceSensor::get(){
  return val;
}
