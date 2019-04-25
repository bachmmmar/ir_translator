#pragma once

#include "types.h"

class IRrecv;
class Controller;
struct decode_results;

class TvRemoteReceiver {

public:
	TvRemoteReceiver(IRrecv * ir_receiver, Controller * ctrl);

	void setup();
	void receive();


private:
	IRrecv * ir_receiver_;
	Controller * ctrl_;

	void printIRResult(const decode_results & results);

	void extractCommand(const decode_results & results);

};
