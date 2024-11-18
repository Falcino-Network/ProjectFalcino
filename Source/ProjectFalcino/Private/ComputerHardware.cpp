// Fill out your copyright notice in the Description page of Project Settings.


#include "ComputerHardware.h"

UComputerHardware::UComputerHardware() {

	//CPU
	CPUCores = 1;
	CPUFrequency = 10.0;
	CPUSpeed = CPUCores * CPUFrequency;
	
	//RAM
	RAMSize = 1;
	RAMFrequency = 10.0;
	RAMSpeed = RAMSize * RAMFrequency;

	ComputerSpeed = CPUSpeed * RAMSpeed;
	
}

UComputerHardware::~UComputerHardware() {

}
