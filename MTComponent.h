#ifndef __MTCOMPONENT_H__
#define __MTCOMPONENT_H__

#include <thread>

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

	protected:
		bool _active;
		thread _thread;
		void run()
		{
			_active = true;
			while (_active)
			{
			}
		}
};

#endif
