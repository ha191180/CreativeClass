#include "body.hpp"

enum modes {
  mSumo,
  mSwitch,
  mBrake,
  mTrace
};

body robot;

void Main() {
	enum modes runMode = mSumo;
  robot.sumo();
  
}

void setup(){
  robot.setup();
  Serial.begin(9600);
}

void loop(){
  Main();
}
