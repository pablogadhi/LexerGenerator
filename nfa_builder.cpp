#include "nfa_builder.h"

StateMachine nfa_from_or(StateMachine &a, StateMachine &b, int &last_index)
{
    shared_ptr<State> first_state = make_shared<State>(to_string(last_index + 1));
    shared_ptr<State> last_state = make_shared<State>(to_string(last_index + 2));
    first_state->set_t_functions(
        vector<pair<int, shared_ptr<State>>>{make_pair(-1, a.start()), make_pair(-1, b.start())});
    a.end()->set_t_functions(vector<pair<int, shared_ptr<State>>>{make_pair(-1, last_state)});
    b.end()->set_t_functions(vector<pair<int, shared_ptr<State>>>{make_pair(-1, last_state)});
    last_index += 2;
    return StateMachine(first_state, last_state);
}

StateMachine nfa_from_concat(StateMachine &a, StateMachine &b)
{
    int b_transition = b.start()->get_t_functions()[0].first;
    a.end()->set_t_functions(vector<pair<int, shared_ptr<State>>>{make_pair(b_transition, b.end())});
    return StateMachine(a.start(), b.end());
}

StateMachine nfa_from_kleene(StateMachine &a, int &last_index)
{
    shared_ptr<State> first_state = make_shared<State>(to_string(last_index + 1));
    shared_ptr<State> last_state = make_shared<State>(to_string(last_index + 2));
    first_state->set_t_functions(
        vector<pair<int, shared_ptr<State>>>{make_pair(-1, a.start()), make_pair(-1, last_state)});
    a.end()->add_t_function(make_pair(-1, a.start()));
    a.end()->add_t_function(make_pair(-1, last_state));
    last_index += 2;
    return StateMachine(first_state, last_state);
}

StateMachine nfa_from_transition(int transition, int &last_index)
{
    shared_ptr<State> last_state = make_shared<State>(to_string(last_index + 2));
    string first_name_string = to_string(last_index + 1);
    shared_ptr<State> first_state =
        make_shared<State>(first_name_string, vector<pair<int, shared_ptr<State>>>{make_pair(transition, last_state)});
    last_index += 2;
    return StateMachine(first_state, last_state);
}