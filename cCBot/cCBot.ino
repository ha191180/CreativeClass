#include "body.hpp"

enum modes {
  mSumo,
  mSwitch,
  mBrake,
  mTrace
};

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
  enum modes runMode = mSumo;
  robot.sumo();
  while (true);
}

void setup(){
  robot.setup();
  Serial.begin(9600);
}

void loop(){
  //Test();
  //Main();
  //Debug();
}


////////////////////////////////////////
