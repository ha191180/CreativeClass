#include "Arduino.h"
#include "./motor.hpp"

motor::motor(int revPinInput, int pwmPinInput){
  pinMode(revPinInput, OUTPUT);
  _revPin = revPinInput;
  _pwmPin = pwmPinInput;

  // inputスピードとの差分だけ全力加速入れたら良さそう。
  // 0-150 と 0-250 の場合は違うから。
}


// 170 lowspeed
// 180 mid speed 
// 15000 loop to kick
// 30000 loop to enough start


void motor::forward(){
  rotateDirection = 1;
  digitalWrite(_revPin, LOW);
  analogWrite(_pwmPin, int(DEFAULTVALUE*bias));
}

void motor::forward(int inputValue){
  rotateDirection = 1;
  digitalWrite(_revPin, LOW);
  analogWrite(_pwmPin, int(inputValue*bias));
}

void motor::backward(){
  rotateDirection = -1;
  digitalWrite(_revPin, HIGH);
  analogWrite(_pwmPin, int(DEFAULTVALUE*bias));
}

void motor::backward(int inputValue){
  /*
  if (rotateDirection != -1){
    for (int i = 0; i < 15000; i++){
      backward();
    }
    */
  rotateDirection = -1;
  digitalWrite(_revPin, HIGH);
  analogWrite(_pwmPin, int(inputValue*bias));
}

void motor::haltQuick(){
  if (rotateDirection == 1){
    for(int i = 0; i<5000; i++){
      backward();
    }
  }
  else if (rotateDirection == -1){
    for(int i = 0; i<5000; i++){
      forward();
    }
  }
  rotateDirection = 0;
  analogWrite(_pwmPin, 0);
}

void motor::halt(){
  rotateDirection = 0;
  analogWrite(_pwmPin, 0);
}


void motor::setBias(double inputBias){
  bias = inputBias;
}
