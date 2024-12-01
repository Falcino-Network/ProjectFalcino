// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComputerApps.generated.h"

class UWidget;
class UTexture2D;

USTRUCT()
struct FComputerApps : public FTableRowBase {

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="ComputerApps")
	UTexture2D* appIcon;

	UPROPERTY(EditDefaultsOnly, Category="ComputerApps")
	TSubclassOf<UWidget> appWindow;

	UPROPERTY(EditDefaultsOnly, Category="ComputerApps")
	int cpuUsage;

	UPROPERTY(EditDefaultsOnly, Category="ComputerApps")
	int ramUsage;
	
};
