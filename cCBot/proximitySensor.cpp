#include "Arduino.h"
#include "./proximitySensor.hpp"


proximitySensor::proximitySensor(int pin){
	_pin = pin;
  dataQueue = Queue<int>(queueSize);
  for (int i = 0; i < queueSize; i++)
  {
    int tmpRawVoltage = analogRead(_pin);
    dataQueue.push(tmpRawVoltage);
    sumVoltage += tmpRawVoltage;
  }
  val = 21000.0*pow(((double)sumVoltage / (double)queueSize), -1.252);
}

void proximitySensor::reload(){ 
  previousVal = val;

  sumVoltage -= dataQueue.pop();
  int tmpRawVoltage = analogRead(_pin);
  dataQueue.push(tmpRawVoltage);
  sumVoltage += tmpRawVoltage;

  val = 21000.0*pow(((double)sumVoltage / (double)queueSize), -1.252);
}

void proximitySensor::reload(bool resetFlag){
  if (resetFlag){
    previousVal = val;
    for (int i = 0; i < queueSize; i++)
    {
      sumVoltage -= dataQueue.pop();
      int tmpRawVoltage = analogRead(_pin);
      dataQueue.push(tmpRawVoltage);
      sumVoltage += tmpRawVoltage;
    }
    val = 21000.0*pow(((double)sumVoltage / (double)queueSize), -1.252);
  }
  else reload();
}

double proximitySensor::get(){
  return this->val;
}

double proximitySensor::getPrevious(){
  return this->previousVal;
}
