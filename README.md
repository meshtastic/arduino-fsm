An arduino library for implementing a finite state machine.

# Memory Efficient Design

This library uses fixed-size arrays to avoid memory fragmentation and leaks. By default:
- Maximum 128 transitions (can be customized with `-DMAX_TRANSITIONS=N`)
- Maximum 8 timed transitions

For projects needing more transitions, compile with: `-DMAX_TRANSITIONS=128` (or your desired limit)

# Usage

The `add_transition()` method now returns a boolean indicating success. Check the return value for critical applications:

```cpp
bool success = fsm.add_transition(&state1, &state2, EVENT, &callback, "transition_name");
if (!success) {
  // Handle error: transition array is full
}

// Check available capacity
int available = fsm.getAvailableTransitions();
```

# Documentation

Other than the examples included in the library, the following pages might be
useful to you:

* [Humble Coder: Arduino finite state machine library][1]
* [Humble Coder: Arduino multitasking using a finite state machine][2]

[1]: http://www.humblecoder.com/arduino-finite-state-machine-library/
[2]: http://www.humblecoder.com/arduino-multitasking-using-finite-state-machines/

# Contribution

If you'd like to contribute to `arduino-fsm` please submit a pull-request on a
feature branch.

# Donate

* Bitcoin: 1HnqohdK1d6gwDc7bT6LPPkmUFAXczEJKp

# Changelog

**2.3.0 - 06/09/2025**

* **MAJOR FIX**: Eliminated memory leak caused by dynamic allocation in `add_transition()`
* Changed from dynamic `realloc()` to fixed-size array for transitions (default: 128 max transitions)
* `add_transition()` now returns `bool` to indicate success/failure
* Added methods: `getNumTransitions()`, `getMaxTransitions()`, `getAvailableTransitions()`
* Maximum transitions can be customized at compile time with `-DMAX_TRANSITIONS=N`
* **BREAKING CHANGE**: `add_transition()` now returns bool instead of void
* Fixed memory fragmentation issues on Arduino with limited RAM

**2.2.0 - 25/10/2017**

* Add `on_state()` handler to states
* New `run_machine()` method to invoke machine execution (includes a `check_timed_transitions()` call)
* New `timed_switchoff.ino` example sketch to ilustrate new `on_state()` and `run_machine()` funcionality
* Corrections:
 - `make_transition()` correctly initialices timed transitions start milliseconds (`make_transition()` is now a fsm method)
 - Initial state `on_enter()` handler is now correctly executed on fsm first run
 - Removed `Serial.println(now);` trace in _Fsm.cpp_
 - Correct initialization of `m_num_timed_transitions`
 

**2.1.0 - 21/11/2015**

* Add timed transitions

**2.0.0 - 03/09/2015**

* Remove AUTHORS files: too much hassle to maintain
* Add library.properties
* Add keywords.txt
* Remove name attribute from state
* Use int for transition event instead of string

**1.0.0 - 24/12/2013**

* Initial release.
