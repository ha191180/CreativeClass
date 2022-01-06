#include <Arduino.h>
#include "body.hpp"

void body::setup() {
  this->wheel = new motors(lMotorRevPin, lMotorPwmPin, rMotorRevPin, rMotorPwmPin);
  this->ltSens = new linetraceSensors(rrTraceSensorPin, rcTraceSensorPin, lcTraceSensorPin, llTraceSensorPin);
  this->proxSens = new proximitySensors(rProxSensorPin, cProxSensorPin, lProxSensorPin);
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
  return proxSens->isObjDetected();
}

/*
bool body::isObjDisappeared(){ // return boolean value. true: a object is dropped.
  double totalDistance = 0;
  totalDistance += proxSens->getLeftValue() - proxSens->getLeftPreviousValue();
  totalDistance += proxSens->getCenterValue() - proxSens->getCenterPreviousValue();
  totalDistance += proxSens->getRightValue() - proxSens->getRightPreviousValue();
  if (totalDistance > 130){
    Serial.print("[*] Object Disappeared!");
    return true;
  }
  else return false;
}
*/



bool body::isObjDisappeared(){
  ltSens->reload();
  if(ltSens->get()) return true;
  else return false;
}


void body::searchObj(){ // spin while object is not in front of robot.
  while(!isObjDetected()){
    wheel->turnLeft();
  }
  return;
}

void body::pushObj(){
  bool isObjOnField= true;
  while(!isObjDetected()){
    Serial.println("[*] init turn");
    wheel->turnLeft();
  }
  while(isObjOnField){
    if (isObjDetected()){
      // Serial.println("[*] object detected");
      // debug();
      if (isObjDisappeared()){
        // Serial.println("[*] object dropped");
        isObjOnField = false;
      }
      wheel->moveForwardEveryMillisec(100);
    }
    else{
      if (proxSens->isAimLeft())
      {
        // Serial.println("[*] go right");
        wheel->turnRight();
      }
      if (proxSens->isAimRight())
      {
        // Serial.println("[*]go left");
        wheel->turnLeft(); // Aim reset.
      }
    }
  }
  return;
}

// pushobj 中のライン検出

void body::sumo(){
  int count = 0;
  while (count != 3)
  {
    pushObj();
    wheel->moveBackwardForSec(1);
    count++;
  }
  return;
}

void body::swmode(){

  // PHASE1 /////////////////////////////////////////////////////////////////////////// touch the line
  ltSens->reload();
  senstmp = ltSens->get();
  while (senstmp != 0b1111){
    ltSens->reload();
    senstmp = ltSens->get(); //senstmp = 0b0000 (ll) (lc) (rc) (rr) ex. 0b00001100
    switch (senstmp) {
      case 0: // 0000
        wheel->moveForwardEveryMillisec(100);
        break;
      case 1: // 0001
        while (senstmp != 0b1111) {
          ltSens->reload();
          senstmp = ltSens->get();
          wheel->turnRightEveryMillisec(100);
        }
        wheel->halt();
        break;
      case 2: // 0010
        // Exception
        break;
      case 3: // 0011
        while (senstmp != 0b1111) {
          ltSens->reload();
          senstmp = ltSens->get();
          wheel->turnRightEveryMillisec(50);
        }
        wheel->halt();
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
        while (senstmp != 0b1111) {
          ltSens->reload();
          senstmp = ltSens->get();
          wheel->turnRightEveryMillisec(20);
        }
        wheel->halt();
        break;
      case 8: // 1000
        while (senstmp != 0b1111) {
          ltSens->reload();
          senstmp = ltSens->get();
          wheel->turnLeftEveryMillisec(100);
        }
        break;
      case 9: // 1001
        wheel->moveBackwardForSec(2);
        wheel->turnLeftSelMillisec();
        break;
      case 10: // 1010
        // Exception
        break;
      case 11: // 1011
        wheel->moveBackwardForSec(3);
        wheel->turnLeftSelMillisec();
        break;
      case 12: // 1100
        while (senstmp != 0b1111) {
          ltSens->reload();
          senstmp = ltSens->get();
          wheel->turnLeftEveryMillisec(50);
        }
        wheel->halt();
        break;
      case 13: // 1101
        wheel->moveBackwardForSec(3);
        wheel->turnLeftSelMillisec();
        break;
      case 14: // 1110
        while (senstmp != 0b1111) {
          ltSens->reload();
          senstmp = ltSens->get();
          wheel->turnLeftEveryMillisec(20);
        }
        wheel->halt();
        break;
      case 15: // 1111
        // Finish
        break;
    }
  }

  wheel->halt();
  wheel->goLeft90();

  // PHASE2 /////////////////////////////////////////////////////////////////////////// goto the course
  ltSens->reload();
  senstmp = ltSens->get();
  while (senstmp != 0b1001) {
    ltSens->reload();
    senstmp = ltSens->get();
    while (senstmp = 0b0000 || senstmp = 0b1000) {
      wheel->goRight();
      ltSens->reload();
      senstmp = ltSens->get();
    }
    wheel->halt();

    while (senstmp = 0b0001) {
      wheel->goLeft();
      ltSens->reload();
      senstmp = ltSens->get();
    }
    wheel->halt();

    wheel->turnLeftSelMillisec(millisec);

    tSens->reload();
    senstmp = ltSens->get();

    if (senstmp = 0b1111) {
      wheel->goLeft90();
      continue
    }
    else{
      while (senstmp != 0b0100 || senstmp != 0b0110 ) {
        wheel->turnLeft();
        tSens->reload();
        senstmp = ltSens->get();
      }
      wheel->halt();
      break
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
