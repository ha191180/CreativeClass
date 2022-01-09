#ifndef PROXIMITYSENSOR_H_INCLUDE
#define PROXIMITYSENSOR_H_INCLUDE

#include "Queue.h"

class proximitySensor{
  private:
    double val;
    double previousVal;
    int _pin;
    int queueSize = 1000;
    Queue<int> dataQueue;
    unsigned long sumVoltage = 0;
  public:
    void reload();
    void reload(bool resetFlag);
    double get();
    double getPrevious();
    proximitySensor(int pin);
};



#endif // !PROXIMITYSENSOR_H_INCLUDE
