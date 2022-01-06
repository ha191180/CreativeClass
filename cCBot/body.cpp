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




bool body::isEdge(){
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


int body::pushObj(){
  while(!isObjDetected()){
    proxSens->reload();
    wheel->turnLeftEveryMillisec(50);
  }

  /*
  while(isObjOnField){
    proxSens->reloadEveryMillisec(500);

    if (isEdge())
    {
      wheel->moveBackwardForMillisec(100);
    }
    
    if (isObjDetected()){
      if (isObjDisappeared()){
        isObjOnField = false;
      }
      else {
        if (proxSens->getCenterValue() > 30.0){
          proxSens->reload();
          wheel->moveForward();
        }
        else if (proxSens->isObjTouched()){
          wheel->punch();
          delay(1000);
        }
        else {
          wheel->moveForwardEveryMillisec(100);
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
        wheel->moveForwardEveryMillisec(100);
      }
    }
  }
  */

 // PHASE1 ////////////////////////////////////////////// aproaching
  bool phase1 = true;
  while(phase1){
    proxSens->reload();

    if (isObjDetected()){
      if (proxSens->getCenterValue() > 20.0){
        for (int i = 0; i < 3000; i++)
        {
          wheel->moveForward();
        }
        wheel->halt();
      }
      else{
        phase1 = false;
        break;
      }
    }
    else{
      if (proxSens->isAimLeft())
      {
        wheel->turnRightEveryMillisec(100);
      }
      else if (proxSens->isAimRight()) 
      {
        wheel->turnLeftEveryMillisec(100);
      }
      else 
      {
        return 0;
      }
    }
  }

  // PHASE2 /////////////////////////////////////////////////// touching
  bool phase2 = true;
  while(phase2){
    proxSens->reload();

    if (isObjDetected()){
      if (proxSens->isObjTouched()){
        phase2 = false;
        break;
      }
      else {
        wheel->moveForwardEveryMillisec(100);
      }
    }
    else{
      if (proxSens->isAimLeft())
      {
        wheel->turnRightEveryMillisec(100);
      }
      else if (proxSens->isAimRight()) 
      {
        wheel->turnLeftEveryMillisec(100);
      }
      else 
      {
        return 0;
      }
    }
  }
  // PHASE3 /////////////////////////////////////////////////// pushing
  bool phase3 = true;
  while (phase3){
    if (isEdge()){
      phase3 = false;
      wheel->moveBackwardForMillisec(100);
      delay(1000);
      return 1;
    }
    else {
      wheel->moveForwardEveryMillisec(100);
    }
  }
}


void body::sumo(){
  int count = 0;
  while (count <= 3)
  {
    count += pushObj();
  }
  return;
}

void body::swmode(){

  // PHASE1 /////////////////////////////////////////////////////////////////////////// touch the line
  ltSens->reload();
  byte senstmp = ltSens->get();
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
        wheel->moveBackwardForMillisec(500);
        wheel->turnLeftSelMillisec(100);
        break;
      case 10: // 1010
        // Exception
        break;
      case 11: // 1011
        wheel->moveBackwardForMillisec(500);
        wheel->turnLeftSelMillisec(100);
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
        wheel->moveBackwardForMillisec(500);
        wheel->turnLeftSelMillisec(100);
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
    while (senstmp == 0b0000 || senstmp == 0b1000) {
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

    wheel->turnLeftSelMillisec(100);

    ltSens->reload();
    senstmp = ltSens->get();

    if (senstmp = 0b1111) {
      wheel->goLeft90();
      continue;
    }
    else{
      while (senstmp != 0b0100 || senstmp != 0b0110 ) {
        wheel->turnLeft();
        ltSens->reload();
        senstmp = ltSens->get();
      }
      wheel->halt();
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
