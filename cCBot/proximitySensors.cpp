#include "Arduino.h"
#include "./proximitySensors.hpp"

proximitySensors::proximitySensors(int rPinInput,
                                   int cPinInput,
                                   int lPinInput){
  rp = new proximitySensor(rPinInput);
  lp = new proximitySensor(lPinInput);
  cp = new proximitySensor(cPinInput);
}


void proximitySensors::reload(){
  rp->reload();
  lp->reload();
  cp->reload();
}

void proximitySensors::reload(bool resetFlag){
  rp->reload(resetFlag);
  lp->reload(resetFlag);
  cp->reload(resetFlag);
}


bool proximitySensors::isObjDetected(){
  if (abs(lp->get() - rp->get()) < OBJSIZE && abs(lp->get() - cp->get()) < OBJSIZE && abs(cp->get() - rp->get()) < OBJSIZE && lp->get() < 100 && cp->get() < 100 && rp ->get() < 100){
    return true;
  }
  else return false;
}

bool proximitySensors::isObjTouched(){
  if (getLeftValue() < 10 && getRightValue() < 10 && getCenterValue() < 10){
    return true;
  }
  else return false;
}

bool proximitySensors::isAimLeft(){
  return (lp->get() - rp->get() > 100.0);
}

bool proximitySensors::isAimRight(){
  return (rp->get() - lp->get() > 100.0);
}



double proximitySensors::getLeftValue(){
  return (lp->get());
}

double proximitySensors::getCenterValue(){
  return (cp->get());
}

double proximitySensors::getRightValue(){
  return (rp->get());
}

double proximitySensors::getLeftPreviousValue(){
  return (lp->getPrevious());
}

double proximitySensors::getCenterPreviousValue(){
  return (cp->getPrevious());
}

double proximitySensors::getRightPreviousValue(){
  return (rp->getPrevious());
}

double proximitySensors::getDiffDistance(){
  double totalDistance = 0;
  totalDistance += this->getLeftValue() - this->getLeftPreviousValue();
  totalDistance += this->getCenterValue() - this->getCenterPreviousValue();
  totalDistance += this->getRightValue() - this->getRightPreviousValue();
  return totalDistance;
}