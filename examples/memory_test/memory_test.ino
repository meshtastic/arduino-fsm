#include "Fsm.h"

// Memory leak test - demonstrates the fix for the realloc() issue

State state1(NULL, NULL, NULL, "State1");
State state2(NULL, NULL, NULL, "State2"); 
State state3(NULL, NULL, NULL, "State3");
State state4(NULL, NULL, NULL, "State4");
State state5(NULL, NULL, NULL, "State5");

Fsm fsm(&state1);

void setup() {
  Serial.begin(9600);
  Serial.println("=== Arduino FSM Memory Leak Test ===");
  
  // Report initial memory info
  Serial.print("Max transitions supported: ");
  Serial.println(fsm.getMaxTransitions());
  
  // Add many transitions to simulate PowerFSM scenario
  Serial.println("Adding 35 transitions to simulate PowerFSM...");
  
  for (int i = 0; i < 35; i++) {
    // Cycle through states to create many transitions
    State* from = &state1;
    State* to = &state2;
    
    switch (i % 5) {
      case 0: from = &state1; to = &state2; break;
      case 1: from = &state2; to = &state3; break;
      case 2: from = &state3; to = &state4; break;
      case 3: from = &state4; to = &state5; break;
      case 4: from = &state5; to = &state1; break;
    }
    
    bool success = fsm.add_transition(from, to, i, NULL, "test_transition");
    
    if (!success) {
      Serial.print("FAILED to add transition ");
      Serial.println(i);
    }
    
    // Print progress every 10 transitions
    if ((i + 1) % 10 == 0) {
      Serial.print("Added ");
      Serial.print(i + 1);
      Serial.print(" transitions. Available: ");
      Serial.println(fsm.getAvailableTransitions());
    }
  }
  
  Serial.print("Final transitions count: ");
  Serial.println(fsm.getNumTransitions());
  Serial.print("Available transitions: ");
  Serial.println(fsm.getAvailableTransitions());
}

void loop() {
  // Nothing to do - this is just a setup test
  delay(1000);
}
