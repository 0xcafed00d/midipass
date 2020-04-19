#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "RtMidi.h"

typedef std::vector<unsigned char> midi_message_t;

std::vector<std::string> getPortNames(std::shared_ptr<RtMidi> midi) {
	std::vector<std::string> ports;

	size_t count = midi->getPortCount();
	for (size_t i = 0; i < count; i++) {
		ports.push_back(midi->getPortName(i));
	}

	return ports;
}

void displayPortNames(const char* msg, std::vector<std::string>& names) {
	std::cout << msg << std::endl;
	int i = 0;
	for (auto s : names) {
		std::cout << " " << i++ << ":  " << s << std::endl;
	}
}

void displayUsage() {
	std::cout << "midipass <input port index> <output port index>" << std::endl;
}

unsigned int parseInt(const char* s) {
	try {
		return std::stoi(s);
	} catch (std::invalid_argument& error) {
		std::string err;
		err += "unable to parse: " + std::string(s) + " as number";
		throw(std::invalid_argument(err.c_str()));
	}
}

void dumpMessage(midi_message_t& msg) {
	for (auto v : msg) {
		printf("%02x ", (int)v);
	}
	printf("\n");
}

std::shared_ptr<RtMidiIn> midi_in;
std::shared_ptr<RtMidiOut> midi_out;

void midiCallback(double timeStamp, std::vector<unsigned char>* message, void* userData) {
	if (message->size()) {
		dumpMessage(*message);
		midi_out->sendMessage(message);
	}
}

int main(int argc, char** argv) {
	try {
		midi_in = std::make_shared<RtMidiIn>();
		midi_out = std::make_shared<RtMidiOut>();

		auto in_names = getPortNames(midi_in);
		auto out_names = getPortNames(midi_out);

		if (argc == 1) {
			displayUsage();
			displayPortNames("Input ports:", in_names);
			displayPortNames("Output ports:", out_names);
		}

		if (argc == 3) {
			unsigned int in_port_idx = parseInt(argv[1]);
			unsigned int out_port_idx = parseInt(argv[2]);
			midi_in->openPort(in_port_idx);
			midi_out->openPort(out_port_idx);
			std::cout << "[" << in_names[in_port_idx] << "] -> [" << out_names[out_port_idx] << "]"
			          << std::endl;

			midi_in->setCallback(&midiCallback);

			while (true) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		} else {
			displayUsage();
		}

	} catch (RtMidiError& error) {
		error.printMessage();
		return 1;
	} catch (std::invalid_argument& error) {
		std::cerr << error.what();
		return 1;
	}

	return 0;
}
