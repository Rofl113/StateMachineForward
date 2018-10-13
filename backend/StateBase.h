#pragma once
#include "MachineBase.h"
#include "StateControl.h"

namespace StateMachineForward
{

class StateMachineControl;

class StateBase : public MachineBase, public StateControl
{
private:
	template < class T = StateBase>
	class MessageSwitchState: private MessageSwitchChild
	{
	public:
		MessageSwitchState(const MachineControl* machine) : m_machine(machine) {}
		virtual ~MessageSwitchState() override = default;
	private:
		virtual PtrMachineMessage createChild() const override
		{
			return { new T() };
		}
		virtual const MachineControl* getMachineMsg() const override
		{
			return m_machine;
		}

		const MachineControl* m_machine;
	};
protected:
	virtual bool handleMessage(const MachineMessage& message) override;

protected:
	StateBase() = default;
	virtual ~StateBase() override = default;
	template < class T = StateMachineControl>
	void switchStateMachine(std::shared_ptr<T> stateMachine)
	{
		switchChild(std::move(stateMachine));
	}
	template < class T = StateBase>
	PtrMachineMessage CREATE_MESSAGE_SWITCH_STATE()
	{
		return { new MessageSwitchState<T>(this)};
	}

private:
	virtual bool _handleParent(const MachineMessage& message) override;
};

} // end namespace StateMachineForward
