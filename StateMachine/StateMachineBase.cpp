#include "StateMachineBase.h"
#include "StateBase.h"


namespace
{
	class MachineActionSwitchState : public MachineAction
	{
	public:
		MachineActionSwitchState() = delete;
		MachineActionSwitchState(StateMachineBase::TypeFuncCreateState&& func) : m_func(func) {}
		const StateMachineBase::TypeFuncCreateState m_func;
	};

	class MachineActionPushState : public MachineAction
	{
	public:
		MachineActionPushState() = delete;
		MachineActionPushState(StateMachineBase::TypeFuncCreateState&& func) : m_func(func) {}
		const StateMachineBase::TypeFuncCreateState m_func;
	};

	class MachineActionPopState : public MachineAction
	{
	public:
		MachineActionPopState() = delete;
		MachineActionPopState(StateBase* state) : m_state(state) {}
		const StateBase* m_state = nullptr;
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
	return dynamic_cast<const StateControl*>(this->_getParent());
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

bool StateMachineBase::_processAction(const MachineAction& action)
{
	if (const auto actionSwitch = dynamic_cast<const MachineActionSwitchState*>(&action))
	{
		this->_popChild();
		this->_pushChild(std::unique_ptr<MachineControl>(actionSwitch->m_func()));
		return true;
	}
	else if (const auto actionPush = dynamic_cast<const MachineActionPushState*>(&action))
	{
		this->_pushChild(std::unique_ptr<MachineControl>(actionPush->m_func()));
		return true;
	}
	else if (const auto actionPop = dynamic_cast<const MachineActionPopState*>(&action))
	{
		if (this->_getChild() == actionPop->m_state)
		{
			this->_popChild();
		}
		return true;
	}
	return ClassBase::_processAction(action);
}
