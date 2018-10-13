#include "StateBase.h"

namespace StateMachineForward
{

bool StateBase::handleMessage(const MachineMessage& message)
{
	return false;
}

bool StateBase::_handleParent(const MachineMessage& message)
{
	return this->handleMessage(message);
}

} // end namespace StateMachineForward
