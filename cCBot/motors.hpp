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
    unsigned long long curveRightEveryMillisecTimer = 0;
    
  public:
    motors(int lRevPinInput,
           int lPwmPinInput,
           int rRevPinInput,
           int rPwmPinInput);
    void moveForward();
    void moveForward(int inputValue);
    void moveForwardEveryMillisec(int millisec);
    void moveForwardEveryMillisec(int millisec, int powerLevel); // powerLevel: 1-3 are recommended
    void moveBackward();
    void moveBackwardForMillisec(int millisec);
    void moveBackwardEveryMillisec(int millisec);
    void moveBackwardEveryMillisec(int millisec, int powerLevel); // powerLevel: 1-3 are recommended
    void turnRight();
    void turnRight(int inputValue);
    void turnRightEveryMillisec(int millisec);
    void turnRightEveryMillisec(int millisec, int powerLevel); // powerLevel: 1-3 are recommended
    void turnRight180();
    void turnLeft();
    void turnLeft(int inputValue);
    void turnLeftEveryMillisec(int millisec);
    void turnLeftEveryMillisec(int millisec, int powerLevel); // powerLevel: 1-3 are recommended
    void turnLeftSelMillisec(int millisec);
    void goRight();
    void goLeft();
    void goRight90();
    void goLeft90();
    void curveRightEveryMillisec(int millisec);
    void curveRightEveryMillisec(int millisec, int powerLevel);
    void curveRightEveryMillisec(int millisec, int powerLevel, int curveRate);
    void halt();
    void halt(bool RotateDirectionRecording);
    void haltQuick();
    void punch();
};


#endif // !MOTORS_H_INCLUDE
