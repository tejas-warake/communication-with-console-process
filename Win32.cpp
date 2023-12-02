// Platform dependent (Windows OS).
#include "Win32.h"

WIN_32::IPC_PIPE::IPC_PIPE() {
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	
	if (!CreatePipe(&stdinRead, &stdinWrite, &sa, 0)) {
		printf("Pipe creation failed: %d\n", GetLastError());
		exit(0);
	}
	if (!CreatePipe(&stdoutRead, &stdoutWrite, &sa, 0)) {
		printf("Pipe creation failed: %d\n", GetLastError());
		exit(0);
	}

	si.hStdOutput = stdoutWrite;
	si.hStdInput = stdinRead;
	si.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

	if (!CreateProcess(
		(LPWSTR)L"<path to program>",
		(LPWSTR)L"<additional args>",
		NULL,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	))
	{
		printf("IPC failed%d\n", GetLastError());
		exit(0);
	}

	CloseHandle(stdinRead);
	CloseHandle(stdoutWrite);
}

void WIN_32::IPC_PIPE::write(std::string input) {
	DWORD bytesWritten = 0;
	if (!WriteFile(stdinWrite, input.c_str(), input.length(), &bytesWritten, NULL)) {
		printf("Write Failed: %d\n", GetLastError());
		exit(0);
	}
	printf("Written:%s  Bytes Written:%d\n", input.c_str(), bytesWritten);
}

std::vector<std::string> WIN_32::IPC_PIPE::read() {
	DWORD bytesRead = 0;
	char buffer[4096];
	// Sleep(1000);
	if (!ReadFile(stdoutRead, buffer, sizeof(buffer), &bytesRead, nullptr)) {
		printf("Read Failed: %d\n", GetLastError());
		exit(0);
	}
	printf("Bytes Read:%d\n", bytesRead);
	std::vector<std::string> response;
	std::stringstream bufferStream(std::string(buffer, bytesRead));
	std::string line;
	while (std::getline(bufferStream, line))
	{
		response.push_back(line);
	}
	return response;
}

WIN_32::IPC_PIPE::~IPC_PIPE() {
	CloseHandle(stdinWrite);
	CloseHandle(stdoutRead);
}