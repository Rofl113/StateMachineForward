#include "MachineBase.h"
#include "ManagerMessagesControl.h"
#include "MachineAction.h"
#include <iostream>


PtrMachineAction MachineBase::createActionDontNext() const
{
	return PtrMachineAction(new MachineActionDontNext());
}

PtrMachineAction MachineBase::createActionNext() const
{
	return {};
}

void MachineBase::_pushChild(std::unique_ptr<MachineControl>&& child)
{
	// Новый
	if (child)
	{
		m_childs.push(std::move(child));
		if (auto childCurrent = m_childs.top().get())
		{
			if (auto ch = dynamic_cast<MachineBase*>(childCurrent))
			{
				ch->setParent(this);
				ch->_handleEnterFull();
			}
		}
	}
}

std::unique_ptr<MachineControl> MachineBase::_popChild()
{
	// Старый
	if (!m_childs.empty())
	{
		auto child = std::move(m_childs.top());
		if (auto ch = dynamic_cast<MachineBase*>(child.get()))
		{
			ch->_handleExitFull();
			ch->setParent(nullptr);
		}
		m_childs.pop();
		return child;
	}
	return {};
}

const MachineControl* MachineBase::_getParent() const
{
	return m_parent;
}

void MachineBase::pushMessage(PtrMachineMessage message)
{
	// Если есть сообщение
	if (message)
	{
		// Если есть родитель (сообщения идут от корня к листам)
		auto m = (nullptr != m_parent) ? m_parent : this;
		m->sendMessage(*message.get());
	}
}

std::unique_ptr<MachineAction> MachineBase::_handleEnterFull()
{
	auto action = this->_handleEnter();
	if (action)
	{
		if (this->_processAction(*action.get()))
		{
			return this->createActionDontNext();
		}
	}
	if (!m_childs.empty())
	{
		auto child = dynamic_cast<MachineBase*>(m_childs.top().get());
		if (child)
		{
			const auto actionChild = child->_handleEnterFull();
			if (actionChild)
			{
				if (this->_processAction(*actionChild.get()))
				{
					return this->createActionDontNext();
				}
			}
		}
	}
	return this->createActionNext();
}

std::unique_ptr<MachineAction> MachineBase::_handleMessageFull(const MachineMessage& message)
{
	auto action = this->_handleMessage(message);
	if (action)
	{
		if (this->_processAction(*action.get()))
		{
			return this->createActionDontNext();
		}
	}
	if (!m_childs.empty())
	{
		auto child = dynamic_cast<MachineBase*>(m_childs.top().get());
		if (child)
		{
			action = child->_handleMessageFull(message);
			if (action)
			{
				if (this->_processAction(*action.get()))
				{
					return this->createActionDontNext();
				}
			}
		}
	}
	return action;
}

std::unique_ptr<MachineAction> MachineBase::_handleExitFull()
{
	// Сначала завершаем дочернюю машину
	if (!m_childs.empty())
	{
		auto child = dynamic_cast<MachineBase*>(m_childs.top().get());
		if (child)
		{
			const auto actionChild = child->_handleExitFull();
			if (actionChild)
			{
				if (this->_processAction(*actionChild.get()))
				{
					return this->createActionDontNext();
				}
			}
		}
	}
	// Затем завершаем текущую машину
	auto action = this->_handleExit();
	if (action)
	{
		if (this->_processAction(*action.get()))
		{
			return this->createActionDontNext();
		}
	}
	return action;
}

const MachineControl* MachineBase::_getChild() const
{
	if (!m_childs.empty())
	{
		return m_childs.top().get();
	}
	return nullptr;
}

MachineControl* MachineBase::_getChild()
{
	if (!m_childs.empty())
	{
		return m_childs.top().get();
	}
	return nullptr;
}

void MachineBase::sendMessage(const MachineMessage& message)
{
	this->_handleMessageFull(message);
}

void MachineBase::setParent(MachineControl* parent)
{
	if (parent != m_parent)
	{
		m_parent = parent;
	}
}

bool MachineBase::_processAction(const MachineAction& action)
{
	if (dynamic_cast<const MachineActionDontNext*>(&action))
	{
		return true;
	}
	return false;
}
