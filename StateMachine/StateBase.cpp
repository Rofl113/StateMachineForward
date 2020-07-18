#include "StateBase.h"
#include "StateMachineBase.h"



namespace
{
	class MachineActionSwitchSm : public MachineAction
	{
	public:
		MachineActionSwitchSm() = delete;
		MachineActionSwitchSm(StateBase::TypeFuncCreateSm&& func) : m_func(func) {}
		const StateBase::TypeFuncCreateSm m_func;
	};

	class MachineActionPushSm : public MachineAction
	{
	public:
		MachineActionPushSm() = delete;
		MachineActionPushSm(StateBase::TypeFuncCreateSm&& func) : m_func(func) {}
		const StateBase::TypeFuncCreateSm m_func;
	};

	class MachineActionPopSm : public MachineAction
	{
	public:
		MachineActionPopSm() = delete;
		MachineActionPopSm(StateMachineBase* sm) : m_sm(sm) {}
		const StateMachineBase* m_sm = nullptr;
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

void StateBase::resetSm()
{
	this->_popChild();
}

const StateMachineControl* StateBase::getParent() const
{
	return dynamic_cast<const StateMachineControl*>(this->_getParent());
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

bool StateBase::_processAction(const MachineAction& action)
{
	if (const auto actionSwitch = dynamic_cast<const MachineActionSwitchSm*>(&action))
	{
		this->_popChild();
		this->_pushChild(std::unique_ptr<MachineControl>(actionSwitch->m_func()));
		return true;
	}
	else if (const auto actionPush = dynamic_cast<const MachineActionPushSm*>(&action))
	{
		this->_pushChild(std::unique_ptr<MachineControl>(actionPush->m_func()));
		return true;
	}
	else if (const auto actionPop = dynamic_cast<const MachineActionPopSm*>(&action))
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

const MachineControl* StateBase::_getChild() const
{
	return ClassBase::_getChild();
}

MachineControl* StateBase::_getChild()
{
	return ClassBase::_getChild();
}

void StateBase::_pushChild(std::unique_ptr<MachineControl>&& child)
{
	ClassBase::_pushChild(std::move(child));
}

std::unique_ptr<MachineControl> StateBase::_popChild()
{
	return ClassBase::_popChild();
}

const MachineControl* StateBase::_getParent() const
{
	return ClassBase::_getParent();
}
