#pragma once
#include "NonAssignable.h"
#include "NonCopyable.h"

namespace StateMachineForward
{

class MachineMessage: private NonAssignable, private NonCopyable
{
public:
	MachineMessage();
	virtual ~MachineMessage() override;
	template <class T = MachineMessage>
	const T* cast() const {
		return dynamic_cast<const T*>(this);
	}
};

} // end namespace StateMachineForward
