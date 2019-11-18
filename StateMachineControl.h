#pragma once
#include "MachineMessage.h"
#include "MachineAction.h"

namespace StateMachineForward
{

class StateBase;

class StateMachineControl
{
	StateMachineControl& operator=(const StateMachineControl &) = delete;
	StateMachineControl(const StateMachineControl &) = delete;
protected:
	StateMachineControl() = default;
	virtual ~StateMachineControl() = default;

public:
	using TypeFuncCreateState = std::function<StateBase*()>;

	virtual PtrMachineAction createActionPopState(StateBase* state) const = 0;

	template<typename TState, typename ... TArgs>
	PtrMachineAction createActionSwitchState(TArgs&& ... args) const
	{
		auto func = [args...] () -> StateBase*
		{
			return { new TState(std::forward<TArgs>(args)...) };
		};
		return this->createActionSwitchStateFunc(std::move(func));
	}

	template<typename TState, typename ... TArgs>
	PtrMachineAction createActionPushState(TArgs&& ... args) const
	{
		auto func = [args...] () -> StateBase*
		{
			return { new TState(std::forward<TArgs>(args)...) };
		};
		return this->createActionPushStateFunc(std::move(func));
	}

protected:
	virtual PtrMachineAction createActionSwitchStateFunc(TypeFuncCreateState&& func) const = 0;
	virtual PtrMachineAction createActionPushStateFunc(TypeFuncCreateState&& func) const = 0;
};

} // end namespace StateMachineForward
