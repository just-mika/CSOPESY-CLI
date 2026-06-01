#include "Process.h"

Process::Process(int GPU, std::string GI, std::string CI, int pID, ProcessType type, std::string processName, unsigned int memUsage)
{
	this->GPU = GPU;
	this->GI = GI;
	this->CI = CI;
	this->pID = pID;
	this->type = type;
	this->processName = processName;
	this->memUsage = memUsage;
	this->state = State::READY;
}

int Process::getGPU() const
{
	return GPU;
};

std::string Process::getGI() const
{
	return GI;
};

std::string Process::getCI() const
{
	return CI;
};

int Process::getPID() const
{
	return pID;
};

std::string Process::getType() const
{
	switch (type)
	{
	case ProcessType::C: return "C";
	case ProcessType::G: return "G";
	case ProcessType::CG: return "C+G";
	}
};

std::string Process::getProcessName() const
{
	return processName;
};

unsigned int Process::getMemUsage() const
{
	return memUsage;
};

bool Process::isReady() const
{
	if (this->state == State::READY) return true;
	return false;
}