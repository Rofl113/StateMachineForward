#pragma once
#include "MachineBase.h"
#include "StateControl.h"
#include "MachineAction.h"

namespace StateMachineForward
{

class StateMachineControl;

class StateBase : public MachineBase, public StateControl
{
	using ClassBase = MachineBase;
protected:
	StateBase() = default;

public:
	virtual ~StateBase() override = default;

protected:
	virtual PtrMachineAction createActionSwitchSmFunc(TypeFuncCreateSm&& func) const override;
	virtual PtrMachineAction createActionPushSmFunc(TypeFuncCreateSm&& func) const override;
	virtual PtrMachineAction createActionPopSm(StateMachineBase* sm) const override;

	virtual PtrMachineAction handleEnter();
	virtual PtrMachineAction handleMessage(const MachineMessage& message);
	virtual PtrMachineAction handleExit();

	const StateMachineControl* getParent() const;

private:
	virtual PtrMachineAction _handleEnter() override;
	virtual PtrMachineAction _handleMessage(const MachineMessage& message) override;
	virtual PtrMachineAction _handleExit() override;

	virtual bool processAction(const MachineAction* action) override;
};

} // end namespace StateMachineForward
