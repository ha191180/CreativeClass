#ifndef MOTOR_H_INCLUDE
#define MOTOR_H_INCLUDE

class motor{
  private:
    int _revPin;
    int _pwmPin;
    const int DEFAULTVALUE = 100; // 0 -255
    double bias = 1;
    int rotateDirection = 0;
  public:
    void forward();
    void forward(int inputValue);
    void backward();
    void backward(int inputValue);
    motor(int revPinInput, int pwmPinInput);
    void setBias(double inputBias);
    void halt();
    void halt(bool rotateDirectionRecording);
    void haltQuick();
};

#endif // !MOTOR_H_INCLUDE
