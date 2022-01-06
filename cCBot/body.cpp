#include <Arduino.h>
#include "body.hpp"

void body::setup() {
  this->wheel = new motors(lMotorRevPin, lMotorPwmPin, rMotorRevPin, rMotorPwmPin);
  this->ltSens = new linetraceSensors(rrTraceSensorPin, rcTraceSensorPin, lcTraceSensorPin, llTraceSensorPin);
  this->proxSens = new proximitySensors(rProxSensorPin, cProxSensorPin, lProxSensorPin);
  wheel->halt();
}

void body::test(){
  int total = 0;
  for (int c = 0; c < 100; c++){
    for (int i = 0; i < 4; i++){
      ltSens->reload();
      int b = (1 << i);
      total += bool(ltSens->get() bitand b);
    }
  }
  Serial.println(total);
}


void body::debug(){ // output the essential values to serial out.
  if (!isDebugEnabled){
    Serial.begin(9600);
    isDebugEnabled = true;
  }

  if (millis() - previousTime > 1000){
    debugOut();
    previousTime = millis();
  }
}

void body::debugOut(){
  Serial.print("#########################################\n");
  Serial.print("[Time: ");
  Serial.print(millis()/1000);
  Serial.print("sec]\n");
  Serial.print("\n");
  Serial.print("[Line Trace Sensors]\n");
  ltSens->reload();
  if (ltSens->get() bitand 0b1000) Serial.print("BLACK "); else Serial.print("WHITE ");
  if (ltSens->get() bitand 0b0100) Serial.print("BLACK "); else Serial.print("WHITE ");
  if (ltSens->get() bitand 0b0010) Serial.print("BLACK "); else Serial.print("WHITE ");
  if (ltSens->get() bitand 0b0001) Serial.print("BLACK "); else Serial.print("WHITE ");
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("[Proximity Sensors]\n");
  proxSens->reload();
  Serial.print(double(proxSens->getLeftValue()));
  Serial.print("\t");
  Serial.print(double(proxSens->getCenterValue()));
  Serial.print("\t");
  Serial.print(double(proxSens->getRightValue()));
  Serial.print("\n");
  Serial.print("isObjectDetected: ");
  Serial.println(isObjDetected());
  Serial.print("#####################################\n\n");
}

bool body::isObjDetected(){ // return boolean value. true: a object is detected, false: else.
  return proxSens->isObjDetected();  // need reload time every millisec
}


bool body::isObjDisappeared(){ // return boolean value. true: a object is dropped.
  double totalDistance = 0.0;
  delay(100);
  proxSens->reload();
  totalDistance += proxSens->getLeftValue() - proxSens->getLeftPreviousValue();
  totalDistance += proxSens->getCenterValue() - proxSens->getCenterPreviousValue();
  totalDistance += proxSens->getRightValue() - proxSens->getRightPreviousValue();
  if (totalDistance > 260.0){
    Serial.println("[*] Object Disappeared!");
    return true;
  }
  else return false;
}




bool body::isObjDisappearedRecheck(){
  int total = 0;
  for (int c = 0; c < 100; c++){
    for (int i = 0; i < 4; i++){
      ltSens->reload();
      int b = (1 << i);
      total += bool(ltSens->get() bitand b);
    }
  }
  if (total > 150){
    return true;
  }
  else return false;
}


void body::pushObj(){
  bool isObjOnField= true;
  while(!isObjDetected()){
    wheel->turnLeftEveryMillisec(50);
  }

  while(isObjOnField){
    if (isObjDetected()){
      if (isObjDisappeared()){
        isObjOnField = false;
      }
      else {
        if (proxSens->getCenterValue() > 30.0){
          wheel->moveForward();
        }
        else {
          wheel->moveForwardEveryMillisec(80);
        }
      }
    }
    else{
      if (proxSens->isAimLeft()) 
      {
        // Serial.println("[*] go right");
        wheel->turnRightEveryMillisec(50);
      }
      else if (proxSens->isAimRight()) 
      {
        // Serial.println("[*]go left");
        wheel->turnLeftEveryMillisec(50); // Aim reset.
      }
      else 
      {
        wheel->turnLeft();
      }
    }
  }
  return;
}


