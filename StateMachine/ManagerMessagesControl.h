#pragma once
#include <memory>
#include "MachineMessage.h"

class MachineControl;


// Менеджер Сообщений
class ManagerMessagesControl
{
public:
	virtual ~ManagerMessagesControl() = default;
	ManagerMessagesControl() = default;
	ManagerMessagesControl& operator=(const ManagerMessagesControl &) = delete;
	ManagerMessagesControl(const ManagerMessagesControl &) = delete;

public:
	virtual void setMachine(std::unique_ptr<MachineControl>&& machine) = 0;
	virtual bool pushMessages(PtrMachineMessage&& msg) = 0;
	virtual bool processMessages() = 0;
};
