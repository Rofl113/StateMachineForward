#pragma once
#include "NonAssignable.h"
#include "NonCopyable.h"
#include <memory>


namespace StateMachineForward
{

	class MachineAction : private NonAssignable, private NonCopyable
	{
	public:
		MachineAction() = default;
		virtual ~MachineAction() = default;
		template<typename T>
		const T* cast() const
		{
			return dynamic_cast<const T*>(this);
		}
	};

	using PtrMachineAction = std::unique_ptr<MachineAction>;
} // end namespace StateMachineForward
