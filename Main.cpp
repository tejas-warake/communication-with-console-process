#include <iostream>
#include "Win32.h"
#define LOG_RESPONSE(res) for (std::string it : res) std::cout<<it<<std::endl;

int main(int argc, _TCHAR* argv[]) {
	std::vector<std::string> response;

	IPC_PIPE *ob = new IPC_PIPE();
	ob->write("Hii");
	response = ob->read();
	LOG_RESPONSE(response);
	return 0;
}