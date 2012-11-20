#ifndef __MTSIGNAL_H__
#define __MTSIGNAL_H__

#include <vector>
#include <iostream>

using namespace std;

template<typename...T>
class MTSignal
{
	public:
		MTSignal()
		{
		}

		void operator() (...)
		{
			std::cout << "HELLO" << std::endl;
		}	
		vector<void (*) (T...)> slots;
};

#endif
