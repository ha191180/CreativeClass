#ifndef LINETRACESENSORS_H_INCLUDE
#define LINETRACESENSORS_H_INCLUDE
#include "./linetraceSensor.hpp"

class linetraceSensors{
	private:
		linetraceSensor *rrp;
		linetraceSensor *rcp;
		linetraceSensor *lcp;
		linetraceSensor *llp;
    byte val;
	public:
		linetraceSensors(int rrPinInput, 
													int rcPinInput,
													int lcPinInput,
													int llPinInput);
		void reload();
    byte get();
};

#endif // !LINETRACESENSORS_H_INCLUDE
