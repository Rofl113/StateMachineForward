#pragma once
#include "MachineMessage.h"
#include <memory>
#include "MachineAction.h"

namespace StateMachineForward
{

class StateControl
{
	StateControl& operator=(const StateControl &) = delete;
	StateControl(const StateControl &) = delete;
protected:
	StateControl() = default;
	virtual ~StateControl() = default;
	virtual PtrMachineAction handleEnter() = 0;
	virtual PtrMachineAction handleMessage(const MachineMessage& message) = 0;
	virtual PtrMachineAction handleExit() = 0;
};

} // end namespace StateMachineForward
