#include "controller.h"

#include "amplifier.h"
#include "timer/Timer.h"


#define POWER_UP_MUSIC_SELECTION_DELAY_MS 10000



Controller::Controller(Timer * timer, Amplifier * amp) : timer_(timer), amp_(amp) {}


void Controller::setup() {
	timer_->after(POWER_UP_MUSIC_SELECTION_DELAY_MS, selectMusic, this);
}


void Controller::receivedCommand(Commands cmd) {
	switch (cmd) {
		case TVVolumeUp: 
			amp_->volumeUp();
			break;
		case TVVolumeDown:
			amp_->volumeDown();
			break;
		case TVPower: 
			amp_->chooseMusic();
			break;
		case TVTV: 
			amp_->chooseTV();
			break;
		case TVSource:
			amp_->choosePC();
			break;
	}
}

void Controller::selectMusic(void *ptr) {
	Serial.println("Choosing Music input");
	static_cast<Controller*>(ptr)->amp_->chooseMusic();
}
