#pragma once
#include <stack>
#include <memory>
#include "MachineControl.h"
#include "MachineAction.h"



namespace StateMachineForward
{

class ManagerMessagesControl;
class MachineAction;

class MachineBase : public MachineControl
{
protected:
	MachineBase() = default;
	virtual ~MachineBase() override = default;

	class MachineActionDontNext: public MachineAction {};

	PtrMachineAction createActionDontNext() const;
	PtrMachineAction createActionNext() const;

	virtual std::unique_ptr<MachineAction> _handleEnter() = 0;
	virtual std::unique_ptr<MachineAction> _handleMessage(const MachineMessage& message) = 0;
	virtual std::unique_ptr<MachineAction> _handleExit() = 0;

	const MachineControl* _getChild() const;
	MachineControl* _getChild();
	void _pushChild(std::unique_ptr<MachineControl>&& child);
	std::unique_ptr<MachineControl> _popChild();

	const MachineControl* _getParent() const;

	virtual bool processAction(const MachineAction* action);

private:
	virtual void sendMessage(const MachineMessage& message) override;
	virtual void pushMessage(PtrMachineMessage message) override;

	std::unique_ptr<MachineAction> _handleEnterFull();
	std::unique_ptr<MachineAction> _handleMessageFull(const MachineMessage& message);
	std::unique_ptr<MachineAction> _handleExitFull();

	void setParent(MachineControl* parent);

	// root
	MachineControl* m_parent = nullptr;
	// childs
	std::stack<std::unique_ptr<MachineControl>> m_childs;
};

} // end namespace StateMachineForward
