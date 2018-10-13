#pragma once
#include "MachineMessage.h"
#include "NonAssignable.h"
#include "NonCopyable.h"

namespace StateMachineForward
{

class StateControl: private NonAssignable, private NonCopyable
{
protected:
	StateControl() = default;
	virtual ~StateControl() = default;
	virtual bool handleMessage(const MachineMessage& message) = 0;
};

} // end namespace StateMachineForward
