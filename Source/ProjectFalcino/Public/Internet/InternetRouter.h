// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InternetRouter.generated.h"

class UInternetConnectedDevice;
class UInternetServer;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTFALCINO_API UInternetRouter : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInternetRouter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Internet Connected Device")
	FString routerID;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Router")
	TArray<UInternetConnectedDevice*> connectedDevices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Router")
	UInternetServer* parentServer = nullptr;
	
	UFUNCTION(BlueprintCallable, Category = "Router")
	void registerDevice(UInternetConnectedDevice* device);

	UFUNCTION(BlueprintCallable, Category = "Router")
	void unRegisterDevice(UInternetConnectedDevice* device);

	UFUNCTION(BlueprintCallable, Category = "Router")
	void routeData(FString senderID, FString targetID, FString data);
};
