// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CR_BaseJet.h"
#include "CR_Jet.generated.h"

UCLASS()
class COMBATRACER_API ACR_Jet : public ACR_BaseJet
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACR_Jet();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float StartTrustSpeed = 100000.0;
	
	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float MaxTrustSpeed = 400000.0;

	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float MinTrustSpeed = -100000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float TrustMultiplier = 80000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float Gravity = 981.0f;

	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float Drag = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float RotationSpeed = 60.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	float TrustSpeed = 0.0f;
	float CurrentSpeed = 0.0f;
	float CurrentSpeedInKM = 0.0f;
	float AppliedGravity = 0.0f;

	//Rotation
	float TargetYaw = 0.0f;
	float CurrentYaw = 0.0f;
	float TargetPitch = 0.0f;
	float CurrentPitch = 0.0f;
	float TargetRoll = 0.0f;
	float CurrentRoll = 0.0f;
	
	void UpdatePosition(float DeltaTime);
	
	void UpdateThrust(float Amount);
	void UpdateYaw(float Amount);
	void UpdatePitch(float Amount);
	void UpdateRoll(float Amount);

	void CalculateSpeed(float DeltaTime);
	void PrintVars();
};
