#include "GPU.h"

GPU::GPU(
	int index, std::string name, int fanPercent, int temp, PerfState perfState, DriverModel driverModel, int powerUsage, int powerCap,
	std::string busID, bool displayActive, unsigned int memUsed, unsigned int memTotal,
	int gpuUtilPercent, ECCMode eccMode, ComputeMode computeMode, MIGMode migMode
)
{
	this->index = index;
	this->name = name;
	this->fanPercent = fanPercent;
	this->temp = temp;
	this->perfState = perfState;
	this->driverModel = driverModel;
	this->powerUsage = powerUsage;
	this->powerCap = powerCap;
	this->busID = busID;
	this->displayActive = displayActive;
	this->memUsed = memUsed;
	this->memTotal = memTotal;
	this->gpuUtilPercent = gpuUtilPercent;
	this->eccMode = eccMode;
	this->computeMode = computeMode;
	this->migMode = migMode;
}

int GPU::getIndex() const
{
	return index;
};
std::string GPU::getName() const
{
	return name;
};
int GPU::getFanPercent() const
{
	return fanPercent;
};
int GPU::getTemp() const
{
	return temp;
};

std::string GPU::getPerfState() const 
{
	static const char* names[] = { "P0","P1","P2","P3","P4","P5","P6","P7","P8" };
	return names[static_cast<int>(perfState)];
}

std::string GPU::getDriverModel() const
{
	switch (driverModel)
	{
	case DriverModel::WDDM: return "WDDM";
	case DriverModel::TCC: return "TCC";
	case DriverModel::NA: return "N/A";
	}
};

int GPU::getPowerUsage() const
{
	return powerUsage;
};
int GPU::getPowerCap() const
{
	return powerCap;
};

std::string GPU::getBusID() const
{
	return busID;
}
bool GPU::isDisplayActive() const
{
	return displayActive;
}
unsigned int GPU::getMemUsed() const
{
	return memUsed;
}
unsigned int GPU::getMemTotal() const
{
	return memTotal;
}

int GPU::getGpuUtil() const
{
	return gpuUtilPercent;
}
std::string GPU::getEccMode() const
{
	switch (eccMode)
	{
	case ECCMode::Enabled: return "Enabled";
	case ECCMode::Disabled: return "Disabled";
	case ECCMode::NA: return "N/A";
	}
}
std::string GPU::getComputeMode() const
{
	switch (computeMode)
	{
	case ComputeMode::Default: return "Default";
	case ComputeMode::Prohibited: return "Prohibited";
	case ComputeMode::Exclusive: return "Exclusive";
	case ComputeMode::NA: return "N/A";
	}
}

std::string GPU::getMigMode() const
{
	switch (migMode)
	{
	case MIGMode::Enabled: return "Enabled";
	case MIGMode::Disabled: return "Disabled";
	case MIGMode::NA: return "N/A";
	}
}