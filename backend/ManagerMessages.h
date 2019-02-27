#pragma once
#include <queue>
#include "MachineBase.h"
#include "ManagerMessagesControl.h"


namespace StateMachineForward
{

// Менеджер Сообщений
class ManagerMessages : public MachineBase, public ManagerMessagesControl
{
public:
	explicit ManagerMessages();
	virtual ~ManagerMessages() override;

	virtual void setMachine(std::unique_ptr<MachineControl>&& machine) override;
	virtual bool pushMessages(PtrMachineMessage&& msg) override;
	virtual bool processMessages() override;

private:
	virtual std::unique_ptr<MachineAction> _handleEnter() override;
	virtual std::unique_ptr<MachineAction> _handleMessage(const MachineMessage& message) override;
	virtual std::unique_ptr<MachineAction> _handleExit() override;

	std::queue<PtrMachineMessage> m_msgQueue;
};

} // end namespace StateMachineForward
