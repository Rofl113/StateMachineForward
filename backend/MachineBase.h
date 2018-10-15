#pragma once
#include <memory>
#include "MachineControl.h"
#include "NonAssignable.h"
#include "NonCopyable.h"
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

	class MessageSwitchChild : public MachineAction
	{
		friend class MachineBase;
	protected:
		MessageSwitchChild() = default;
		virtual ~MessageSwitchChild() override = default;
		virtual std::unique_ptr<MachineControl> createChild() const;
	};

	PtrMachineAction createActionDontNext() const;
	PtrMachineAction createActionNext() const;

	virtual std::unique_ptr<MachineAction> _handleParent(const MachineMessage& message) = 0;

	const MachineControl* _getChild() const;
	void _setChild(std::unique_ptr<MachineControl>&& child);

private:
	virtual void sendMessage(const MachineMessage& message) override;
	virtual void setManager(ManagerMessagesControl* manager) override;

	// root or manager
	ManagerMessagesControl* m_manager = nullptr;
	std::unique_ptr<MachineControl> m_child;
};

} // end namespace StateMachineForward
