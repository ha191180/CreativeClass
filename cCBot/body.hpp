#ifndef BODY_H_INCLUDE
#define BODY_H_INCLUDE
#include "linetraceSensors.hpp"
#include "proximitySensors.hpp"
#include "motors.hpp"



class body {
	public:
		void setup(); // setup for arduino.
		void debug(); // output the essential values to serial out.
		void sumo(); // do sumo.
		void swmode(); // switch modes.
		void hilldown(); // down the hill.
		void lineTrace(); // do line trace.
    void test();
		void haltForever();


	private:
		// VARIABLE ///////////////////////////////////////////////////////////////////////
		// Pin for left motor
		const int lMotorPwmPin = 10;
		const int lMotorRevPin = 12;

		// Pin for right motor
		const int rMotorPwmPin = 9;
		const int rMotorRevPin = 8;

		// Pin for linetrace sensor
		const int rrTraceSensorPin = 2; // Right Right
		const int rcTraceSensorPin = 3; // Right Center
		const int lcTraceSensorPin = 4; // Left Center
		const int llTraceSensorPin = 5; // Left Left

		// Pin for proximity sensor
		const int lProxSensorPin = A0; // Left
		const int cProxSensorPin = A1; // Center
		const int rProxSensorPin = A2; // Right

   
   // Motors
    motors *wheel;

		// Structure of Sensors
		linetraceSensors *ltSens;

		proximitySensors *proxSens;

		// debug 
		bool isDebugEnabled = false;
		unsigned long previousTime = 0;
		
		// FUNCTION //////////////////////////////////////////////////////////////////////
		// functinos for sumo
		bool isObjDetected(); // return boolean value. true: a object is detected, false: else.
		bool isObjDisappeared(); //return boolean value. true: a object is dropped from the field.
		bool isEdge(); //return boolean value. true: a object is dropped from the field.
		int pushObj();

		// debug
		void debugOut();
};


#endif // !BODY_H_INCLUDE
