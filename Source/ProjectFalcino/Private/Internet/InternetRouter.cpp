// Fill out your copyright notice in the Description page of Project Settings.


#include "Internet/InternetRouter.h"
#include "Internet/InternetConnectedDevice.h"
#include "Internet/InternetServer.h"

// Sets default values for this component's properties
UInternetRouter::UInternetRouter() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	int randomAddress = FMath::RandRange(0, 99);
	routerID = "192.168.10." + FString::FromInt(randomAddress);
}

// Called when the game starts
void UInternetRouter::BeginPlay() {
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Router Component Initialized"));
	}
}

// Called every frame
void UInternetRouter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInternetRouter::registerDevice(UInternetConnectedDevice* device) {
	if (device && !connectedDevices.Contains(device)) {
		connectedDevices.Add(device);
		device->parentRouter = this;

		if (GEngine) {
			FString DebugMessage = FString::Printf(TEXT("Device Registered to Router: %s"), *device->deviceID);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, DebugMessage);
		}

		device->isConnected = true;
	}
}

void UInternetRouter::unRegisterDevice(UInternetConnectedDevice* device) {
	if (device && connectedDevices.Contains(device)) {
		connectedDevices.Remove(device);
		device->parentRouter = nullptr;

		// Debug message
		if (GEngine) {
			FString DebugMessage = FString::Printf(TEXT("Device Unregistered from Router: %s"), *device->deviceID);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, DebugMessage);
		}

		device->isConnected = false;
	}
}

void UInternetRouter::routeData(FString senderID, FString targetID, FString data) {
	// Check for local device
	for (UInternetConnectedDevice* device : connectedDevices) {
		if (device && device->deviceID.Equals(targetID)) {
			device->receiveData(data);

			if (GEngine) {
				FString debugMessage = FString::Printf(TEXT("Router routed data locally: Sender=%s, Target=%s, Data=%s"), *senderID, *targetID, *data);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, debugMessage);
			}
			return;
		}
	}

	// If the target device is not local, forward the data to the server
	if (parentServer) {
		parentServer->routeData(senderID, targetID, data);

		if (GEngine) {
			FString debugMessage = FString::Printf(TEXT("Router forwarded data to server: Sender=%s, Target=%s, Data=%s"), *senderID, *targetID, *data);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, debugMessage);
		}
	} else {
		// No server connected
		if (GEngine) {
			FString errorMessage = FString::Printf(TEXT("Router failed to forward data: No server connected! Target=%s"), *targetID);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, errorMessage);
		}
	}
}

