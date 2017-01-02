#include <iostream>

#include "PlayerStateMachine.h"


//-----------------------------------------------------------------------------------------
// Update of the StateMachine. 
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::Update()
{
    StateMachine::Update();
}


////-----------------------------------------------------------------------------------------
//// Event happened. It makes the transition to the corresponding state.
////-----------------------------------------------------------------------------------------
//void PlayerStateMachine::ReceiveDamage()
//{
//    BEGIN_TRANSITION_MAP                      // - Current State -
//        TRANSITION_MAP_ENTRY (ST_UNDEFINED)   // ST_Undefined
//        TRANSITION_MAP_ENTRY (ST_DAMAGED)     // ST_Healthy
//        TRANSITION_MAP_ENTRY (ST_DEAD)        // ST_Damaged
//        TRANSITION_MAP_ENTRY (EVENT_IGNORED)  // ST_Dead
//    END_TRANSITION_MAP(NULL)
//}


//-----------------------------------------------------------------------------------------
// Converts a State type to a string
//-----------------------------------------------------------------------------------------
const char * PlayerStateMachine::StateToStr(State state)
{
    const char *paszStates[] = {
        #define PLAYER_STATE(_state, _func) #_state,
            #include "PlayerState.h"
        #undef PLAYER_STATE
    };
    return paszStates[state];
}

//-----------------------------------------------------------------------------------------
// Idle State
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::OnEnter_Idle(State PrevState, const EventData* pData)
{
    OnEvent(ST_IDLE, NULL);
}

void PlayerStateMachine::OnUpdate_Idle()
{
    OnEvent(ST_IDLE, NULL);
}

void PlayerStateMachine::OnExit_Idle(State NextState)
{
}

//-----------------------------------------------------------------------------------------
// Walk State
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::OnEnter_Walk(State PrevState, const EventData* pData)
{
	OnEvent(ST_WALK, NULL);
}

void PlayerStateMachine::OnUpdate_Walk()
{
	OnEvent(ST_WALK, NULL);
}

void PlayerStateMachine::OnExit_Walk(State NextState)
{
}

//-----------------------------------------------------------------------------------------
// Jump State
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::OnEnter_Jump(State PrevState, const EventData* pData)
{
	OnEvent(ST_JUMP, NULL);
}

void PlayerStateMachine::OnUpdate_Jump()
{
	OnEvent(ST_JUMP, NULL);
}

void PlayerStateMachine::OnExit_Jump(State NextState)
{
}

//-----------------------------------------------------------------------------------------
// Jump Move State
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::OnEnter_JumpMove(State PrevState, const EventData* pData)
{
	OnEvent(ST_JUMP_MOVE, NULL);
}

void PlayerStateMachine::OnUpdate_JumpMove()
{
	OnEvent(ST_JUMP_MOVE, NULL);
}

void PlayerStateMachine::OnExit_JumpMove(State NextState)
{
}