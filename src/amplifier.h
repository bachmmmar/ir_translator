#pragma once

#include <arduino.h>

class IRsend;
class IRrecv;

class Amplifier {

public:
	Amplifier(IRsend * ir_send, IRrecv * ir_receiver);

	void chooseTV();
	void choosePC();
	void chooseMusic();

	void volumeUp();
	void volumeDown();


private:
	void sendCommand(unsigned long data, String description);

	IRsend * ir_send_;
	IRrecv * ir_receiver_;

};
