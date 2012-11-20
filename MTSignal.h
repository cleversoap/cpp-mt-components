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

		void operator() (T... args)
		{
			for(int i = 0; i < slots.size(); ++i)
			{
				slots.at(i)(args...);
			}
		}	

		vector<void (*) (T...)> slots;
};

#endif
