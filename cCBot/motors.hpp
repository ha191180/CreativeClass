#ifndef MOTORS_H_INCLUDE
#define MOTORS_H_INCLUDE
#include "motor.hpp"

class motors{
  private:
    motor *lp;
    motor *rp;
    unsigned long long moveBackwardForSecTimer = 0;
    unsigned long long moveForwardEveryMillisecTimer = 0;
    unsigned long long turnLeftEveryMillisecTimer = 0;
    
  public:
    motors(int lRevPinInput,
           int lPwmPinInput,
           int rRevPinInput,
           int rPwmPinInput);
    void moveForward();
    void moveForward(int inputValue);
    void moveForwardEveryMillisec(int second);
    void moveBackward();
    void moveBackwardForSec(int second);
    void turnRight();
    void turnLeft();
    void turnLeftEveryMillisec(int second);
    void goRight();
    void goLeft();
    void goRight90();
};

#endif // !MOTORS_H_INCLUDE
