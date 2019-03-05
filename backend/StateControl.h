#pragma once
#include "MachineMessage.h"
#include <memory>
#include "MachineAction.h"

namespace StateMachineForward
{

class StateMachineBase;

class StateControl
{
	StateControl& operator=(const StateControl &) = delete;
	StateControl(const StateControl &) = delete;
protected:
	StateControl() = default;
	virtual ~StateControl() = default;

public:
	using TypeFuncCreateSm = std::function<StateMachineBase*()>;

	virtual PtrMachineAction createActionPopSm(StateMachineBase* sm) const = 0;

	template<typename TState, typename ... TArgs>
	PtrMachineAction createActionSwitchSm(TArgs&& ... args) const
	{
		auto func = [args...] () -> StateMachineBase*
		{
			return { new TState(std::forward<TArgs>(args)...) };
		};
		return this->createActionSwitchSmFunc(std::move(func));
	}

	template<typename TState, typename ... TArgs>
	PtrMachineAction createActionPushSm(TArgs&& ... args) const
	{
		auto func = [args...] () -> StateMachineBase*
		{
			return { new TState(std::forward<TArgs>(args)...) };
		};
		return this->createActionPushSmFunc(std::move(func));
	}

protected:
	virtual PtrMachineAction createActionSwitchSmFunc(TypeFuncCreateSm&& func) const = 0;
	virtual PtrMachineAction createActionPushSmFunc(TypeFuncCreateSm&& func) const = 0;
};

} // end namespace StateMachineForward
