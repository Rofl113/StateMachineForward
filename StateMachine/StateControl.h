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
	virtual PtrMachineAction createActionResetSm(StateMachineBase* sm) const = 0;

public:
	template<typename TState, typename ... TArgs>
	PtrMachineAction createActionCreateSm(TArgs&& ... args) const
	{
		auto func = [args...] () -> StateMachineBase*
		{
			return { new TState(std::forward<TArgs>(args)...) };
		};
		return this->createActionCreateSmFunc(std::move(func));
	}

protected:
	virtual PtrMachineAction createActionCreateSmFunc(TypeFuncCreateSm&& func) const = 0;
};
