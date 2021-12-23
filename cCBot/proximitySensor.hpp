#ifndef PROXIMITYSENSOR_H_INCLUDE
#define PROXIMITYSENSOR_H_INCLUDE

class proximitySensor{
  private:
    double val;
    double previousVal;
    int _pin;
    const int th = 150;
  public:
    void reload();
    double get();
    double getPrevious();
    proximitySensor(int pin);
};



#endif // !PROXIMITYSENSOR_H_INCLUDE
