// Fill out your copyright notice in the Description page of Project Settings.

#include "Internet/InternetConnectedDevice.h"

#include "Internet/InternetRouter.h"

// Sets default values for this component's properties
UInternetConnectedDevice::UInternetConnectedDevice() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	int randomAddress = FMath::RandRange(0, 99);
	deviceID = "192.168.1." + FString::FromInt(randomAddress);
}

// Called when the game starts
void UInternetConnectedDevice::BeginPlay() {
	Super::BeginPlay();

	if (GEngine) {
		const FString debugMessage = FString::Printf(TEXT("DeviceComponent Initialized: %s"), *deviceID);
		GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Green, debugMessage);
	}
}

// Called every frame
void UInternetConnectedDevice::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInternetConnectedDevice::sendData(const FString& targetDeviceID, const FString& data) {
	
	if (isConnected && parentRouter) {
		
		parentRouter -> routeData(deviceID, targetDeviceID, data);

		if (GEngine) {
			FString debugMessage = FString::Printf( TEXT("Device %s sent data through Router to %s: %s"), *deviceID, *targetDeviceID, *data);
			GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, debugMessage);
		}
	} else {
		// Error message if not connected
		if (GEngine) {
			GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Device is not connected to a router!"));
		}
	}
}

void UInternetConnectedDevice::receiveData(const FString& data) {
	receivedData = data;

	if (GEngine) {
		FString debugMessage = FString::Printf(TEXT("Received Data: '%s'"), *receivedData);
		GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, debugMessage);
	}
}
