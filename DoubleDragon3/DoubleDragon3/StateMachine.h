#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
#include <stdio.h>
#include "EventData.h"
 
struct StateStruct;
 
// This is the base clase for states machines.
class StateMachine 
{
public:
    typedef unsigned char State;

            StateMachine    (int maxStates);
    virtual ~StateMachine   () {}

    virtual void    Update  ();

protected:
    enum { EVENT_IGNORED = 0xFE, CANNOT_HAPPEN };

    State m_CurrentState;

    void                       OnEvent    (State NewState, const EventData* = NULL);
    virtual const StateStruct* GetStateMap() = 0;

private:
    const int mc_MaxStates;

    void MoveState(State ucNewEvent, const EventData* pData);
};
 

//----------------------------------------------------------------------------------------------------
// Every state has 3 associated fuctions: OnEnter, OnUpdate and OnExit.
// These are the prototypes for those functions
//----------------------------------------------------------------------------------------------------
typedef void (StateMachine::*StateFuncOnEnter )(StateMachine::State PrevState, const EventData* pData);
typedef void (StateMachine::*StateFuncOnUpdate)();
typedef void (StateMachine::*StateFuncOnExit  )(StateMachine::State NextState);
struct StateStruct 
{
    StateFuncOnEnter  pOnEnter;
    StateFuncOnUpdate pOnUpdate;
    StateFuncOnExit   pOnExit;
};

//----------------------------------------------------------------------------------------------------
// Next macros map the States with their corresponding fuctions of "OnEnter", "OnUpdate" and "OnExit" 
// It must be used in the child StateMachine declaration.
//----------------------------------------------------------------------------------------------------
#define BEGIN_STATE_MAP \
public:\
const StateStruct* GetStateMap() {\
    static const StateStruct StateMap[] = { 

#define STATE_MAP_ENTRY(_class, _entry)\
    { reinterpret_cast<StateFuncOnEnter>(&_class::OnEnter_##_entry)  , \
      reinterpret_cast<StateFuncOnUpdate>(&_class::OnUpdate_##_entry), \
      reinterpret_cast<StateFuncOnExit>(&_class::OnExit_##_entry)    },

#define END_STATE_MAP \
    { reinterpret_cast<StateFuncOnEnter>((StateFuncOnEnter)nullptr),   \
      reinterpret_cast<StateFuncOnUpdate>((StateFuncOnUpdate)nullptr), \
      reinterpret_cast<StateFuncOnExit>((StateFuncOnExit)nullptr) }    \
    };                                                                 \
    return &StateMap[0]; }


//----------------------------------------------------------------------------------------------------
// Next macros map the transition between states. Be careful! The order of every entry must be 
// always consistent with the state order!
//----------------------------------------------------------------------------------------------------
#define BEGIN_TRANSITION_MAP \
    static const unsigned char TRANSITIONS[] = {\

#define TRANSITION_MAP_ENTRY(entry)\
    entry,

#define END_TRANSITION_MAP(data) \
    0 };\
    OnEvent(TRANSITIONS[m_CurrentState], data);


//----------------------------------------------------------------------------------------------------
// Makes the declaration of the functions needed for every estate easier. The functions needed are
// OnEnter_xxx, OnUpdate_xxx and OnExit_xxx, where xxx is the state name.
//----------------------------------------------------------------------------------------------------
#define STATE_FUNCTION_DECLARATION(_func) \
    private: void OnEnter_##_func  (StateMachine::State PrevState, const EventData* pData); \
             void OnUpdate_##_func ();                                            \
             void OnExit_##_func   (StateMachine::State NextState);

#endif //STATE_MACHINE_H
