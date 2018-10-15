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
		: StateBase() {
		std::cout << "CREATE class StateB" << std::endl;
	}
	~StateB() {
		std::cout << "DELETE class StateB" << std::endl;
	}
};

class StateA: public StateBase
{
public:
	StateA()
		: StateBase() {
		std::cout << "CREATE class StateA" << std::endl;
	}
	~StateA() {
		std::cout << "DELETE class StateA" << std::endl;
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
	std::unique_ptr<ManagerMessagesControl> manager;
	{
		auto mana = new ManagerMessages;
		if (!mana)
		{
			return -1;
		}
		manager = std::unique_ptr<ManagerMessagesControl>(mana);
		mana = nullptr;
	}

	std::unique_ptr<MachineControl> machine;
	{
		auto mach = new StateMachineMain();
		if (!mach)
		{
			return -2;
		}
		machine = std::unique_ptr<MachineControl>(mach);
		mach = nullptr;
	}

	std::cout << "Example Start" << std::endl;
	manager->setMachineRoot(machine.get());
	manager->pushMessages(MessageSwitch::create("manager->sendMessage (AfterSetRoot)"));
	manager->processMessages();
	std::cout << "Example Finish" << std::endl;

	return 0;
}
