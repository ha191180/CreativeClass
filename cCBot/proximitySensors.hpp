#ifndef PROXIMITYSENSORS_H_INCLUDE
#define PROXIMITYSENSORS_H_INCLUDE
#include "proximitySensor.hpp"

class proximitySensors{
  private:
    proximitySensor *rp;
    proximitySensor *lp;
    proximitySensor *cp;
    const double OBJSIZE = 10.0; // cm diameter
  public:
    void reload();
    proximitySensors(int rPinInput,
                     int cPinInput,
                     int lPinInput);
    bool isObjDetected();
    bool isAimLeft();
    bool isAimRight();
    double getLeftValue();
    double getCenterValue();
    double getRightValue();
    double getLeftPreviousValue();
    double getCenterPreviousValue();
    double getRightPreviousValue();
};



#endif // !PROXIMITYSENSORS_H_INCLUDE
