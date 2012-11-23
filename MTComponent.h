/*
* Copyright (c) 2012 Cleversoap
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/
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
