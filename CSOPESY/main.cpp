#include "CLI.h"
#include <iostream>
#include "Process.h"
#include "GPU.h"
#include <vector>


struct SystemInfo {
    std::string nvidiaSmiVersion;
    std::string driverVersion;
    std::string cudaVersion;
    GPUList gpus;
    ProcessList processes;
};

std::unique_ptr<ProcessList> initializeProcesses()
{
    std::unique_ptr<ProcessList> p = std::make_unique<ProcessList>();

    p->push_back(Process(0, "N/A", "N/A", 184200, ProcessType::C, "python3", 8204));
    p->push_back(Process(0, "N/A", "N/A", 2391, ProcessType::G, "genshinimpact.exe", 4096));
    p->push_back(Process(0, "N/A", "N/A", 3107, ProcessType::G, "Blender.exe", 2048));
    p->push_back(Process(0, "N/A", "N/A", 4452, ProcessType::CG, "VSCode.exe", 2816));
    p->push_back(Process(0, "N/A", "N/A", 5890, ProcessType::G, "chrome.exe", 312));
	
    return p;
}

std::unique_ptr<GPUList> initializeGPUs()
{
    std::unique_ptr<GPUList> g = std::make_unique<GPUList>();
    g->push_back(GPU(
        0, "NVIDIA GeForce RTX 3050 6GB Laptop GPU", -1, 52, PerfState::P0, DriverModel::WDDM, 10, 95,
        "00000000:01:00.0", false, 0, 6144,
        0, ECCMode::NA, ComputeMode::Default, MIGMode::NA
    ));
    g->push_back(GPU(
	    1, "NVIDIA GeForce RTX 4090", 42, 78, PerfState::P2, DriverModel::WDDM, 285, 450,
	    "00000000:02:00.0", false, 18432, 24576,
	    87, ECCMode::Disabled, ComputeMode::Default, MIGMode::Disabled
	));

	g->push_back(GPU(
	    2, "NVIDIA Tesla T4", 0, 52, PerfState::P0, DriverModel::TCC, 70, 70,
	    "00000000:03:00.0", false, 8192, 16384,
	    60, ECCMode::Enabled, ComputeMode::Exclusive, MIGMode::Disabled
	));
    return g;
}

int main()
{
    SystemInfo sys;
    sys.nvidiaSmiVersion = "581.86";
    sys.driverVersion = "581.86";
    sys.cudaVersion = "13.0";
	sys.gpus = *initializeGPUs();
    sys.processes = *initializeProcesses();

    printDateTime();
    printDriverInfo(sys.nvidiaSmiVersion, sys.driverVersion, sys.cudaVersion);
    printGPUs(sys.gpus);

    std::cout << std::endl;
    printProcesses(sys.processes);

    return 0;
}