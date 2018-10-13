#include "MachineBase.h"
#include "ManagerMessagesControl.h"


namespace StateMachineForward
{

bool MachineBase::_handleMessage(const MachineMessage& message)
{
	if (true == this->_handleParent(message))
	{
		return true;
	}
	if (m_child)
	{
		auto child = dynamic_cast<MachineBase*>(m_child.get());
		if (child)
		{
			return child->_handleMessage(message);
		}
	}
	return false;
}

void MachineBase::sendMessage(const MachineMessage& message)
{
	this->_handleMessage(message);
}

void MachineBase::setManager(ManagerMessagesControl* manager)
{
	if (manager == m_manager)
	{
		return;
	}
	this->_setManager(manager);
}

void MachineBase::_setManager(ManagerMessagesControl* manager)
{
	m_manager = manager;
	if (m_manager)
	{
		m_manager->setMachineRoot(this);
	}
}

PtrMachineMessage MachineBase::MessageSwitchChild::createChild() const
{
	return nullptr;
}

const MachineControl* MachineBase::MessageSwitchChild::getMachineMsg() const
{
	return nullptr;
}

} // end namespace StateMachineForward
