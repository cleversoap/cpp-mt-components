#ifndef __MTCOMPONENT_H__
#define __MTCOMPONENT_H__

#include <thread>
#include <iostream>

using namespace std;

class MTComponent
{
	public:
		MTComponent()
		: _active(false)
		{
		}

		bool isActive()
		{
			return _active;
		}

		void start(void)
		{
			if (!_active)
			{
				_thread = thread(&MTComponent::run, this);
			}
		}

		void stop(void)
		{
			if (_active)
			{
				_active = false;
				_thread.join();
			}
		}

		void test(int x)
		{
			cout << "Testing..." << x << endl;
		}

	protected:
		bool _active;
		thread _thread;
		void run()
		{
			_active = true;
			while (_active)
			{
				cout << "HELLO" << endl;
				_active = false;
			}
		}
};

#endif
