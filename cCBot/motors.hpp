#ifndef MOTORS_H_INCLUDE
#define MOTORS_H_INCLUDE
#include "./motor.hpp"

class motors{
  private:
    motor *lp;
    motor *rp;
    unsigned long moveBackwardForMillisecTimer = 0;
    unsigned long moveBackwardEveryMillisecTimer = 0;
    unsigned long moveForwardEveryMillisecTimer = 0;
    unsigned long turnLeftEveryMillisecTimer = 0;
    unsigned long turnLeftForMillisecTimer = 0;
    unsigned long turnRightEveryMillisecTimer = 0;
    unsigned long turnRightForMillisecTimer = 0;
    unsigned long goLeftInverseEveryMillisecTimer = 0;
    unsigned long curveRightEveryMillisecTimer = 0;
    
  public:
    motors(int lRevPinInput,
           int lPwmPinInput,
           int rRevPinInput,
           int rPwmPinInput);
    void moveForward();
    void moveForward(int inputValue);
    void moveForwardEveryMillisec(int millisec);
    void moveForwardEveryMillisec(int millisec, int moveTime); // moveTime: 1-3 are recommended
    void moveBackward();
    void moveBackwardForMillisec(int millisec);
    void moveBackwardForMillisec(int millisec, int powerLevel);
    void moveBackwardEveryMillisec(int millisec);
    void moveBackwardEveryMillisec(int millisec, int moveTime); // moveTime: 1-3 are recommended
    void turnRight();
    void turnRight(int inputValue);
    void turnRightEveryMillisec(int millisec);
    void turnRightEveryMillisec(int millisec, int moveTime); // moveTime: 1-3 are recommended
    void turnRight180();
    void turnLeft();
    void turnLeft(int inputValue);
    void turnLeftEveryMillisec(int millisec);
    void turnLeftEveryMillisec(int millisec, int moveTime); // moveTime: 1-3 are recommended
    void turnLeftForMillisec(int millisec);
    void turnLeftForMillisec(int millisec, int powerLevel);
    void turnRightForMillisec(int millisec);
    void turnRightForMillisec(int millisec, int powerLevel);
    void goRight();
    void goRight(int powerLevel);
    void goLeft();
    void goLeft(int powerLevel);
    void goRight90();
    void goLeft90();
    void goLeftInverseEveryMillisec(int millisec);
    void goLeftInverseEveryMillisec(int millisec, int moveTime);
    void curveRight();
    void curveRight(int powerLevel);
    void curveRight(int powerLevel, int curveRate);
    void curveRightEveryMillisec(int millisec);
    void curveRightEveryMillisec(int millisec, int moveTime);
    void curveRightEveryMillisec(int millisec, int moveTIme, int curveRate);
    void halt();
    void halt(bool RotateDirectionRecording);
    void haltQuick();
    void punch();
};


#endif // !MOTORS_H_INCLUDE
