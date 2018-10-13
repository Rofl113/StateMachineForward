#pragma once
#include <memory>
#include "MachineControl.h"



namespace StateMachineForward
{

class ManagerMessagesControl;


class MachineBase : public MachineControl
{
public:
	bool _handleMessage(const MachineMessage& message);

protected:
	MachineBase() = default;
	virtual ~MachineBase() override = default;

	class MessageSwitchChild : public MachineMessage
	{
		friend class StateMachineBase;
	protected:
		MessageSwitchChild() = default;
		virtual ~MessageSwitchChild() override = default;
		virtual PtrMachineMessage createChild() const;
		virtual const  MachineControl* getMachineMsg() const;
	};

	virtual bool _handleParent(const MachineMessage& message) = 0;
	template < class T = MachineBase>
	void _switchChild(T* child)
	{
		if (auto ch = dynamic_cast<MachineBase*>(child))
		{
			ch->setManager(m_manager);
		}
		m_child.reset(child);
	}
	const MachineControl* _getChild() const;

private:
	virtual void sendMessage(const MachineMessage& message) override;
	virtual void setManager(ManagerMessagesControl* manager) override;

	void _setManager(ManagerMessagesControl* manager);

	// root or manager
	ManagerMessagesControl* m_manager = nullptr;
	std::unique_ptr<MachineControl> m_child;
};

} // end namespace StateMachineForward
