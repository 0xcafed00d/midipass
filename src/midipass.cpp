#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>

#include "RtMidi.h"

std::vector<std::string> getPortNames(std::shared_ptr<RtMidi> midi) {
	std::vector<std::string> ports;

	size_t count = midi->getPortCount();
	for (size_t i = 0; i < count; i++) {
		ports.push_back(midi->getPortName(i));
	}

	return ports;
}

int main() {
	std::shared_ptr<RtMidiIn> midi_in;
	std::shared_ptr<RtMidiOut> midi_out;

	try {
		midi_in = std::make_shared<RtMidiIn>();
		midi_out = std::make_shared<RtMidiOut>();

		auto in_names = getPortNames(midi_in);
		auto out_names = getPortNames(midi_out);

	} catch (RtMidiError& error) {
		error.printMessage();
	}

	return 0;
}