void body::sumo(){
  int count = 0;
  while (count != 3)
  {
    pushObj();
    wheel->moveBackwardForMillisec(500);
    count++;
  }
  return;
}

void body::swmode(){
  
  // PHASE1 /////////////////////////////////////////////////////////////////////////// touch the line
  char senstmp = 1;
  while (senstmp != 0b1111){
    ltSens->reload();
    senstmp = ltSens->get(); //senstmp = 0b0000 (ll) (lc) (rc) (rr) ex. 0b00001100
    switch (senstmp) {
      case 0: // 0000
        wheel->moveForwardEveryMillisec(100);
        break;
      case 1: // 0001
        wheel->turnRight();
        break;
      case 2: // 0010
        // Exception
        break;
      case 3: // 0011
        // Exception
        break;
      case 4: // 0100
        // Exception
        break;
      case 5: // 0101
        // Exception
        break;
      case 6: // 0110
        // Exception
        break;
      case 7: // 0111
        wheel->turnRight();
        break;
      case 8: // 1000
        wheel->turnLeft();
        break;
      case 9: // 1001
        wheel->moveBackwardForMillisec(500);
        wheel->turnRight();
        break;
      case 10: // 1010
        // Exception
        break;
      case 11: // 1011
        // Exception
        break;
      case 12: // 1100
        wheel->turnLeft(); 
        break;
      case 13: // 1101
        // Exception
        break;
      case 14: // 1110
        wheel->turnLeft();
        break;
      case 15: // 1111
        // Finish
        break;
    }
  }

  wheel->goRight90();

  // PHASE2 /////////////////////////////////////////////////////////////////////////// goto the edge
  while (senstmp != 0b1111){
    ltSens->reload();
    senstmp = ltSens->get(); 
    switch (senstmp) {
      case 0: // 0000
        wheel->goLeft();
        break;
      case 8: // 1000
        wheel->goRight();
        break;
      case 9: // 1001
        wheel->turnRight();
        break;
      case 10: // 1010
        // Exception
        break;
      case 11: // 1011
        // Exception
        break;
      case 14: // 1110
        wheel->turnRight();
        break;
      case 15: // 1111
        // Finish
        break;
    }
  }

  
}

void body::hilldown() {
  char senstmp = 1;
  while (senstmp bitand 0b1000) {
    ltSens->reload();
    senstmp = ltSens->get();
    switch (senstmp) {
      case 0: // 0000

        break;
      case 1: // 0001

        break;
      case 2: // 0010
        wheel->goRight();
        break;
      case 3: // 0011

        break;
      case 4: // 0100
        wheel->goLeft();     
        break;
      case 5: // 0101

        break;
      case 6: // 0110

        break;
      case 7: // 0111

        break;
      case 8: // 1000

        break;
      case 9: // 1001

        break;
      case 10: // 1010

        break;
      case 11: // 1011

        break;
      case 12: // 1100

        break;
      case 13: // 1101

        break;
      case 14: // 1110

        break;
      case 15: // 1111

        break;
    }
  }
}

void body::lineTrace() {
  char senstmp = 1;
  while (senstmp != 0){
    ltSens->reload();
    senstmp = ltSens->get(); //senstmp = 0b0000 (ll) (lc) (rc) (rr) ex. 0b00001100
    switch (senstmp) {
      case 0: // 0000

        break;
      case 1: // 0001

        break;
      case 2: // 0010
        wheel->turnRight();
        break;
      case 3: // 0011
        wheel->moveForward();
        break;
      case 4: // 0100
      
        break;
      case 5: // 0101

        break;
      case 6: // 0110

        break;
      case 7: // 0111

        break;
      case 8: // 1000

        break;
      case 9: // 1001

        break;
      case 10: // 1010

        break;
      case 11: // 1011
        wheel->turnLeft();
        break;
      case 12: // 1100
        wheel->turnRight(); // turn90deg
        break;
      case 13: // 1101

        break;
      case 14: // 1110

        break;
      case 15: // 1111
        wheel->moveForward();
        break;
    }
  }
  return;
}
