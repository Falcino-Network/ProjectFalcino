// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComputerHardware.generated.h"

UCLASS(BlueprintType, Blueprintable)
class PROJECTFALCINO_API UComputerHardware : public UObject {
	
	GENERATED_BODY()

public:

	//Vars
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ComputerHardware")
	float ComputerSpeed;
	
	//CPU
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ComputerHardware")
	int CPUCores;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ComputerHardware")
	float CPUFrequency;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ComputerHardware")
	float CPUSpeed;

	//RAM
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ComputerHardware")
	int RAMSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ComputerHardware")
	float RAMFrequency;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ComputerHardware")
	float RAMSpeed;
	
	//Methods
	
	UComputerHardware();
	~UComputerHardware();
	
};