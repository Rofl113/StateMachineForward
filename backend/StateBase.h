#pragma once
#include "MachineBase.h"
#include "StateControl.h"
#include "MachineAction.h"

namespace StateMachineForward
{

class StateMachineBase;

class StateBase : public MachineBase, public StateControl
{
	using ClassBase = MachineBase;
protected:
	StateBase() = default;

public:
	virtual ~StateBase() override = default;

	using TypeFuncCreateSm = std::function<StateMachineBase*()>;

	PtrMachineAction createActionSwitchSm(TypeFuncCreateSm&& func) const;
	PtrMachineAction createActionPushSm(TypeFuncCreateSm&& func) const;
	PtrMachineAction createActionPopSm(StateMachineBase* sm) const;

	template<typename TState, typename ... TArgs>
	PtrMachineAction createActionSwitchSm(TArgs&& ... args) const
	{
		auto func = [args...] () -> StateMachineBase*
		{
			return { new TState(std::forward<TArgs>(args)...) };
		};
		return this->createActionSwitchSm(std::move(func));
	}

	template<typename TState, typename ... TArgs>
	PtrMachineAction createActionPushSm(TArgs&& ... args) const
	{
		auto func = [args...] () -> StateMachineBase*
		{
			return { new TState(std::forward<TArgs>(args)...) };
		};
		return this->createActionSwitchSm(std::move(func));
	}

protected:
	virtual PtrMachineAction handleEnter() override;
	virtual PtrMachineAction handleMessage(const MachineMessage& message) override;
	virtual PtrMachineAction handleExit() override;

	const StateMachineBase* getParent() const;

private:
	virtual PtrMachineAction _handleEnter() override;
	virtual PtrMachineAction _handleMessage(const MachineMessage& message) override;
	virtual PtrMachineAction _handleExit() override;

	virtual bool processAction(const MachineAction* action) override;
};

} // end namespace StateMachineForward
