#include "body.hpp"

body robot;

void Debug() {
  robot.debug();
}

void Test() {
  robot.test();
  robot.haltForever();
}

/////////////////////////////////////////

void Main() {
  robot.sumo();
  robot.swmode();
  robot.hilldown();
  robot.lineTrace();
  robot.haltForever();
}

void setup(){
  robot.setup();
  // Serial.begin(9600);
}

void loop(){
  // Test();
  Main();
  // Debug();
}


////////////////////////////////////////
