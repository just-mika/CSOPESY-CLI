#pragma once
#include "Enums.h"
#include <string>
#include <vector>

class GPU
{
private:
	int index;
	std::string name;
	int fanPercent;
	int temp;
	PerfState perfState;
	DriverModel driverModel;
	int powerUsage;
	int powerCap;
	
	std::string busID;
	bool displayActive;
	unsigned int memUsed;
	unsigned int memTotal;
	
	int gpuUtilPercent;
	ECCMode eccMode;
	ComputeMode computeMode;
	MIGMode migMode;

public:
	GPU(
		int index, std::string name, int fanPercent, int temp, PerfState perfState, DriverModel driverModel, int powerUsage, int powerCap, 
		std::string busID, bool displayActive, unsigned int memUsed, unsigned int memTotal, 
		int gpuUtilPercent, ECCMode eccMode, ComputeMode computeMode, MIGMode migMode
	);

	int getIndex() const;
	std::string getName()const;
	int getFanPercent()const;
	int getTemp()const;
	std::string getPerfState() const;
	std::string getDriverModel() const;
	int getPowerUsage() const;
	int getPowerCap() const;

	std::string getBusID() const;
	bool isDisplayActive() const;
	unsigned int getMemUsed() const;
	unsigned int getMemTotal() const;

	int getGpuUtil() const;
	std::string getEccMode() const;
	std::string getComputeMode() const;
	std::string getMigMode() const;

};

typedef std::vector<GPU> GPUList;