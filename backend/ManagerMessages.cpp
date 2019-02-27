#include "ManagerMessages.h"
#include "MachineControl.h"


namespace StateMachineForward
{

ManagerMessages::ManagerMessages()
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

	if (auto m = this->_getChild())
	{
		while (not empty.empty())
		{
			const auto message = std::move(empty.front());
			empty.pop();
			m->pushMessage(message);
		}
		return true;
	}
	return false;
}

std::unique_ptr<MachineAction> ManagerMessages::_handleEnter()
{
	return this->createActionNext();
}

std::unique_ptr<MachineAction> ManagerMessages::_handleMessage(const MachineMessage& /*message*/)
{
	return this->createActionNext();
}

std::unique_ptr<MachineAction> ManagerMessages::_handleExit()
{
	return this->createActionNext();
}

void ManagerMessages::setMachine(std::unique_ptr<MachineControl>&& machine)
{
	this->_popChild();
	this->_pushChild(std::move(machine));
}

} // end namespace StateMachineForward
