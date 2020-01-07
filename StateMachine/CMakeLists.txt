cmake_minimum_required(VERSION 3.5)


set(SOURCES_StateMachine
    ./MachineBase.cpp
    ./ManagerMessages.cpp
    ./MachineMessage.cpp
    ./StateBase.cpp
    ./StateMachineBase.cpp
)

set(INCLUDES_StateMachine
    ./MachineAction.h
    ./MachineControl.h
    ./ManagerMessagesControl.h
    ./StateControl.h
    ./StateMachineControl.h
)

# Создание статической библиотеки
add_library(StateMachine_LIB STATIC ${SOURCES_StateMachine} ${INCLUDES_StateMachine})
