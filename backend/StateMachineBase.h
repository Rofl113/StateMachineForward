#pragma once
#include "MachineBase.h"
#include "StateMachineControl.h"
#include "MachineAction.h"


namespace StateMachineForward
{

class StateBase;

class StateMachineBase : public MachineBase, public StateMachineControl
{
	using ClassBase = MachineBase;
protected:
	StateMachineBase() = default;

public:
	virtual ~StateMachineBase() override = default;

	using TypeFuncCreateState = std::function<StateBase*()>;

	PtrMachineAction createActionSwitchState(TypeFuncCreateState&& func) const;
	PtrMachineAction createActionPushState(TypeFuncCreateState&& func) const;
	PtrMachineAction createActionPopState(StateBase* state) const;

	template<typename TState, typename ... TArgs>
	PtrMachineAction createActionSwitchState(TArgs&& ... args) const
	{
		auto func = [args...] () -> StateBase*
		{
			return { new TState(std::forward<TArgs>(args)...) };
		};
		return this->createActionSwitchState(std::move(func));
	}

	template<typename TState, typename ... TArgs>
	PtrMachineAction createActionPushState(TArgs&& ... args) const
	{
		auto func = [args...] () -> StateBase*
		{
			return { new TState(std::forward<TArgs>(args)...) };
		};
		return this->createActionPushState(std::move(func));
	}

protected:
	virtual PtrMachineAction handleEnter() override;
	virtual PtrMachineAction handleMessage(const MachineMessage& message) override;
	virtual PtrMachineAction handleExit() override;

	const StateBase* getParent() const;

private:
	virtual PtrMachineAction _handleEnter() override;
	virtual PtrMachineAction _handleMessage(const MachineMessage& message) override;
	virtual PtrMachineAction _handleExit() override;

	virtual bool processAction(const MachineAction* action) override;
};

} // end namespace StateMachineForward
