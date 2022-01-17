#include "Arduino.h"
#include "./motors.hpp"

motors::motors(int lRevPinInput,
               int lPwmPinInput,
               int rRevPinInput,
               int rPwmPinInput){
  lp = new motor(lRevPinInput, lPwmPinInput);
  rp = new motor(rRevPinInput, rPwmPinInput);
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
    for (int i = 0; i < 500; i++){
      moveForward();
    }
    halt(false);
    moveForwardEveryMillisecTimer = millis();
  }
}

void motors::moveForwardEveryMillisec(int milliSecond, int moveTime){
  if(millis() - moveForwardEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < moveTime * 500; i++){
      moveForward();
    }
    halt(false);
    moveForwardEveryMillisecTimer = millis();
  }
}

void motors::moveForwardForMillisec(int millisec){
  unsigned long moveForwardForMillisecTimer = millis();
  while(millis() - moveForwardForMillisecTimer < millisec){
    lp->forward();
    rp->forward();
  }
  this->halt();
}

void motors::moveForwardForMillisec(int millisec, int powerLevel){
  unsigned long moveForwardForMillisecTimer = millis();
  while(millis() - moveForwardForMillisecTimer < millisec){
    lp->forward(powerLevel);
    rp->forward(powerLevel);
  }
  this->halt();
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

void motors::moveBackwardForMillisec(int millisec, int powerLevel){ // powerLevel must be 0 - 255
  moveBackwardForMillisecTimer = millis();
  while (millis() - moveBackwardForMillisecTimer < millisec)
  {
    lp->backward(powerLevel);
    rp->backward(powerLevel);
  }
  this->halt();
}

void motors::moveBackwardEveryMillisec(int milliSecond){
  if(millis() - moveBackwardEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < 500; i++){
      moveBackward();
    }
    halt(false);
    moveBackwardEveryMillisecTimer = millis();
  }
}


void motors::moveBackwardEveryMillisec(int milliSecond, int moveTime){
  if(millis() - moveBackwardEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < moveTime * 500; i++){
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
    for (int i = 0; i < 250; i++){
      this->turnLeft();
    }
    this->halt(false);
    turnLeftEveryMillisecTimer = millis();
  }
}

void motors::turnLeftEveryMillisec(int milliSecond, int moveTime){
  if(millis() - turnLeftEveryMillisecTimer > milliSecond)
  {
    for (int i = 0; i < moveTime * 250; i++){
      this->turnLeft();
    }
    this->halt(false);
    turnLeftEveryMillisecTimer = millis();
  }
}

void motors::turnLeftForMillisec(int millisec){
  turnLeftForMillisecTimer = millis();
  while (millis() - turnLeftForMillisecTimer < millisec) {
    lp->backward();
    rp->forward();
  }
  halt();
}

void motors::turnLeftForMillisec(int millisec, int powerLevel){
  turnLeftForMillisecTimer = millis();
  while (millis() - turnLeftForMillisecTimer < millisec) {
    lp->backward(powerLevel);
    rp->forward(powerLevel);
  }
  halt();
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
    for (int i = 0; i < 250; i++){
      this->turnRight();
    }
    this->halt(false);
    turnRightEveryMillisecTimer = millis();
  }
}

void motors::turnRightEveryMillisec(int milliSecond, int moveTime){
  if(millis() - turnRightEveryMillisecTimer> milliSecond)
  {
    for (int i = 0; i < moveTime * 250; i++){
      this->turnRight();
    }
    this->halt(false);
    turnRightEveryMillisecTimer = millis();
  }
}

void motors::turnRightForMillisec(int millisec){
  turnRightForMillisecTimer = millis();
  while (millis() - turnRightForMillisecTimer < millisec) {
    rp->backward();
    lp->forward();
  }
  halt();
}

void motors::turnRightForMillisec(int millisec, int powerLevel){
  turnRightForMillisecTimer = millis();
  while (millis() - turnRightForMillisecTimer < millisec) {
    rp->backward(powerLevel);
    lp->forward(powerLevel);
  }
  halt();
}



