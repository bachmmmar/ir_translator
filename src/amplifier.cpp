#include "amplifier.h"

#include "IRremote/IRremote.h"

Amplifier::Amplifier(IRsend * ir_send, IRrecv * ir_receiver) : ir_send_(ir_send), ir_receiver_(ir_receiver) {}


void Amplifier::chooseTV() {
	sendCommand(0xb56, "Send Amp OPT1");
}

void Amplifier::choosePC() {
	sendCommand(0xb54, "Send Amp USB");  // 354
}

void Amplifier::chooseMusic() {
	sendCommand(0xb59, "Send Amp COAX2");
}

void Amplifier::volumeUp() {
	sendCommand(0xb50, "Send Amp Volume Up");  // 350
}

void Amplifier::volumeDown() {
	sendCommand(0xb51, "Send Amp Volume Down"); // 351
}


void Amplifier::sendCommand(unsigned long data, String description) {
	Serial.println(description.c_str());
	ir_send_->sendRC5(data, 12);
	delay(1);
	ir_receiver_->enableIRIn();
}