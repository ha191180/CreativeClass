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
}

/////////////////////////////////////////

void Main() {
  enum modes runMode = mSumo;
  robot.sumo();
  while (true);
}

void setup(){
  robot.setup();
}

void loop(){
  //Test();
  Main();
  //Debug();
}


////////////////////////////////////////
