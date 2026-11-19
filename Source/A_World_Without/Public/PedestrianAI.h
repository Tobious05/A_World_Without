// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PedestrianAI.generated.h"

UENUM(BlueprintType)
enum class EPedestrianState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Walking UMETA(DisplayName = "Walking"),
	Fleeing UMETA(DisplayName = "Fleeing")
};


UCLASS()
class A_WORLD_WITHOUT_API APedestrianAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APedestrianAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The current state of the AI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings")
	EPedestrianState CurrentState;

	//How fast the AI walks normally
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Settings")
	float WalkSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AI Logic")
	void MoveToWaypoint();

	UFUNCTION(BlueprintCallable, Category = "AI Logic")
	void Flee(FVector ThreatLocation);

	UFUNCTION(BlueprintCallable, Category = "AI Logic")
	virtual void HaltMovement();		//virtual so the criminal AI child class can override this and not react to devices

	UFUNCTION(BlueprintCallable, Category = "AI Logic")
	void ResumeMovement();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "AI Interaction")
	virtual void ReactToLRAD();

};
