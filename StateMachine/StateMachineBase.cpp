#include "StateMachineBase.h"
#include "StateBase.h"


namespace
{
	class MachineActionSwitchState : public MachineAction
	{
	public:
		MachineActionSwitchState(StateMachineBase::TypeFuncCreateState&& func) : m_func(func) {}
		const StateMachineBase::TypeFuncCreateState m_func;
	};

	class MachineActionPushState : public MachineAction
	{
	public:
		MachineActionPushState(StateMachineBase::TypeFuncCreateState&& func) : m_func(func) {}
		const StateMachineBase::TypeFuncCreateState m_func;
	};

	class MachineActionPopState : public MachineAction
	{
	public:
		MachineActionPopState(StateBase* state) : m_state(state) {}
		const StateBase* m_state;
	};
} // end namespace

PtrMachineAction StateMachineBase::handleEnter()
{
	return this->createActionNext();
}

PtrMachineAction StateMachineBase::handleMessage(const MachineMessage& /*message*/)
{
	return this->createActionNext();
}

PtrMachineAction StateMachineBase::handleExit()
{
	return this->createActionNext();
}

PtrMachineAction StateMachineBase::createActionSwitchStateFunc(StateMachineBase::TypeFuncCreateState&& func) const
{
	return PtrMachineAction{ new MachineActionSwitchState(std::move(func)) };
}

PtrMachineAction StateMachineBase::createActionPushStateFunc(StateMachineBase::TypeFuncCreateState&& func) const
{
	return PtrMachineAction{ new MachineActionPushState(std::move(func)) };
}

PtrMachineAction StateMachineBase::createActionPopState(StateBase* state) const
{
	return PtrMachineAction{ new MachineActionPopState(state) };
}

const StateControl* StateMachineBase::getParent() const
{
	return this->_getParent()->cast<StateControl>();
}

PtrMachineAction StateMachineBase::_handleEnter()
{
	return this->handleEnter();
}

PtrMachineAction StateMachineBase::_handleMessage(const MachineMessage& message)
{
	return this->handleMessage(message);
}

PtrMachineAction StateMachineBase::_handleExit()
{
	return this->handleExit();
}

bool StateMachineBase::_processAction(const MachineAction* action)
{
	if (const auto actionSwitch = action->cast<MachineActionSwitchState>())
	{
		this->_popChild();
		this->_pushChild(std::unique_ptr<MachineControl>(actionSwitch->m_func()));
		return true;
	}
	else if (const auto actionPush = action->cast<MachineActionPushState>())
	{
		this->_pushChild(std::unique_ptr<MachineControl>(actionPush->m_func()));
		return true;
	}
	else if (const auto actionPop = action->cast<MachineActionPopState>())
	{
		if (this->_getChild() == actionPop->m_state)
		{
			this->_popChild();
		}
		return true;
	}
	return ClassBase::_processAction(action);
}
