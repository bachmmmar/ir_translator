#pragma once

#include "types.h"

class IRrecv;
class Controller;
class Timer;
struct decode_results;

class TvRemoteReceiver {

public:
	TvRemoteReceiver(IRrecv * ir_receiver, Controller * ctrl, Timer * timer);

	void setup();
	void receive();


private:
	IRrecv * ir_receiver_;
	Controller * ctrl_;
	Timer * timer_;

	static void ensureWorkingReceiver(void *ptr);

	void printIRResult(const decode_results & results);

	void extractCommand(const decode_results & results);

};
