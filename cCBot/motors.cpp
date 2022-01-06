#include "Arduino.h"
#include "motors.hpp"

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
    moveForward();
    moveForwardEveryMillisecTimer = millis();
  }
}

void motors::moveBackward(){
  lp->backward();
  rp->backward();
}

void motors::moveBackwardForSec(int second){
  moveBackwardForSecTimer = millis();
  while (millis() - moveBackwardForSecTimer < second * 1000)
  {
    lp->backward();
    rp->backward();
  }
}

void motors::turnLeft(){
  lp->backward();
  rp->forward();
}

void motors::turnLeftEveryMillisec(int milliSecond){
  if(millis() - turnLeftEveryMillisecTimer > milliSecond)
  {
    turnLeft();
    turnLeftEveryMillisecTimer = millis();
  }
}

void motors::turnRight(){
  lp->forward();
  rp->backward();
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
