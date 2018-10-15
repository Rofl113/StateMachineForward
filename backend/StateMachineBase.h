#pragma once
#include "MachineBase.h"
#include "StateMachineControl.h"
#include "MachineAction.h"


namespace StateMachineForward
{

class StateBase;

class StateMachineBase : public MachineBase, public StateMachineControl
{
protected:
	StateMachineBase() = default;

public:
	virtual ~StateMachineBase() override = default;

private:
	using TypeFuncCreateSm = std::function<StateMachineBase*()>;
	class MachineActionSwitchStateMachine: public MessageSwitchChild
	{
	public:
		MachineActionSwitchStateMachine(TypeFuncCreateSm&& func);
		virtual ~MachineActionSwitchStateMachine() override = default;
	private:
		virtual std::unique_ptr<MachineControl> createChild() const override;
		const TypeFuncCreateSm m_func;
	};

protected:
	virtual PtrMachineAction handleMessage(const MachineMessage& message) override;

	PtrMachineAction createActionSwitchStateMachine(TypeFuncCreateSm&& func);
	void setState(std::unique_ptr<StateBase>&& state);

private:
	virtual PtrMachineAction _handleParent(const MachineMessage& message) override;
};

} // end namespace StateMachineForward
