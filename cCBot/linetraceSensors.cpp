#include "Arduino.h"
#include "./linetraceSensors.hpp"

linetraceSensors::linetraceSensors(int rrPinInput,
																	 int rcPinInput, 
																	 int lcPinInput, 
																	 int llPinInput) {
  rrp = new linetraceSensor(rrPinInput);
  rcp = new linetraceSensor(rcPinInput);
  lcp = new linetraceSensor(lcPinInput);
  llp = new linetraceSensor(llPinInput);
}

void linetraceSensors::reload(){
  llp->reload();
  lcp->reload();
  rcp->reload();
  rrp->reload();
	val =  ((llp->get() << 3) + (lcp->get() << 2) + (rcp->get() << 1) + (rrp->get() << 0));
}

byte linetraceSensors::get(){
  return val;
}
