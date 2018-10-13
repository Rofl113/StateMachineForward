#pragma once
#include "MachineMessage.h"
#include "NonAssignable.h"
#include "NonCopyable.h"

namespace StateMachineForward
{

class MachineControl;

// Менеджер Сообщений
class ManagerMessagesControl: private NonAssignable, private NonCopyable
{
public:
	ManagerMessagesControl() = default;
	virtual ~ManagerMessagesControl() = default;
	virtual bool pushMessages(PtrMachineMessage&& message) = 0;
	virtual bool processMessages() = 0;
	virtual void setMachineRoot(MachineControl* machine) = 0;
};

} // end namespace StateMachineForward
