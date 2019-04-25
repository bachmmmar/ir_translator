
#include "src/IRremote/IRremote.h"

#include "src/timer/Timer.h"
#include "src/controller.h"
#include "src/amplifier.h"
#include "src/tv_remote_receiver.h"


/*********** IR Config and variables *********** */
int RECV_PIN = 13;
int SEND_PIN = 3;
IRrecv irrecv(RECV_PIN);
IRsend irsend;  // uses pin 3 on arduino uno

/*********** Devices *********** */
Timer timer;
Amplifier amp(&irsend, & irrecv);
Controller ctrl(&timer, &amp);
TvRemoteReceiver tv_remote(&irrecv, &ctrl);

void setup() {

  Serial.begin(9600);
  
  ctrl.setup();
  tv_remote.setup();
}

void loop() {
  timer.update();
  tv_remote.receive();
}
