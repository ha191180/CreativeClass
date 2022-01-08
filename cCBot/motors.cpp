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
    halt(false);
    moveForwardEveryMillisecTimer = millis();
  }
}

void motors::moveForwardEveryMillisec(int milliSecond, int powerLevel){
  if(millis() - moveForwardEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < powerLevel * 1000; i++){
      moveForward();
    }
    halt(false);
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
  this->halt();
}

void motors::moveBackwardEveryMillisec(int milliSecond){
  if(millis() - moveBackwardEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < 1000; i++){
      moveBackward();
    }
    halt(false);
    moveBackwardEveryMillisecTimer = millis();
  }
}


void motors::moveBackwardEveryMillisec(int milliSecond, int powerLevel){
  if(millis() - moveBackwardEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < powerLevel * 1000; i++){
      moveBackward();
    }
    halt(false);
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
    for (int i = 0; i < 500; i++){
      this->turnLeft();
    }
    this->halt(false);
    turnLeftEveryMillisecTimer = millis();
  }
}

void motors::turnLeftEveryMillisec(int milliSecond, int powerLevel){
  if(millis() - turnLeftEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < powerLevel * 500; i++){
      this->turnLeft();
    }
    this->halt(false);
    turnLeftEveryMillisecTimer = millis();
  }
}


void motors::turnRight(){
  lp->forward();
  rp->backward();
}

void motors::turnRight(int inputValue){
  lp->forward(inputValue);
  rp->backward(inputValue);
}

void motors::turnRightEveryMillisec(int milliSecond){
  if(millis() - turnRightEveryMillisecTimer> milliSecond)
  {
    for (int i = 0; i < 500; i++){
      this->turnRight();
    }
    this->halt(false);
    turnRightEveryMillisecTimer = millis();
  }
}

void motors::turnRightEveryMillisec(int milliSecond, int powerLevel){
  if(millis() - turnRightEveryMillisecTimer> milliSecond)
  {
    for (int i = 0; i < powerLevel * 500; i++){
      this->turnRight();
    }
    this->halt(false);
    turnRightEveryMillisecTimer = millis();
  }
}

void motors::turnRight180(){
  for (int i = 0; i < 28000; i++){
    this->turnRight();
  }
  this->haltQuick();
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
  int millisec = 0;
  while (millisec) {
    lp->backward();
    rp->forward();
  }
  halt();
}

void motors::turnLeftSelMillisec(int millisec){
  while (millisec) {
    lp->backward();
    rp->forward();
  }
  halt();
}

void motors::curveRightEveryMillisec(int millisec){
  if(millis() - curveRightEveryMillisecTimer > millisec)
  {
    for (int i = 0; i < 500; i++){
      if (i < 500 / 2) rp->forward();
      else rp -> halt(false);
      lp -> forward();
    }
    this->halt(false);
    curveRightEveryMillisecTimer = millis();
  }
}

void motors::curveRightEveryMillisec(int millisec, int powerLevel){
  if(millis() - curveRightEveryMillisecTimer > millisec)
  {
    for (int i = 0; i < powerLevel * 500; i++){
      if (i < powerLevel * 500 / 2) rp->forward();
      else rp->halt(false);
      lp -> forward();
    }
    this->halt(false);
    curveRightEveryMillisecTimer = millis();
  }
}

void motors::curveRightEveryMillisec(int millisec, int powerLevel, int curveRate){
  if(millis() - curveRightEveryMillisecTimer > millisec)
  {
    for (int i = 0; i < powerLevel * 500; i++){
      if (curveRate > 100) curveRate = 100;
      if (i < powerLevel * 500 - (powerLevel * curveRate*5) ) rp->forward();
      else rp->halt(false);
      lp -> forward();
    }
    this->halt(false);
    curveRightEveryMillisecTimer = millis();
  }
}

void motors::halt(){
  lp->halt();
  rp->halt();
}

void motors::halt(bool RotateDirectionRecording){
  lp->halt(RotateDirectionRecording);
  rp->halt(RotateDirectionRecording);
}

void motors::haltQuick(){
  lp->haltQuick();
  rp->haltQuick();
}

void motors::punch(){
  for (int i = 0; i < 2000; i++){
    this->moveForward();
  }
  this->haltQuick();
}