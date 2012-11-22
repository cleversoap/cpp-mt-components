#ifndef __MTCOMPONENT_H__
#define __MTCOMPONENT_H__

#include <thread>
#include <string>

using namespace std;

class MTComponent
{
	public:
		MTComponent(const string &name)
		: _active(false), _name(name)
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

		string getName()
		{
			return _name;
		}

	protected:
		bool _active;
		thread _thread;
		string _name;
		void run()
		{
			_active = true;
			while (_active)
			{
				//cout << getName() << endl;
			}
		}
};

#endif
