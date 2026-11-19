// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDevice.generated.h"

UCLASS()
class A_WORLD_WITHOUT_API AInteractableDevice : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableDevice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle CooldownTimerHandle;	//handles timer for cooldown

	void ResetCooldown();	//resets cooldown once timer ends

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")	//whether device is on or off
	bool bIsActive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction|Cooldown")		//whether device is on cooldown
	bool bIsOnCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Cooldown")		//how long device is on cooldown
	float CooldownDuration;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")	//native event called to trigger events of different devices
	void TriggerDevice();

	//function will start a cooldown for devices so they cant be spam clicked
	UFUNCTION(BlueprintCallable, Category = "Interaction|Cooldown")
	void StartCooldown();

	//function to display the cooldown timer
	UFUNCTION(BlueprintPure, Category = "Interaction|Cooldown")
	float GetRemainingCooldown() const;

};
