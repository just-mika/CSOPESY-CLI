#pragma once
#include <string>
#include <vector>

#include "Enums.h"

class Process
{
private:
	int GPU;
	std::string GI;
	std::string	CI;
	int pID;                            //process ID
	ProcessType type;
	std::string processName;            // process_name
	unsigned int memUsage;
	State state;

public:
	Process(int GPU, std::string GI, std::string CI, int pID, ProcessType type, std::string processName, unsigned int memUsage, State state = State::READY);

	int getGPU() const;

	std::string getGI() const;

	std::string getCI() const;

	int getPID() const;

	std::string getType() const;

	std::string getProcessName() const;

	unsigned int getMemUsage() const;

	bool isReady() const;
};

typedef std::vector<Process> ProcessList;