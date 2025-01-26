// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InternetServer.generated.h"

class UInternetRouter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTFALCINO_API UInternetServer : public UActorComponent {
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInternetServer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Server")
	TArray<UInternetRouter*> connectedRouters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Internet Connected Device")
	FString serverID;

	UFUNCTION(BlueprintCallable, Category = "Server")
	void registerRouter(UInternetRouter* router);

	UFUNCTION(BlueprintCallable, Category = "Server")
	void unregisterRouter(UInternetRouter* router);

	UFUNCTION(BlueprintCallable, Category = "Server")
	void routeData(FString senderDeviceID, FString targetDeviceID, FString data);
};
