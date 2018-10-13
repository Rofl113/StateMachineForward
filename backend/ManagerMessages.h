#pragma once
#include <queue>
#include "ManagerMessagesControl.h"


namespace StateMachineForward
{

// Менеджер Сообщений
class ManagerMessages : public ManagerMessagesControl
{
public:
	explicit ManagerMessages();
	virtual ~ManagerMessages() override;
	virtual bool pushMessages(PtrMachineMessage&& msg) override;
	virtual bool processMessages() override;
	virtual void setMachineRoot(MachineControl* machine) override;

private:
	void _setMachineRoot(MachineControl* machine);

	std::queue<PtrMachineMessage> m_msgQueue;
	MachineControl* m_machineRoot;
};

} // end namespace StateMachineForward
