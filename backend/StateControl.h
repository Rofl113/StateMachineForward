#pragma once
#include "MachineMessage.h"
#include "NonAssignable.h"
#include "NonCopyable.h"
#include <memory>
#include "MachineAction.h"

namespace StateMachineForward
{

class StateControl: private NonAssignable, private NonCopyable
{
protected:
	StateControl() = default;
	virtual ~StateControl() = default;
	virtual PtrMachineAction handleMessage(const MachineMessage& message) = 0;
};

} // end namespace StateMachineForward
