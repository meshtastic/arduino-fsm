// This file is part of arduino-fsm.
//
// arduino-fsm is free software: you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// arduino-fsm is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with arduino-fsm.  If not, see <http://www.gnu.org/licenses/>.

#ifndef FSM_H
#define FSM_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

struct State
{
  State(void (*on_enter)(), void (*on_state)(), void (*on_exit)(), const char *name);
  void (*on_enter)();
  void (*on_state)();
  void (*on_exit)();
  const char *name;
};

struct Transition
{
  State *state_from;
  State *state_to;
  int event;
  void (*on_transition)();
  const char *name;
};

struct TimedTransition
{
  Transition transition;
  unsigned long start;
  unsigned long interval;
};

#define MAX_TIMED_TRANSITIONS 8

// Maximum number of regular transitions
// Can be overridden at compile time: -DMAX_TRANSITIONS=128
// Fixed-size array prevents memory leaks and fragmentation
#ifndef MAX_TRANSITIONS
#define MAX_TRANSITIONS 128
#endif

class Fsm
{
public:
  Fsm(State *initial_state);
  ~Fsm();

  // Add a transition between states
  // Returns true on success, false if transition array is full
  bool add_transition(State *state_from, State *state_to, int event,
                      void (*on_transition)(), const char *name);

  TimedTransition *add_timed_transition(State *state_from, State *state_to,
                            unsigned long interval, void (*on_transition)(), const char *name);

  State *getState() const { return m_current_state; }
  int getNumTransitions() const { return m_num_transitions; }
  int getMaxTransitions() const { return MAX_TRANSITIONS; }
  int getAvailableTransitions() const { return MAX_TRANSITIONS - m_num_transitions; }

  void check_timed_transitions();

  void trigger(int event);
  void run_machine();

private:
  static Transition create_transition(State *state_from, State *state_to,
                                      int event, void (*on_transition)(), const char *name);

  void make_transition(Transition *transition);

private:
  State *m_current_state;
  Transition m_transitions[MAX_TRANSITIONS];
  int m_num_transitions;

  TimedTransition m_timed_transitions[MAX_TIMED_TRANSITIONS];
  int m_num_timed_transitions;
  bool m_initialized;
};

#endif
