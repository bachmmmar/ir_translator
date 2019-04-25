#include "tv_remote_receiver.h"

#include <arduino.h>

#include "controller.h"
#include "IRremote/IRremote.h"

TvRemoteReceiver::TvRemoteReceiver(IRrecv * ir_receiver, Controller * ctrl) : ir_receiver_(ir_receiver), ctrl_(ctrl) {}


void TvRemoteReceiver::setup() {
	Serial.println("Setting up ir receiver");
	ir_receiver_->enableIRIn();  // Start the receiver
}


void TvRemoteReceiver::receive() {
	decode_results results;

	if (ir_receiver_->decode(&results)) {
    	printIRResult(results);
    	extractCommand(results);

		ir_receiver_->resume(); // Receive the next value
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
