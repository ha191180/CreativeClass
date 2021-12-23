#include "Arduino.h"
#include "motor.hpp"

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
  digitalWrite(_revPin, LOW);
  analogWrite(_pwmPin, int(DEFAULTVALUE*bias));
}

void motor::forward(int inputValue){
  digitalWrite(_revPin, LOW);
  analogWrite(_pwmPin, int(inputValue*bias));
}

void motor::backward(){
  digitalWrite(_revPin, HIGH);
  analogWrite(_pwmPin, int(DEFAULTVALUE*bias));
}

void motor::backward(int inputValue){
  digitalWrite(_revPin, HIGH);
  analogWrite(_pwmPin, int(inputValue*bias));
}

void motor::setBias(double inputBias){
  bias = inputBias;
}
