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
	virtual PtrMachineAction createActionSwitchSmFunc(TypeFuncCreateSm&& func) const override;
	virtual PtrMachineAction createActionPushSmFunc(TypeFuncCreateSm&& func) const override;
	virtual PtrMachineAction createActionPopSm(StateMachineBase* sm) const override;

	virtual PtrMachineAction handleEnter();
	virtual PtrMachineAction handleMessage(const MachineMessage& message);
	virtual PtrMachineAction handleExit();
	virtual bool processAction(const MachineAction* action);

	const StateMachineControl* getParent() const;

private:
	virtual PtrMachineAction _handleEnter() override final;
	virtual PtrMachineAction _handleMessage(const MachineMessage& message) override final;
	virtual PtrMachineAction _handleExit() override final;

	virtual bool _processAction(const MachineAction& action) override final;
};
