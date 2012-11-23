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



// Variadic type parameters
template<typename...T>
class MTSignal
{
	// Types
	typedef function<void(T...)> vft;	
	typedef void (*mft) (T...);
	
	// Member Variables
	protected:
		vector<vft> _slots; // Slot functions container

	// Public Functions
	public:
		// Constructor
		MTSignal(){}

		// Call the operator as you normally would with parameters
		// as the type templating has already been done
		// This will iterate over each slot and call it with the passed params.
		void operator() (T... args)
		{
			for(auto i = _slots.begin(); i < _slots.end(); ++i)
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
			for(auto i = _slots.begin(); i < _slots.end(); ++i)
			{
				if (slf.template target<mft*>() == static_cast<vft>(*i).template target<mft*>())
				{
					_slots.erase(i);
				}
			}
		}


};

// No-parameter void signal template
template<>
class MTSignal<>
{
	// Types
	typedef function<void()> vft; 

	// Member Variables
	protected:
		vector<vft> _slots; // Slot functions container

	// Public Functions
	public:
		// Constructor
		MTSignal(){}

		// Empty operator as this type of signal will not have any args.
		void operator()()
		{
			for(auto i = _slots.begin(); i < _slots.end(); ++i)
			{
				(*i)();
			}
		}

		// Connect a slot to this signal.
		void connect(vft slf)
		{
			_slots.push_back(slf);
		}

		// Remove a slot from this signal.
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
};
#endif
