#pragma once
#include "MachineBase.h"
#include "StateMachineControl.h"
#include "MachineAction.h"


namespace StateMachineForward
{

class StateControl;

class StateMachineBase : public MachineBase, public StateMachineControl
{
	using ClassBase = MachineBase;
protected:
	StateMachineBase() = default;

public:
	virtual ~StateMachineBase() override = default;

protected:
	virtual PtrMachineAction createActionSwitchStateFunc(TypeFuncCreateState&& func) const override;
	virtual PtrMachineAction createActionPushStateFunc(TypeFuncCreateState&& func) const override;
	virtual PtrMachineAction createActionPopState(StateBase* state) const override;

	virtual PtrMachineAction handleEnter();
	virtual PtrMachineAction handleMessage(const MachineMessage& message);
	virtual PtrMachineAction handleExit();

	const StateControl* getParent() const;

private:
	virtual PtrMachineAction _handleEnter() override;
	virtual PtrMachineAction _handleMessage(const MachineMessage& message) override;
	virtual PtrMachineAction _handleExit() override;

	virtual bool processAction(const MachineAction* action) override;
};

} // end namespace StateMachineForward
