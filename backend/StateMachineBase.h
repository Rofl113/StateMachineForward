#pragma once
#include "MachineBase.h"
#include "StateMachineControl.h"
#include "StateControl.h"


namespace StateMachineForward
{

class StateMachineBase : public MachineBase, public StateMachineControl
{
protected:
	StateMachineBase() = default;
	virtual ~StateMachineBase() override = default;
	virtual bool handleMessage(const MachineMessage& message) override;

	template < class T = StateControl>
	void switchState(T* state)
	{
		_switchChild(std::move(state));
	}

private:
	virtual bool _handleParent(const MachineMessage& message) override;
};

} // end namespace StateMachineForward
