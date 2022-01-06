#include "Arduino.h"
#include "./motors.hpp"

motors::motors(int lRevPinInput,
               int lPwmPinInput,
               int rRevPinInput,
               int rPwmPinInput){
  lp = new motor(lRevPinInput, lPwmPinInput);
  rp = new motor(rRevPinInput, rPwmPinInput);
  rp->setBias(0.85);
}

void motors::moveForward(){
  lp->forward();
  rp->forward();
}

void motors::moveForward(int inputValue){
  lp->forward(inputValue);
  rp->forward(inputValue);
}

void motors::moveForwardEveryMillisec(int milliSecond){
  if(millis() - moveForwardEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < 1000; i++){
      moveForward();
    }
    halt();
    moveForwardEveryMillisecTimer = millis();
  }
}

void motors::moveBackward(){
  lp->backward();
  rp->backward();
}

void motors::moveBackwardForMillisec(int millisec){
  moveBackwardForMillisecTimer = millis();
  while (millis() - moveBackwardForMillisecTimer < millisec)
  {
    lp->backward();
    rp->backward();
  }
}

void motors::moveBackwardEveryMillisec(int milliSecond){
  if(millis() - moveBackwardEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < 1000; i++){
      moveBackward();
    }
    halt();
    moveBackwardEveryMillisecTimer = millis();
  }
}




void motors::turnLeft(){
  lp->backward();
  rp->forward();
}

void motors::turnLeft(int inputValue){
  lp->backward(inputValue);
  rp->forward(inputValue);
}

void motors::turnLeftEveryMillisec(int milliSecond){
  if(millis() - turnLeftEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < 1000; i++){
      this->turnLeft();
    }
    this->halt();
    turnLeftEveryMillisecTimer = millis();
  }
}

void motors::turnRight(){
  lp->forward();
  rp->backward();
}

void motors::turnRightEveryMillisec(int milliSecond){
  if(millis() - turnRightEveryMillisecTimer> milliSecond)
  {
    for (int i = 0; i < 1000; i++){
      this->turnRight();
    }
    this->halt();
    turnRightEveryMillisecTimer = millis();
  }
}

void motors::goRight(){
  rp->forward();
}

void motors::goLeft(){
  lp->forward();
}

void motors::goRight90(){

}

// whrite goLeft90function and turnLeftSelMillisecfunction
void motors::goLeft90(){
  while (millisec) {
    lp->backward();
    rp->forward();
  }
  wheel->halt();
}

void motors::turnLeftSelMillisec(int millisec){
  while (millisec) {
    lp->backward();
    rp->forward();
  }
  wheel->halt();
}

void motors::halt(){
  lp->halt();
  rp->halt();
}

void motors::haltQuick(){
  lp->haltQuick();
  rp->haltQuick();
}