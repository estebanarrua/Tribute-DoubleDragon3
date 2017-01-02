#include <iostream>
#include <cassert>
#include "StateMachine.h"

//-----------------------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------------------
StateMachine::StateMachine(int maxStates) :
    mc_MaxStates(maxStates),
    m_CurrentState(0)
{
}

//-----------------------------------------------------------------------------------------
// Call the update of the current state 
//-----------------------------------------------------------------------------------------
void StateMachine::Update()
{
    const StateStruct* pStateMap = GetStateMap();

    (this->*pStateMap[m_CurrentState].pOnUpdate)();
}
 
//-----------------------------------------------------------------------------------------
// Handles a new event to change the current state
//-----------------------------------------------------------------------------------------
void StateMachine::OnEvent(State NewState, const EventData* pData)
{
    assert(NewState < mc_MaxStates || NewState >= EVENT_IGNORED);
    assert(NewState != CANNOT_HAPPEN);

    switch (NewState)
    {
        case EVENT_IGNORED:
            std::cout << "Event ignored.\n";
            break;

        case CANNOT_HAPPEN:
            std::cout << "Error: This transition cannot happen.\n";
            break;

        default:
            MoveState(NewState, pData); 
            break;
    }
}
 
//-----------------------------------------------------------------------------------------
// Executes the state change
//-----------------------------------------------------------------------------------------
void StateMachine::MoveState(State NewState, const EventData* pData)
{
    const StateStruct* pStateMap = GetStateMap();
    unsigned char PrevState = m_CurrentState;

    // Exit from current state
    (this->*pStateMap[m_CurrentState].pOnExit)(NewState);
    

    // Enter in the new state
    m_CurrentState = NewState;
    (this->*pStateMap[m_CurrentState].pOnEnter)(PrevState, pData);
}
