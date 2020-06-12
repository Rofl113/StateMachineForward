#pragma once
#include <functional>
#include "MachineMessage.h"
#include "MachineAction.h"

class StateBase;

class StateMachineControl
{
protected:
	StateMachineControl() = default;

public:
	virtual ~StateMachineControl() = default;
	StateMachineControl(const StateMachineControl &) = delete;
	StateMachineControl& operator=(const StateMachineControl &) = delete;

public:
	using TypeFuncCreateState = std::function<StateBase*()>;

public:
	virtual PtrMachineAction createActionPopState(StateBase* state) const = 0;

public:
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
