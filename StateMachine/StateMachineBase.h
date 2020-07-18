#pragma once
#include "MachineBase.h"
#include "StateMachineControl.h"
#include "MachineAction.h"


class StateControl;

class StateMachineBase : public MachineBase, public StateMachineControl
{
	using ClassBase = MachineBase;
protected:
	StateMachineBase() = default;

public:
	virtual ~StateMachineBase() override = default;

protected:
	virtual PtrMachineAction handleEnter();
	virtual PtrMachineAction handleMessage(const MachineMessage& message);
	virtual PtrMachineAction handleExit();

protected:
	virtual PtrMachineAction createActionSwitchStateFunc(TypeFuncCreateState&& func) const override final;
	virtual PtrMachineAction createActionPushStateFunc(TypeFuncCreateState&& func) const override final;
	virtual PtrMachineAction createActionPopState(StateBase* state) const override final;

protected:
	template<typename TState, typename ... TArgs>
	void pushState(TArgs&& ... args)
	{
		static_assert (std::is_base_of<TState, StateBase>().value, "Bad Type State!");
		this->_pushChild({ new TState(std::forward<TArgs>(args)...) });
	}
	void popState();

protected:
	const StateControl* getParent() const;

private:
	virtual PtrMachineAction _handleEnter() override final;
	virtual PtrMachineAction _handleMessage(const MachineMessage& message) override final;
	virtual PtrMachineAction _handleExit() override final;
	virtual bool _processAction(const MachineAction& action) override final;

private: // Move to Private
	const MachineControl* _getChild() const;
	MachineControl* _getChild();
	void _pushChild(std::unique_ptr<MachineControl>&& child);
	std::unique_ptr<MachineControl> _popChild();
	const MachineControl* _getParent() const;
};
