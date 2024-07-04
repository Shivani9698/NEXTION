#include "Nextion.h"

// Declare your Nextion button objects for page 1
NexButton b0 = NexButton(0, 1, "b0");
NexButton b1 = NexButton(0, 2, "b1");
NexButton b2 = NexButton(0, 3, "b2");
NexButton b3 = NexButton(0, 4, "b3");
NexButton b4 = NexButton(0, 5, "b4");
NexButton b5 = NexButton(0, 6, "b5");
NexButton b6 = NexButton(0, 7, "b6");
NexButton b7 = NexButton(0, 8, "b7");
NexButton b8 = NexButton(0, 9, "b8");
NexButton b9 = NexButton(0, 10, "b9");
NexButton b10 = NexButton(0, 11, "b10");
NexButton b11 = NexButton(0, 12, "b11");
NexButton b12 = NexButton(0, 13, "b12");
NexButton b13 = NexButton(0, 14, "b13");
NexButton b14 = NexButton(0, 15, "b14");

// Register the button objects to the touch event list
NexTouch *nex_listen_list[] = {
  &b0, &b1, &b2, &b3, &b4, &b5, &b6, &b7, &b8, &b9, 
  &b10, &b11, &b12, &b13, &b14, 
  NULL
};

// Callback functions for button press events
void b0PopCallback(void *ptr) { Serial.println("Button b0 pressed"); }
void b1PopCallback(void *ptr) { Serial.println("Button b1 pressed"); }
void b2PopCallback(void *ptr) { Serial.println("Button b2 pressed"); }
void b3PopCallback(void *ptr) { Serial.println("Button b3 pressed"); }
void b4PopCallback(void *ptr) { Serial.println("Button b4 pressed"); }
void b5PopCallback(void *ptr) { Serial.println("Button b5 pressed"); }
void b6PopCallback(void *ptr) { Serial.println("Button b6 pressed"); }
void b7PopCallback(void *ptr) { Serial.println("Button b7 pressed"); }
void b8PopCallback(void *ptr) { Serial.println("Button b8 pressed"); }
void b9PopCallback(void *ptr) { Serial.println("Button b9 pressed"); }
void b10PopCallback(void *ptr) { Serial.println("Button b10 pressed"); }
void b11PopCallback(void *ptr) { Serial.println("Button b11 pressed"); }
void b12PopCallback(void *ptr) { Serial.println("Button b12 pressed"); }
void b13PopCallback(void *ptr) { Serial.println("Button b13 pressed"); }
void b14PopCallback(void *ptr) { Serial.println("Button b14 pressed"); }

void setup(void) {    
  Serial.begin(9600);
  
  // Initialize the Nextion display
  nexInit();
  
  // Attach the callback functions to the button objects
  b0.attachPop(b0PopCallback);
  b1.attachPop(b1PopCallback);
  b2.attachPop(b2PopCallback);
  b3.attachPop(b3PopCallback);
  b4.attachPop(b4PopCallback);
  b5.attachPop(b5PopCallback);
  b6.attachPop(b6PopCallback);
  b7.attachPop(b7PopCallback);
  b8.attachPop(b8PopCallback);
  b9.attachPop(b9PopCallback);
  b10.attachPop(b10PopCallback);
  b11.attachPop(b11PopCallback);
  b12.attachPop(b12PopCallback);
  b13.attachPop(b13PopCallback);
  b14.attachPop(b14PopCallback);
}

void loop(void) {   
  // Listen for touch events
  nexLoop(nex_listen_list);
}
