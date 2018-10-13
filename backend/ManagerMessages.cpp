#include "ManagerMessages.h"
#include "MachineBase.h"

namespace StateMachineForward
{

ManagerMessages::ManagerMessages()
	: m_machineRoot(nullptr)
{

}
ManagerMessages::~ManagerMessages() {}

bool ManagerMessages::pushMessages(PtrMachineMessage&& msg)
{
	if (nullptr == msg)
	{
		return false;
	}
	m_msgQueue.push(std::move(msg));
	return true;
}

bool ManagerMessages::processMessages()
{
	std::queue<PtrMachineMessage> empty;
	std::swap(m_msgQueue, empty);

	if (nullptr == m_machineRoot)
	{
		return false;
	}

	while (not empty.empty())
	{
		const auto message = std::move(empty.front());
		empty.pop();
		m_machineRoot->sendMessage(*message.get());
	}

	return true;
}

void ManagerMessages::setMachineRoot(MachineControl* machine)
{
	if (machine == m_machineRoot)
	{
		return;
	}
	_setMachineRoot(machine);
}

void ManagerMessages::_setMachineRoot(MachineControl* machine)
{
	m_machineRoot = machine;
	if (m_machineRoot)
	{
		m_machineRoot->setManager(this);
	}
}

} // end namespace StateMachineForward
