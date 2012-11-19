#include "MTComponent.h"


MTComponent::MTComponent()
: _componentActive(false)
{
	_thread = thread(&MTComponent::run, this);
}

MTComponent::~MTComponent()
{
}

bool MTComponent::isActive()
{
	return _componentActive;
}

void MTComponent::run()
{
	_componentActive = true;

	while(_componentActive)
	{
		_componentActive = false;
	}
}

