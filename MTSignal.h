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

#ifndef __MTSIGNAL_H__
#define __MTSIGNAL_H__

#include <vector>
#include <functional>

using namespace std;
using namespace std::placeholders;

template<typename...T>
class MTSignal
{
	typedef function<void(T...)> vft;	
	typedef void (*mft) (T...);

	public:
		MTSignal(){}

		// Call the operator as you normally would with parameters
		// as the type templating has already been done
		// This will iterate over each slot and call it with the passed params.
		void operator() (T... args)
		{
			for(auto i = _slots.begin(); i != _slots.end(); ++i)
			{
				(*i)(args...);
			}
		}

		// Connect a slot function that returns void and matches the
		// signal delegate. Note that a slot can be added more than once
		// and will therefore be called more than once.
		void connect(vft slf)
		{
			_slots.push_back(slf);
		}

		// Remove a slot function from being called.
		void remove(vft slf)
		{
			for(auto i = _slots.begin(); i != _slots.end(); ++i)
			{
				if (slf.template target<mft*>() == static_cast<vft>(*i).template target<mft*>())
				{
					_slots.erase(i);
				}
			}
		}

	protected:
		// Vector of all slot functions
		vector<vft> _slots;
};

template<>
class MTSignal<>
{
	typedef function<void()> vft; 

	public:
		MTSignal(){}

		void operator()()
		{
			for(auto i = _slots.begin(); i < _slots.end(); ++i)
			{
				(*i)();
			}
		}

		void connect(vft slf)
		{
			_slots.push_back(slf);
		}

		void remove(vft slf)
		{
			for(auto i = _slots.begin(); i < _slots.end(); ++i)
			{
				if ((*i).target<void()>() == slf.target<void()>())
				{
					_slots.erase(i);
				}
			}
		}

	protected:
		vector<vft> _slots;

};

#endif
