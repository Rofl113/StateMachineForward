#pragma once
#include <memory>


namespace StateMachineForward
{

	class MachineAction
	{
	public:
		MachineAction& operator=(const MachineAction &) = delete;
		MachineAction(const MachineAction &) = delete;

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
