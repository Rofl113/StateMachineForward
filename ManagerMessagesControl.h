#pragma once
#include "MachineMessage.h"
#include <memory>

class MachineControl;

using PtrMachineMessage = std::shared_ptr<const MachineMessage>;

// Менеджер Сообщений
class ManagerMessagesControl
{
	ManagerMessagesControl& operator=(const ManagerMessagesControl &) = delete;
	ManagerMessagesControl(const ManagerMessagesControl &) = delete;
public:
	ManagerMessagesControl() = default;
	virtual ~ManagerMessagesControl() = default;

	virtual void setMachine(std::unique_ptr<MachineControl>&& machine) = 0;
	virtual bool pushMessages(PtrMachineMessage&& msg) = 0;
	virtual bool processMessages() = 0;
};
