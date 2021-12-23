#ifndef LINETRACESENSORS_H_INCLUDE
#define LINETRACESENSORS_H_INCLUDE
#include "linetraceSensor.hpp"

class linetraceSensors{
	private:
		linetraceSensor *rrp;
		linetraceSensor *rcp;
		linetraceSensor *lcp;
		linetraceSensor *llp;
    char val;
	public:
		linetraceSensors(int rrPinInput, 
													int rcPinInput,
													int lcPinInput,
													int llPinInput);
		void reload();
    char get();
};

#endif // !LINETRACESENSORS_H_INCLUDE