void motors::turnRight180(){
  for (int i = 0; i < 10000; i++){
    this->turnRight();
  }
  this->haltQuick();
}


void motors::goRight(){
  lp->forward();
  rp->halt();
}

void motors::goRight(int powerLevel){
  lp->forward(powerLevel);
  rp->halt();
}

void motors::goRightForMillisec(int millisec){
  goRightForMillisecTimer = millis();
  while (millis() - goRightForMillisecTimer < millisec){
    this->goRight();
  }
  this->halt();
}

void motors::goRightForMillisec(int millisec, int powerLevel){
  goRightForMillisecTimer = millis();
  while (millis() - goRightForMillisecTimer < millisec){
    this->goRight(powerLevel);
  }
  this->halt();
}

void motors::goLeft(){
  rp->forward();
  lp->halt();
}

void motors::goLeft(int powerLevel){
  rp->forward(powerLevel);
  lp->halt();
}

void motors::goLeftForMillisec(int millisec){
  goLeftForMillisecTimer = millis();
  while (millis() - goLeftForMillisecTimer < millisec){
    this->goLeft();
  }
  this->halt();
}

void motors::goLeftForMillisec(int millisec, int powerLevel){
  goLeftForMillisecTimer = millis();
  while (millis() - goLeftForMillisecTimer < millisec){
    this->goLeft(powerLevel);
  }
  this->halt();
}

void motors::goRight90(){
  for(int i=0; i<18000; i++){
    goRight();
  }
  halt();
}

void motors::goLeft90(){
  for(int i=0; i<18000; i++){
    goLeft();
  }
  halt();
}

void motors::goLeftInverseEveryMillisec(int millisec){  
  if(millis() - goLeftInverseEveryMillisecTimer > millisec)
  {
    for (int i = 0; i < 250; i++){
      rp->backward();
      lp->halt();
    }
    this->halt(false);
    goLeftInverseEveryMillisecTimer = millis();
  }
}

void motors::goLeftInverseEveryMillisec(int millisec, int moveTime){  
  if(millis() - goLeftInverseEveryMillisecTimer > millisec)
  {
    for (int i = 0; i < moveTime * 250; i++){
      rp->backward();
      lp->halt();
    }
    this->halt(false);
    goLeftInverseEveryMillisecTimer = millis();
  }
}



void motors::curveRight(){
  rp -> forward(255/2);
  lp -> forward(255);
}

void motors::curveRight(int powerLevel){
  rp -> forward(powerLevel/2);
  lp -> forward(powerLevel);
}

void motors::curveRight(int powerLevel, int curveRate){
  rp -> forward(powerLevel - (curveRate * powerLevel / 100));
  lp -> forward(powerLevel);
}

void motors::curveRightEveryMillisec(int millisec){
  if(millis() - curveRightEveryMillisecTimer > millisec)
  {
    for (int i = 0; i < 250; i++){
      if (i < 250 / 2) rp->forward();
      else rp -> halt(false);
      lp -> forward();
    }
    this->halt(false);
    curveRightEveryMillisecTimer = millis();
  }
}

void motors::curveRightEveryMillisec(int millisec, int moveTime){
  if(millis() - curveRightEveryMillisecTimer > millisec)
  {
    for (int i = 0; i < moveTime * 250; i++){
      if (i < moveTime * 250 / 2) rp->forward();
      else rp->halt(false);
      lp -> forward();
    }
    this->halt(false);
    curveRightEveryMillisecTimer = millis();
  }
}

void motors::curveRightEveryMillisec(int millisec, int moveTime, int curveRate){
  if(millis() - curveRightEveryMillisecTimer > millisec)
  {
    for (int i = 0; i < moveTime * 250; i++){
      if (curveRate > 100) curveRate = 100;
      if (i < moveTime * 250 - (moveTime * curveRate*5/2) ) rp->forward();
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
  for (int i = 0; i < 4000; i++){
    this->moveForward();
  }
  this->halt();
}