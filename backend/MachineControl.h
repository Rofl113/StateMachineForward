#pragma once
#include "MachineMessage.h"
#include "NonAssignable.h"
#include "NonCopyable.h"
#include <memory>


namespace StateMachineForward
{

class ManagerMessagesControl;

class MachineControl: private NonAssignable, private NonCopyable
{
public:
	MachineControl() = default;
	virtual ~MachineControl() = default;
	virtual void sendMessage(const MachineMessage& message) = 0;
	virtual void setManager(ManagerMessagesControl* manager) = 0;
};

using PtrMachineControl = std::unique_ptr<MachineControl>;

} // end namespace StateMachineForward
