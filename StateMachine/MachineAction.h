#pragma once
#include <memory>


class MachineAction
{
public:
	virtual ~MachineAction() = default;
	MachineAction() = default;
	MachineAction& operator=(const MachineAction &) = delete;
	MachineAction(const MachineAction &) = delete;
};

using PtrMachineAction = std::unique_ptr<MachineAction>;
