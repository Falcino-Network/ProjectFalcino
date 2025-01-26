// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InternetConnectedDevice.generated.h"

class UInternetRouter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTFALCINO_API UInternetConnectedDevice : public UActorComponent {
	GENERATED_BODY()

public:
	
	UInternetConnectedDevice();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Internet Connected Device")
	FString deviceID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Internet Connected Device")
	bool isConnected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Internet Connected Device")
	FString receivedData = "";

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Internet Connected Device")
	UInternetRouter* parentRouter = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Internet Connected Device")
	void sendData(const FString& targetDeviceID, const FString& data);

	UFUNCTION(BlueprintCallable, Category = "Internet Connected Device")
	void receiveData(const FString& data);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
