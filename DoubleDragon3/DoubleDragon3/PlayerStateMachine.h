#ifndef _PLAYERSTATEMACHINE_H_
#define _PLAYERSTATEMACHINE_H_

#include "StateMachine.h"

class PlayerStateMachine : public StateMachine {
public:

        PlayerStateMachine () : StateMachine(ST_COUNT) {}
        ~PlayerStateMachine() {}

    void Update();

    // Supported Events:
    void HealthPotion();
    void ReceiveDamage();

private:

    // Enumeration of the states:
    enum EState {
        #define PLAYER_STATE(_state, _func) _state,
            #include "PlayerState.h"
        #undef PLAYER_STATE
        ST_COUNT   
    };

    // Function declaration for the states. Every states has 3 associated functions:
    // OnEnter_xxx, OnUpdate_xxx and OnExit_xxx
    #define PLAYER_STATE(_state, _func) STATE_FUNCTION_DECLARATION(_func)
        #include "PlayerState.h"
    #undef PLAYER_STATE

    // Mapping of the states with their associated functions
    BEGIN_STATE_MAP
        #define PLAYER_STATE(_state, _func) STATE_MAP_ENTRY(PlayerStateMachine, _func)
            #include "PlayerState.h"  
        #undef PLAYER_STATE
    END_STATE_MAP

    // Converts a state to string
    const char * StateToStr(State state);
 };

#endif // _PLAYERSTATEMACHINE_H_

