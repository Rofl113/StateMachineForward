#include "StateBase.h"
#include "StateMachineBase.h"


namespace StateMachineForward
{

std::unique_ptr<MachineAction> StateBase::handleMessage(const MachineMessage& /*message*/)
{
	return {};
}

PtrMachineAction StateBase::createActionSwitchState(StateBase::TypeFuncCreateState&& func)
{
	return PtrMachineAction{ new MachineActionSwitchState(std::move(func)) };
}

void StateBase::setStateMachine(std::unique_ptr<StateMachineBase>&& sm)
{
	std::unique_ptr<MachineControl> smControl { sm.get() };
	sm = nullptr;
	this->_setChild(std::move(smControl));
}

std::unique_ptr<MachineAction> StateBase::_handleParent(const MachineMessage& message)
{
	return this->handleMessage(message);
}

StateBase::MachineActionSwitchState::MachineActionSwitchState(StateBase::TypeFuncCreateState&& func)
	: m_func (func)
{}

std::unique_ptr<MachineControl> StateBase::MachineActionSwitchState::createChild() const
{
	return std::unique_ptr<MachineControl>{ this->m_func() };
}

} // end namespace StateMachineForward
