#include "Arduino.h"
#include "./proximitySensor.hpp"


proximitySensor::proximitySensor(int pin){
	_pin = pin;
  val = 0.0;
}

void proximitySensor::reload(){ 
  previousVal = val;
  double sum = 0;
  for (byte i = 0; i < 255; i++){
    sum += analogRead(_pin);
  }
  val = 21000.0*pow(sum/255.0, -1.252);
  //if (val > double(th)) val = th;
}

double proximitySensor::get(){
  return this->val;
}

double proximitySensor::getPrevious(){
  return this->previousVal;
}
