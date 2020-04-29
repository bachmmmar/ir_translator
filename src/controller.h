#pragma once

#include <arduino.h>
#include "types.h"


class Amplifier;
class Timer;

class Controller {

public:
	Controller(Timer * timer, Amplifier * amp);

	void setup();

	void receivedCommand(Commands cmd);


private:
	Timer * timer_;
	Amplifier * amp_;

	bool tvNotPC_;

	static void selectMusic(void *ptr);

};
