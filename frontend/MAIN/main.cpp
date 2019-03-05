#include <iostream>
#include "StateMachineBase.h"
#include "StateBase.h"
#include "ManagerMessages.h"


using namespace StateMachineForward;

class MessageSwitch: public MachineMessage
{
public:
	MessageSwitch(std::string name)
		: m_name(name)
	{

	}
	virtual ~MessageSwitch() override {}
	static PtrMachineMessage create(std::string name)
	{
		return PtrMachineMessage(new MessageSwitch(name));
	}

	const std::string m_name;
};

class StateB: public StateBase
{
public:
	StateB()
		: StateBase()
	{
		printf("CREATE class StateB\n");
	}
	virtual ~StateB() override
	{
		printf("DELETE class StateB\n");
	}
};

class StateA: public StateBase
{
public:
	StateA()
		: StateBase()
	{
		printf("CREATE class StateA\n");
	}
	virtual ~StateA() override
	{
		printf("DELETE class StateA\n");
	}
protected:
	virtual PtrMachineAction handleMessage(const MachineMessage& message) override
	{
		if (const auto msg = message.cast<MessageSwitch>())
		{
			std::cout << "CHECK MessageSwitch: " << msg->m_name << std::endl;
			return this->getParent()->createActionSwitchState<StateB>();
		}
		return this->createActionNext();
	}
};

class StateMachineMain : public StateMachineBase
{
public:
	StateMachineMain()
		: StateMachineBase()
	{
	}
protected:
	virtual PtrMachineAction handleEnter() override
	{
		return this->createActionPushState<StateA>();
	}
	virtual PtrMachineAction handleMessage(const MachineMessage& /*message*/) override
	{
		return this->createActionNext();
	}
};

int main(int argc, char *argv[])
{
	printf("Example Start\n");
	{
		std::unique_ptr<ManagerMessagesControl> manager (new ManagerMessages());
		{
			std::unique_ptr<MachineControl> machine (new StateMachineMain());
			manager->setMachine(std::move(machine));
		}
		manager->pushMessages(MessageSwitch::create("manager->sendMessage (AfterSetRoot)"));
		manager->processMessages();
	}
	printf("Example Finish\n");

	return 0;
}
