#ifndef LINETRACESENSOR_H_INCLUDE
#define LINETRACESENSOR_H_INCLUDE

class linetraceSensor{
	private:
		bool val; 
		int _pin;
	public:
    bool get(); 
		void reload(); // 0 white
		linetraceSensor(int pin);
};

#endif // !LINETRACESENSOR_H_INCLUDE
