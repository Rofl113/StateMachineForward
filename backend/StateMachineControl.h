#pragma once
#include "MachineMessage.h"
#include "MachineAction.h"

namespace StateMachineForward
{

class StateMachineControl
{
	StateMachineControl& operator=(const StateMachineControl &) = delete;
	StateMachineControl(const StateMachineControl &) = delete;
protected:
	StateMachineControl() = default;
	virtual ~StateMachineControl() = default;
	virtual PtrMachineAction handleEnter() = 0;
	virtual PtrMachineAction handleMessage(const MachineMessage& message) = 0;
	virtual PtrMachineAction handleExit() = 0;
};

} // end namespace StateMachineForward
