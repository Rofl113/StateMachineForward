cmake_minimum_required(VERSION 3.5)

set(SOURCES_StateMachine
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

add_library(Rofl113_StateMachine_Lib STATIC ${SOURCES_StateMachine})  # Создание статической библиотеки
