#pragma once
#include "MachineMessage.h"
#include "NonAssignable.h"
#include "NonCopyable.h"
#include "MachineAction.h"

namespace StateMachineForward
{

class StateMachineControl: private NonAssignable, private NonCopyable
{
protected:
	StateMachineControl() = default;
	virtual ~StateMachineControl() = default;
	virtual PtrMachineAction handleMessage(const MachineMessage& message) = 0;
};

} // end namespace StateMachineForward
