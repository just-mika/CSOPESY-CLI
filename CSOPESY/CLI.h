#pragma once
#include <iomanip>
#include <time.h>
#include <iostream>
#include <vector>
#include "GPU.h"
#include "Process.h"
#include <Windows.h>

typedef std::string String;

CONSOLE_SCREEN_BUFFER_INFO csbi;

void setCursorPosition(int posX, int posY)
{
    COORD coord;
    coord.X = posX;
    coord.Y = posY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int getYPos()
{
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}

void printAtX(int posX, int width, const String text, bool left = false)
{
    DWORD written;
	int posY = getYPos();

    // clear the region first
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', width, 
        COORD{(SHORT)posX, (SHORT) posY}, &written);

    // then write the text (truncated to width)
    setCursorPosition(posX, posY);

    if (left)
        std::cout << std::left << std::setw(width) << text.substr(0, width);
    else
        std::cout << std::right << std::setw(width) << text.substr(0, width);
}

std::string truncateName(const std::string& str, int limit)
{
    if (str.length() > limit)
        return str.substr(0, limit - 3) + "...";
    return str;
}

void printDateTime()
{
    time_t t = time(0);
    char str_time[26];
    ctime_s(str_time, sizeof(str_time), &t);

    std::cout << str_time;
}

void printDriverInfo(String nvidiaSmiVer, String driverVer, String cudaVer)
{
    std::cout << "+-----------------------------------------------------------------------------------------+\n";

	std::cout << "| NVIDIA-SMI";
    printAtX(13, 10, nvidiaSmiVer);

    setCursorPosition(35, 2);
    std::cout << " Driver Version:";
    printAtX(52, 10, driverVer);

    setCursorPosition(67, 2);
    std::cout << " CUDA Version:";
    printAtX(82, 6, cudaVer);
    printAtX(90, 2, "|\n");
}

void printGPUs(GPUList gpus)
{
    std::cout << "+-----------------------------------------+------------------------+----------------------+\n";
    std::cout << "| GPU  Name";

    setCursorPosition(29, 4);
	std::cout << "Driver-Model |";

    setCursorPosition(43, 4);
    std::cout << " Bus-Id";

    setCursorPosition(60, 4);
    std::cout << "Disp.A ";
    std::cout << "| Volatile Uncorr. ECC |\n";

    std::cout << "| Fan  Temp   Perf";

    setCursorPosition(28, 5);
    std::cout << "Pwr:Usage/Cap |";

    setCursorPosition(54, 5);
    std::cout << "Memory-Usage ";
    std::cout << "| GPU-Util  Compute M. |\n";

    std::cout << "|";

    setCursorPosition(42, 6); 
	std::cout << "|";

    setCursorPosition(67, 6); 
	std::cout << "|";

    setCursorPosition(83, 6);
    std::cout << "MIG M. |";
	std::cout << "\n";
    std::cout << "|=========================================+========================+======================|\n";
    
	if (gpus.empty())
    {
        std::cout << "| No GPUs found";
        setCursorPosition(90, 8);
        std::cout << "|\n";
        std::cout << "+-----------------------------------------+------------------------+----------------------+\n";
        return;
    }
    else {
        for (const GPU& gpu : gpus)
        {
            std::cout << "| ";
            int i = gpu.getIndex();
            printAtX(2, 3, std::to_string(gpu.getIndex()));
            printAtX(7, 27, truncateName(gpu.getName(), 27), true);
            printAtX(36, 4, gpu.getDriverModel());
            std::cout << "  |";
            printAtX(45, 17, gpu.getBusID());
            printAtX(63, 3, gpu.isDisplayActive() ? "On" : "Off");
            std::cout << " |";
            printAtX(81, 8, gpu.getEccMode());
            std::cout << " |\n";

			String fanPercent = gpu.getFanPercent() >= 0 ? std::to_string(gpu.getFanPercent()) + "%" : "N/A";

            std::cout << "|";
            printAtX(2, 3, fanPercent);
            printAtX(7, 3, std::to_string(gpu.getTemp()) + "C");
            printAtX(15, 2, gpu.getPerfState());
            printAtX(28, 5, std::to_string(gpu.getPowerUsage()) + "W");
            std::cout << " / ";
            printAtX(36, 5, std::to_string(gpu.getPowerCap()) + "W");
            std::cout << " |";
            printAtX(44, 9, std::to_string(gpu.getMemUsed()) + "MiB");
            std::cout << " / ";
            printAtX(57, 9, std::to_string(gpu.getMemTotal()) + "MiB");
            std::cout << " |";
			printAtX(72, 4, std::to_string(gpu.getGpuUtil()) + "%");
			printAtX(79, 10, gpu.getComputeMode());
            std::cout << " |\n";

            std::cout << "|";
            setCursorPosition(42, 10 + (i * 4));
            std::cout << "|";
            setCursorPosition(67, 10 + (i * 4));
            std::cout << "|";
            printAtX(81, 8, gpu.getMigMode());
            std::cout << " |\n";

            std::cout << "+-----------------------------------------+------------------------+----------------------+\n";
        }
    }
}

void printProcesses(ProcessList processes)
{
    std::cout << "+-----------------------------------------------------------------------------------------+\n";
    std::cout << "| Processes:";
    setCursorPosition(90, getYPos());
	std::cout << "|\n";
    std::cout << "|  GPU   GI   CI";
    setCursorPosition(30, getYPos());
    std::cout << "PID   Type   Process name";
    setCursorPosition(79, getYPos());
    std::cout << "GPU Memory |\n";
    std::cout << "|        ID   ID ";
    setCursorPosition(79, getYPos());
	std::cout << "Usage      |\n"; 
	std::cout << "+-----------------------------------------------------------------------------------------+\n";

    if (processes.empty())
    {
        std::cout << "| No running processes found";
        setCursorPosition(90, getYPos());
        std::cout << "|\n";
    }
    else
    {
	    for (const Process& p : processes)
	    {
            std::cout << "| ";
            printAtX(2, 3, std::to_string(p.getGPU()));
			printAtX(8, 4, p.getGI());
			printAtX(13, 4, p.getCI());
			printAtX(26, 7, std::to_string(p.getPID()));
			printAtX(37, 3, p.getType());
			printAtX(43, 35, 
                truncateName(p.getProcessName(), 35), true);
			printAtX(79, 10, std::to_string(p.getMemUsage()) + "MiB");
			std::cout << " |\n";
	    }
    }
    std::cout << "+-----------------------------------------------------------------------------------------+";
}
