#pragma once

enum class PerfState { P0, P1, P2, P3, P4, P5, P6, P7, P8 };
enum class DriverModel { WDDM, TCC, NA };
enum class ECCMode { Enabled, Disabled, NA };
enum class ComputeMode { Default, Exclusive, Prohibited, NA };
enum class MIGMode { Enabled, Disabled, NA };
enum class ProcessType { C, G, CG };
enum class State
{
	READY,
	RUNNING,
	FINISHED
};
