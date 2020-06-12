#pragma once
#include <memory>
#include "MachineMessage.h"



class MachineControl
{
protected:
	MachineControl() = default;
public:
	virtual ~MachineControl() = default;
	MachineControl& operator=(const MachineControl &) = delete;
	MachineControl(const MachineControl &) = delete;

public:
	virtual void sendMessage(const MachineMessage& message) = 0;
	virtual void pushMessage(PtrMachineMessage message) = 0;
};

using PtrMachineControl = std::unique_ptr<MachineControl>;
