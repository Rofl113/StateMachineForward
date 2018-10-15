#include "MachineBase.h"
#include "ManagerMessagesControl.h"
#include "MachineAction.h"
#include <iostream>


namespace StateMachineForward
{

PtrMachineAction MachineBase::createActionDontNext() const
{
	return PtrMachineAction(new MachineActionDontNext());
}

PtrMachineAction MachineBase::createActionNext() const
{
	return {};
}

void MachineBase::_setChild(std::unique_ptr<MachineControl>&& child)
{
	this->m_child.reset();
	if (child)
	{
		this->m_child = std::move(child);
		if (auto childCurrent = m_child.get())
		{
			if (auto ch = dynamic_cast<MachineBase*>(childCurrent))
			{
				ch->setManager(m_manager);
			}
		}
	}
}

void MachineBase::sendMessage(const MachineMessage& message)
{
	const auto action = this->_handleParent(message);
	if (action)
	{
		if (action->cast<MachineActionDontNext>())
		{
			return;
		}
		else if (const auto actionSwitch = action->cast<MessageSwitchChild>())
		{
			std::cout << "CHECK MessageSwitchChild" << std::endl;
			this->_setChild({});
			std::cout << "CHILD NULL" << std::endl;
			this->_setChild(actionSwitch->createChild());
			std::cout << "CHILD SET" << std::endl;
		}
	}
	if (m_child)
	{
		auto child = dynamic_cast<MachineBase*>(m_child.get());
		if (child)
		{
			return child->sendMessage(message);
		}
	}
}

void MachineBase::setManager(ManagerMessagesControl* manager)
{
	if (manager != m_manager)
	{
		m_manager = manager;
		if (m_manager)
		{
			m_manager->setMachineRoot(this);
		}
	}
}

std::unique_ptr<MachineControl> MachineBase::MessageSwitchChild::createChild() const
{
	return nullptr;
}

} // end namespace StateMachineForward
