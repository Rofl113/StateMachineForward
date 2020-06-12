#pragma once
#include "MachineMessage.h"
#include <memory>
#include <functional>
#include "MachineAction.h"



class StateMachineBase;

class StateControl
{
protected:
	StateControl() = default;
public:
	virtual ~StateControl() = default;
	StateControl& operator=(const StateControl &) = delete;
	StateControl(const StateControl &) = delete;

public:
	using TypeFuncCreateSm = std::function<StateMachineBase*()>;

public:
	virtual PtrMachineAction createActionPopSm(StateMachineBase* sm) const = 0;

public:
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
