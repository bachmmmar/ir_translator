

# Introduction
The IRTranslator simply takes commands from my Samsung TV remote control and translates certain commands for my Amplifier by using an Arduino UNO.


The following behaviour is implemented:

| Input | Result |
| --- | --- |
| Powerup -> 10s delay | -> Amplifier Switch to Coax Input (Squezebox Touch) |
| TV Remote Volume UP/Down | -> Amplifier Volume UP/Down |
| TV Remote Power Off | -> Amplifier Switch to Coax Input (Squezebox Touch) |
| TV Remote TV Button | -> Amplifier Switch to Optical Input (TV) |
| TV Remote Source Button | -> Amplifier Switch to USB (PC) or Switch to Optical Input (TV) alternating |



# Introduction to IR with Arduino
Tutorial: http://www.circuitbasics.com/arduino-ir-remote-receiver-tutorial/
