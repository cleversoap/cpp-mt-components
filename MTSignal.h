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
#include <thread>

template<typename...T>
class MTSignal
{
	
	public:
		MTSignal(){}
		~MTSignal()
		{
			clear();
		}
	
		typedef std::function<void(T...)> SlotFunc;	
		typedef void (*SlotFuncDelegate) (T...);
	
		void operator() (T... args)
		{
			for(auto i = _slots.begin(); i < _slots.end(); ++i)
			{
				(*i)(args...);
				//std::thread(*i, args...).detach();
			}
		}

		void connect(SlotFunc slotFunc)
		{
			_slots.push_back(slotFunc);
		}

		void remove(SlotFunc slotFunc)
		{
			for(auto i = _slots.begin(); i < _slots.end(); ++i)
			{
				if (slotFunc.template target<SlotFuncDelegate*>() == static_cast<SlotFunc>(*i).template target<SlotFuncDelegate*>())
				{
					_slots.erase(i);
				}
			}
		}

		void clear()
		{
			_slots.clear();
		}

	protected:
		std::vector<SlotFunc> _slots; // Slot functions container
};
#endif
