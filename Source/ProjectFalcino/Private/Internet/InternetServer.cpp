// Fill out your copyright notice in the Description page of Project Settings.

#include "Internet/InternetServer.h"
#include "Internet/InternetConnectedDevice.h"
#include "Internet/InternetRouter.h"

// Sets default values for this component's properties
UInternetServer::UInternetServer() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	int randomAddress = FMath::RandRange(0, 99);
	serverID = "192.168.15." + FString::FromInt(randomAddress);
}


// Called when the game starts
void UInternetServer::BeginPlay() {
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Server Component is online!"));
	}
}


// Called every frame
void UInternetServer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UInternetServer::registerRouter(UInternetRouter* router) {
	if (router && !connectedRouters.Contains(router)) {
		connectedRouters.Add(router);
		router->parentServer = this;

		if (GEngine) {
			FString debugMessage = FString::Printf(TEXT("Router registered to server: %s"), *router->routerID);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, debugMessage);
		}
	}
}

void UInternetServer::unregisterRouter(UInternetRouter* router) {
	if (router && connectedRouters.Contains(router)) {
		connectedRouters.Remove(router);
		router->parentServer = nullptr;

		if (GEngine) {
			FString debugMessage = FString::Printf(TEXT("Router unregistered from server: %s"), *router->routerID);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, debugMessage);
		}
	}
}

void UInternetServer::routeData(FString senderDeviceID, FString targetDeviceID, FString data) {
	for (UInternetRouter* router : connectedRouters) {
		if (router) {
			// Check if the target device is connected to this router
			for (UInternetConnectedDevice* device : router->connectedDevices) {
				if (device && device->deviceID.Equals(targetDeviceID)) {
					// Route data to the target router
					router->routeData(senderDeviceID, targetDeviceID, data);

					if (GEngine) {
						FString debugMessage = FString::Printf(TEXT("Server Component routed data: SenderDevice=%s, TargetDevice=%s, Data=%s"), *senderDeviceID, *targetDeviceID, *data);
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, debugMessage);
					}

					return;
				}
			}
		}
	}

	// If no router has the target device
	if (GEngine) {
		FString errorMessage = FString::Printf(TEXT("Server Component failed to route data: TargetDevice=%s not found!"), *targetDeviceID);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, errorMessage);
	}
}
