#pragma once
#include <memory>

class MachineMessage
{
public:
	MachineMessage& operator=(const MachineMessage &) = delete;
	MachineMessage(const MachineMessage &) = delete;

	MachineMessage();
	virtual ~MachineMessage();
	template <typename T = MachineMessage>
	const T* cast() const {
		return dynamic_cast<const T*>(this);
	}
};



using PtrMachineMessage = std::shared_ptr<const MachineMessage>;
