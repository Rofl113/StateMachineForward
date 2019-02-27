cmake_minimum_required(VERSION 3.5)

set(SOURCES_SM
	./MachineAction.h
	./MachineControl.h
	./MachineBase.cpp
	./ManagerMessagesControl.h
	./ManagerMessages.cpp
	./MachineMessage.cpp
	./StateControl.h
	./StateBase.cpp
	./StateMachineControl.h
	./StateMachineBase.cpp
)

add_library(SM_LIBS STATIC ${SOURCES_SM})  # Создание статической библиотеки
