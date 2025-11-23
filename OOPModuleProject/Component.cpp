#include "Component.h"
#include "GameMediator.h"

Component::Component() : visible(false)
{
}

void Component::setVisible(bool newVisible)
{
	this->visible = newVisible;
}
