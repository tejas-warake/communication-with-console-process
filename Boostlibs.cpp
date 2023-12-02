// Platfor Independent (Works on all OS).

#include "Boostlibs.h"

BOOST::IPC_PIPE::IPC_PIPE() {
	std::string process = "";
	c = bp::child(process, bp::std_out > out, bp::std_in < in);
}

void BOOST::IPC_PIPE::write(std::string input) {
	in << input;
	in.close();
}

std::vector<std::string> BOOST::IPC_PIPE::read() {
	std::vector<std::string> result;
	std::string line;

	// For Async we can use read_until() or async_read_until().
	while (std::getline(out, line) && !line.empty()) {
		std::replace(line.begin(), line.end(), '\r', '\n');
		result.push_back(line);
	}
	return result;
}

BOOST::IPC_PIPE::~IPC_PIPE() {
	c.terminate();
}