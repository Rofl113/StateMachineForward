#include "StateMachineBase.h"


namespace StateMachineForward
{

bool StateMachineBase::handleMessage(const MachineMessage& /*message*/)
{
	return false;
}

bool StateMachineBase::_handleParent(const MachineMessage& message)
{
	return this->handleMessage(message);
}

} // end namespace StateMachineForward
