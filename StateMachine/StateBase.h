#pragma once
#include "MachineBase.h"
#include "StateControl.h"
#include "MachineAction.h"


class StateMachineControl;

class StateBase : public MachineBase, public StateControl
{
	using ClassBase = MachineBase;
protected:
	StateBase() = default;

public:
	virtual ~StateBase() override = default;

protected:
	virtual PtrMachineAction handleEnter();
	virtual PtrMachineAction handleMessage(const MachineMessage& message);
	virtual PtrMachineAction handleExit();
	virtual bool processAction(const MachineAction* action);

protected:
	virtual PtrMachineAction createActionCreateSmFunc(TypeFuncCreateSm&& func) const override final;
	virtual PtrMachineAction createActionResetSm(StateMachineBase* sm) const override final;

protected:
	template<typename TState, typename ... TArgs>
	void createSm(TArgs&& ... args)
	{
		static_assert (std::is_base_of<StateMachineBase, TState>().value, "Bad Type StateMachine!");
		this->resetSm();
		this->_pushChild(std::unique_ptr<MachineControl>{ new TState(std::forward<TArgs>(args)...) });
	}
	void resetSm();

protected:
	const StateMachineControl* getParent() const;

private:
	virtual PtrMachineAction _handleEnter() override final;
	virtual PtrMachineAction _handleMessage(const MachineMessage& message) override final;
	virtual PtrMachineAction _handleExit() override final;
	virtual bool _processAction(const MachineAction& action) override final;

private: // Move to Private
	const MachineControl* _getChild() const;
	MachineControl* _getChild();
	void _pushChild(std::unique_ptr<MachineControl>&& child);
	std::unique_ptr<MachineControl> _popChild();
	const MachineControl* _getParent() const;
};
