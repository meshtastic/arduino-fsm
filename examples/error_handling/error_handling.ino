#include "Fsm.h"

// Example demonstrating error handling for transition limits

#define BUTTON_PRESS 1

State state1(NULL, NULL, NULL, "State1");
State state2(NULL, NULL, NULL, "State2");
Fsm fsm(&state1);

void setup()
{
  Serial.begin(9600);
  
  Serial.print("Maximum transitions: ");
  Serial.println(fsm.getMaxTransitions());
  
  // Add transitions with error checking
  bool success = fsm.add_transition(&state1, &state2, BUTTON_PRESS, NULL, "1->2");
  if (!success) {
    Serial.println("ERROR: Failed to add transition 1->2");
  }
  
  success = fsm.add_transition(&state2, &state1, BUTTON_PRESS, NULL, "2->1");
  if (!success) {
    Serial.println("ERROR: Failed to add transition 2->1");
  }
  
  Serial.print("Transitions used: ");
  Serial.println(fsm.getNumTransitions());
  Serial.print("Transitions available: ");
  Serial.println(fsm.getAvailableTransitions());
}

void loop()
{
  fsm.run_machine();
  
  // Simulate button press every 2 seconds
  static unsigned long last_press = 0;
  if (millis() - last_press > 2000) {
    fsm.trigger(BUTTON_PRESS);
    last_press = millis();
  }
}
