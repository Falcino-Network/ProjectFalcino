// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComputerApps.generated.h"

class UWidget;
class UTexture2D;

USTRUCT()
struct FComputerApps : public FTableRowBase {

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ComputerApps")
	UTexture2D* appIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ComputerApps")
	TSubclassOf<UWidget> appWindow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ComputerApps")
	int cpuUsage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ComputerApps")
	int ramUsage;
	
};
