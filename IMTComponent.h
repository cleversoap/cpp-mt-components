#ifndef __IMTCOMPONENT_H__
#define __IMTCOMPONENT_H__

#include <thread>
#include <functional>

using namespace std;

class IMTComponent
{
	public:
		IMTComponent();
		virtual ~IMTComponent();
	
	protected:
		bool _componentActive;
		thread _thread;
		
};

#endif
