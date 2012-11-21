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

		MTSignal<> start;
		MTSignal<> stop;

	protected:
		vector<MTComponent*> _components;
};

#endif
