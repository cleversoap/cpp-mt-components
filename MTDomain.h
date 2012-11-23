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
#ifndef __MTDOMAIN_H__
#define __MTDOMAIN_H__

#include <vector>
#include <functional>

#include "MTComponent.h"
#include "MTSignal.h"

using namespace std;
using namespace std::placeholders;

class MTDomain
{
	// Signals
	public:
		MTSignal<> start;
		MTSignal<> stop;

	// Member Variables
	protected:
		vector<MTComponent*> _components;

	// Public Functions
	public:
		// Constructor
		MTDomain(){}

		// Variadic Constructor
		MTDomain(MTComponent* component, ...)
		{
			va_list ap;
			va_start(ap,component);
			// Iterate over the new components
			// until nullptr
			decltype(component) nc;
			while((nc = va_arg(ap,decltype(component))))
			{
				if (nc != nullptr)
				{
					addComponent(nc);
				}
				else
				{
					break;
				}	
			}
			va_end(ap);
			delete nc;
		}

		// Add a component and bind its slots to the start/stop signals
		// of the domain.
		void addComponent(MTComponent* component)
		{
			_components.push_back(component);
			start.connect(bind(&MTComponent::start,component));
			stop.connect(bind(&MTComponent::stop,component));
		}

		// Retrieves a component by matching the supplied string
		// to the getName() function of each component. This will
		// only match the first component with the name and will
		// not work if trying to retrieve multiple components.
		MTComponent* getComponent(const string &name)
		{
			for (auto i = _components.begin(); i < _components.end(); ++i)
			{
				if ((*i)->getName() == name)
				{
					return *i;
				}
			}

			return nullptr;
		}

		// Remove all components that match the supplied name.
		void removeComponent(const string &name)
		{
			removeComponent(getComponent(name));
		}

		// Remove all component entries that contain the supplied component
		void removeComponent(MTComponent* component)
		{
			for (auto i = _components.begin(); i < _components.end(); ++i)
			{
				if (*i == component)
				{
					_components.erase(i);
				}
			}
		}

		// Check if any components have the supplied name.
		bool hasComponent(const string &name)
		{
			return getComponent(name) != nullptr;
		}
};

#endif
