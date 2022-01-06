#ifndef MOTORS_H_INCLUDE
#define MOTORS_H_INCLUDE
#include "./motor.hpp"

class motors{
  private:
    motor *lp;
    motor *rp;
    unsigned long long moveBackwardForMillisecTimer = 0;
    unsigned long long moveBackwardEveryMillisecTimer = 0;
    unsigned long long moveForwardEveryMillisecTimer = 0;
    unsigned long long turnLeftEveryMillisecTimer = 0;
    unsigned long long turnRightEveryMillisecTimer = 0;
    
  public:
    motors(int lRevPinInput,
           int lPwmPinInput,
           int rRevPinInput,
           int rPwmPinInput);
    void moveForward();
    void moveForward(int inputValue);
    void moveForwardEveryMillisec(int millisec);
    void moveBackward();
    void moveBackwardForMillisec(int millisec);
    void moveBackwardEveryMillisec(int millisec);
    void turnRight();
    void turnRightEveryMillisec(int millisec);
    void turnLeft();
    void turnLeft(int inputValue);
    void turnLeftEveryMillisec(int millisec);
    void goRight();
    void goLeft();
    void goRight90();
    void halt();
    void haltQuick();
};


#endif // !MOTORS_H_INCLUDE
