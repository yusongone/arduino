#include <Arduino.h>

#ifndef RelayObj_h
#define RelayObj_h

class Relay{
	public:
		void opn();
		void close();
	private:
		int pin;
};

class RelayObj
{
	public:
		RelayObj();
		void createRelay(int* f);
	private:
		
};

#endif
