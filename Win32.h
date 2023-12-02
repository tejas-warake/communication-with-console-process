#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <tchar.h>

namespace WIN_32 {
	class IPC_PIPE {
	private:
		SECURITY_ATTRIBUTES sa;
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		HANDLE stdinRead, stdinWrite, stdoutRead, stdoutWrite;

	public:
		IPC_PIPE();
		~IPC_PIPE();
		void write(std::string);
		std::vector<std::string> read();
	};
}