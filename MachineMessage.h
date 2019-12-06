#pragma once

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
