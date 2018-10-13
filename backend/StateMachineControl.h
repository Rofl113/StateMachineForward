#pragma once
#include "MachineMessage.h"
#include "NonAssignable.h"
#include "NonCopyable.h"

namespace StateMachineForward
{

class StateMachineControl: private NonAssignable, private NonCopyable
{
protected:
	StateMachineControl() = default;
	virtual ~StateMachineControl() = default;
	virtual bool handleMessage(const MachineMessage& message) = 0;
};

} // end namespace StateMachineForward
