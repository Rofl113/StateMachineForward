#include "StateMachineBase.h"
#include "StateBase.h"


namespace StateMachineForward
{

PtrMachineAction StateMachineBase::handleMessage(const MachineMessage& /*message*/)
{
	return {};
}

void StateMachineBase::setState(std::unique_ptr<StateBase>&& state)
{
	std::unique_ptr<MachineControl> stateControl = std::move(state);
	this->_setChild(std::move(stateControl));
}

PtrMachineAction StateMachineBase::createActionSwitchStateMachine(StateMachineBase::TypeFuncCreateSm&& func)
{
	return PtrMachineAction{ new MachineActionSwitchStateMachine(std::move(func)) };
}

PtrMachineAction StateMachineBase::_handleParent(const MachineMessage& message)
{
	return this->handleMessage(message);
}

StateMachineBase::MachineActionSwitchStateMachine::MachineActionSwitchStateMachine(StateMachineBase::TypeFuncCreateSm&& func)
	: m_func(func)
{

}

std::unique_ptr<MachineControl> StateMachineBase::MachineActionSwitchStateMachine::createChild() const
{
	return std::unique_ptr<MachineControl>{ m_func() };
}

} // end namespace StateMachineForward
