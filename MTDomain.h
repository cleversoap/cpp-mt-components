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
	public:
		MTDomain(){}

		void addComponent(MTComponent* component)
		{
			_components.push_back(component);
			start.connect(bind(&MTComponent::start,component));
			stop.connect(bind(&MTComponent::stop,component));
		}

		MTComponent* getComponent(const string &name)
		{
			for (auto i = _components.begin(); i < _components.end(); ++i)
			{
				if ((*i)->getName() == name)
				{
					return *i;
				}
			}

			return NULL;
		}

		void removeComponent(const string &name)
		{
			removeComponent(getComponent(name));
		}

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

		bool hasComponent(const string &name)
		{
			return getComponent(name) != NULL;
		}

		MTSignal<> start;
		MTSignal<> stop;

	protected:
		vector<MTComponent*> _components;
};

#endif
