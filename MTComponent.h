#ifndef __MTCOMPONENT_H__
#define __MTCOMPONENT_H__

#include <thread>
#include <functional>

using namespace std;

class MTComponent
{
	public:
		MTComponent();
		virtual ~MTComponent();
		bool isActive();
		void kill();	

	protected:
		bool _componentActive;
		thread _thread;
		void run();
};

#endif
