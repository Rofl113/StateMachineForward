#include "StateBase.h"
#include "StateMachineBase.h"



namespace
{
	class MachineActionSwitchSm : public MachineAction
	{
	public:
		MachineActionSwitchSm(StateBase::TypeFuncCreateSm&& func) : m_func(func) {}
		const StateBase::TypeFuncCreateSm m_func;
	};

	class MachineActionPushSm : public MachineAction
	{
	public:
		MachineActionPushSm(StateBase::TypeFuncCreateSm&& func) : m_func(func) {}
		const StateBase::TypeFuncCreateSm m_func;
	};

	class MachineActionPopSm : public MachineAction
	{
	public:
		MachineActionPopSm(StateMachineBase* sm) : m_sm(sm) {}
		const StateMachineBase* m_sm;
	};
} // end namespace

PtrMachineAction StateBase::handleEnter()
{
	return this->createActionNext();
}

PtrMachineAction StateBase::handleMessage(const MachineMessage& /*message*/)
{
	return this->createActionNext();
}

PtrMachineAction StateBase::handleExit()
{
	return this->createActionNext();
}

PtrMachineAction StateBase::createActionSwitchSmFunc(StateBase::TypeFuncCreateSm&& func) const
{
	return PtrMachineAction{ new MachineActionSwitchSm(std::move(func)) };
}

PtrMachineAction StateBase::createActionPushSmFunc(StateBase::TypeFuncCreateSm&& func) const
{
	return PtrMachineAction{ new MachineActionPushSm(std::move(func)) };
}

PtrMachineAction StateBase::createActionPopSm(StateMachineBase* sm) const
{
	return PtrMachineAction{ new MachineActionPopSm(sm) };
}

const StateMachineControl* StateBase::getParent() const
{
	return this->_getParent()->cast<StateMachineControl>();
}

PtrMachineAction StateBase::_handleEnter()
{
	return this->handleEnter();
}

PtrMachineAction StateBase::_handleMessage(const MachineMessage& message)
{
	return this->handleMessage(message);
}

PtrMachineAction StateBase::_handleExit()
{
	return this->handleExit();
}

bool StateBase::_processAction(const MachineAction* action)
{
	if (const auto actionSwitch = action->cast<MachineActionSwitchSm>())
	{
		this->_popChild();
		this->_pushChild(std::unique_ptr<MachineControl>(actionSwitch->m_func()));
		return true;
	}
	else if (const auto actionPush = action->cast<MachineActionPushSm>())
	{
		this->_pushChild(std::unique_ptr<MachineControl>(actionPush->m_func()));
		return true;
	}
	else if (const auto actionPop = action->cast<MachineActionPopSm>())
	{
		if (this->_getChild() == actionPop->m_sm)
		{
			this->_popChild();
		}
		return true;
	}
	return ClassBase::_processAction(action);
}

bool StateBase::processAction(const MachineAction* /*action*/)
{
	return false;
}
