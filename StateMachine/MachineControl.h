#pragma once
#include "MachineMessage.h"
#include <memory>


using PtrMachineMessage = std::shared_ptr<const MachineMessage>;

class MachineControl
{
	MachineControl& operator=(const MachineControl &) = delete;
	MachineControl(const MachineControl &) = delete;
public:
	MachineControl() = default;
	virtual ~MachineControl() = default;

	virtual void sendMessage(const MachineMessage& message) = 0;
	virtual void pushMessage(PtrMachineMessage message) = 0;

	template<typename T>
	T* cast()
	{
		return dynamic_cast<T*>(this);
	}

	template<typename T>
	const T* cast() const
	{
		return dynamic_cast<const T*>(this);
	}
};

using PtrMachineControl = std::unique_ptr<MachineControl>;
