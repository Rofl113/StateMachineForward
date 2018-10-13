#include <iostream>
#include "StateMachineBase.h"
#include "ManagerMessages.h"


using namespace StateMachineForward;

class MachineMessageHello : public MachineMessage
{
public:
	MachineMessageHello(std::string name)
		: m_name(name)
	{

	}
	virtual ~MachineMessageHello() override {}
	static PtrMachineMessage create(std::string name)
	{
		return PtrMachineMessage(new MachineMessageHello(name));
	}

	const std::string m_name;
};

class StateMachineHello : public StateMachineBase
{
protected:
	virtual bool handleMessage(const MachineMessage& message) override
	{
		if (auto msg = message.cast<MachineMessageHello>())
		{
			std::cout << msg->m_name << "= Hello!" << std::endl;
			return true;
		}
		return false;
	}
};

int main(int argc, char *argv[])
{
	std::shared_ptr<ManagerMessagesControl> manager;
	{
		auto mana = new ManagerMessages;
		if (!mana)
		{
			return -1;
		}
		manager = std::shared_ptr<ManagerMessagesControl>(mana);
		mana = nullptr;
	}

	std::shared_ptr<MachineControl> machine;
	{
		auto mach = new StateMachineHello;
		if (!mach)
		{
			return -2;
		}
		machine = std::shared_ptr<MachineControl>(mach);
		mach = nullptr;
	}

	std::cout << "Example One" << std::endl;
	manager->setMachineRoot(nullptr);
	machine->sendMessage(MachineMessageHello("machine->sendMessage (AfterSetRoot)"));
	manager->pushMessages(MachineMessageHello::create("manager->sendMessage (AfterSetRoot)"));
	manager->setMachineRoot(machine.get());
	machine->sendMessage(MachineMessageHello("machine->sendMessage (BeforeSetRoot)"));
	manager->pushMessages(MachineMessageHello::create("manager->sendMessage (BeforeSetRoot)"));
	manager->processMessages();

	std::cout << "\nExample Two" << std::endl;
	manager->setMachineRoot(nullptr);
	machine->sendMessage(MachineMessageHello("machine->sendMessage (AfterSetRoot)"));
	manager->pushMessages(MachineMessageHello::create("manager->sendMessage (AfterSetRoot)"));
	manager->processMessages();
	manager->setMachineRoot(machine.get());
	machine->sendMessage(MachineMessageHello("machine->sendMessage (BeforeSetRoot)"));
	manager->pushMessages(MachineMessageHello::create("manager->sendMessage (BeforeSetRoot)"));
	manager->processMessages();

	return 0;
}
