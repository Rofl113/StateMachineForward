#include "StateBase.h"
#include "StateMachineBase.h"



namespace
{
	class MachineActionCreateSm : public MachineAction
	{
	public:
		MachineActionCreateSm() = delete;
		MachineActionCreateSm(StateBase::TypeFuncCreateSm&& func) : m_func(func) {}
		const StateBase::TypeFuncCreateSm m_func;
	};

	class MachineActionResetSm : public MachineAction
	{
	public:
		MachineActionResetSm() = delete;
		MachineActionResetSm(StateMachineBase* sm) : m_sm(sm) {}
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
	if (const auto actionSwitch = dynamic_cast<const MachineActionCreateSm*>(&action))
	{
		this->resetSm();
		this->_pushChild(std::unique_ptr<MachineControl>(actionSwitch->m_func()));
		return true;
	}
	else if (const auto actionPop = dynamic_cast<const MachineActionResetSm*>(&action))
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

PtrMachineAction StateBase::createActionCreateSmFunc(StateControl::TypeFuncCreateSm&& func) const
{
	return PtrMachineAction{ new MachineActionCreateSm(std::move(func)) };
}

PtrMachineAction StateBase::createActionResetSm(StateMachineBase* sm) const
{
	return PtrMachineAction{ new MachineActionResetSm(sm) };
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
