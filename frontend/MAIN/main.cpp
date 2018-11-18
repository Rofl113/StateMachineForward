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
			return this->createActionSwitchState([] { return new StateB(); });
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
		this->setState(std::unique_ptr<StateBase>{new StateA()});
	}
protected:
	virtual PtrMachineAction handleMessage(const MachineMessage& message) override
	{
		return this->createActionNext();
	}
};

int main(int argc, char *argv[])
{
	std::unique_ptr<ManagerMessagesControl> manager (new ManagerMessages());
	std::unique_ptr<MachineControl> machine (new StateMachineMain());

	std::cout << "Example Start" << std::endl;
	manager->setMachineRoot(machine.get());
	manager->pushMessages(MessageSwitch::create("manager->sendMessage (AfterSetRoot)"));
	manager->processMessages();
	machine->sendMessage(MessageSwitch("manager->sendMessage (AfterSetRoot)"));
	std::cout << "Example Finish" << std::endl;

	return 0;
}
