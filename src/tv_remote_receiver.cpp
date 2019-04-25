#include "tv_remote_receiver.h"

#include <arduino.h>

#include "controller.h"
#include "IRremote/IRremote.h"
#include "timer/Timer.h"


#define ENABLE_RECEIVER_TIMER_MS 60000

TvRemoteReceiver::TvRemoteReceiver(IRrecv * ir_receiver, Controller * ctrl, Timer * timer) : ir_receiver_(ir_receiver), ctrl_(ctrl), timer_(timer) {}


void TvRemoteReceiver::setup() {
	Serial.println("Setting up ir receiver");
	ir_receiver_->enableIRIn();  // Start the receiver
	timer_->every(ENABLE_RECEIVER_TIMER_MS, ensureWorkingReceiver, this);
}


void TvRemoteReceiver::receive() {
	decode_results results;

	if (ir_receiver_->decode(&results)) {
    	printIRResult(results);
    	extractCommand(results);

		ir_receiver_->resume(); // Receive the next value
  	}
}

void TvRemoteReceiver::ensureWorkingReceiver(void *ptr) {
	if (static_cast<TvRemoteReceiver*>(ptr)->ir_receiver_->isIdle()) {
		Serial.println("Receiver Idle");
		static_cast<TvRemoteReceiver*>(ptr)->ir_receiver_->enableIRIn();
	} else {
		Serial.println("Receiver not Idle");
	}
}

void TvRemoteReceiver::extractCommand(const decode_results & results) {
	if (results.decode_type == SAMSUNG) {
		switch (results.value) {
			case 0xe0e040bf:
				Serial.println("TV Power pressed");
				ctrl_->receivedCommand(TVPower);
				break;
			case 0xe0e0d827:
				Serial.println("TV TV pressed");
				ctrl_->receivedCommand(TVTV);
				break;
			case 0xe0e0e01f:
				Serial.println("TV Volume Up pressed");
				ctrl_->receivedCommand(TVVolumeUp);
				break;
			case 0xe0e0d02f:
				Serial.println("TV Volume Down pressed");
				ctrl_->receivedCommand(TVVolumeDown);
				break;
			case 0xe0e0807f:
				Serial.println("TV Source pressed");
				ctrl_->receivedCommand(TVSource);
				break;
		}
	}
}

void TvRemoteReceiver::printIRResult(const decode_results & results) {
    String str = "Received: 0x"+ String(results.value, HEX) + ", decoded with " + String(results.decode_type) + ", " + String(results.bits) + "bits ";
    Serial.println(str.c_str());
    #ifdef PRINT_RAW_IR_DATA
    str = "   RAW: ";
    for (int i=0; i < results.rawlen; i++) {
        str+= " 0x" + String(results.rawbuf[i], HEX);
    }
    Serial.println(str.c_str());
    #endif
}
