#pragma once
#include "MachineBase.h"
#include "StateControl.h"
#include "MachineAction.h"

namespace StateMachineForward
{

class StateMachineBase;

class StateBase : public MachineBase, public StateControl
{
protected:
	StateBase() = default;

public:
	virtual ~StateBase() override = default;

private:
	using TypeFuncCreateState = std::function<StateBase*()>;
	class MachineActionSwitchState: public MessageSwitchChild
	{
	public:
		MachineActionSwitchState(TypeFuncCreateState&& func);
		virtual ~MachineActionSwitchState() override = default;
	private:
		virtual std::unique_ptr<MachineControl> createChild() const override;
		const TypeFuncCreateState m_func;
	};
protected:
	virtual PtrMachineAction handleMessage(const MachineMessage& message) override;

protected:
	PtrMachineAction createActionSwitchState(TypeFuncCreateState&& func);
	void setStateMachine(std::unique_ptr<StateMachineBase>&& sm);

private:
	virtual std::unique_ptr<MachineAction> _handleParent(const MachineMessage& message) override;
};

} // end namespace StateMachineForward
