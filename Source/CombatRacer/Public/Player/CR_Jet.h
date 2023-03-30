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
	float StartThrustSpeed = 0.0;
	
	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float MaxThrustSpeed = 800000.0;

	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float MinThrustSpeed = -200000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float ThrustAcceleration = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float ThrustMultiplier = 80000.0f;

	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float Drag = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category="Jet Movement")
	float RotationSpeed = 60.0f;

	UPROPERTY(EditDefaultsOnly, Category="Jet Damage")
	float MaxAngleToDestroyOnHit = 40.0f;

	UPROPERTY(EditDefaultsOnly, Category="Jet Damage")
	float MinSpeedToApplyDamage = 300000.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	//Thrust
	float ThrustSpeed = 0.0f;
	float CurrentSpeed = 0.0f;

	//Rotation
	float TargetPitch = 0.0f;
	float CurrentPitch = 0.0f;
	float TargetRoll = 0.0f;
	float CurrentRoll = 0.0f;
	// float TargetYaw = 0.0f;
	// float CurrentYaw = 0.0f;
	
	void UpdateThrust(float Amount);
	void CalculateSpeed(float DeltaTime);
	void CalculateSpeedOnHit(float HitDegrees);
	void StopSpeed();

	void UpdatePosition(float DeltaTime);
	
	void UpdatePitch(float Amount);
	void UpdateRoll(float Amount);
	// void UpdateYaw(float Amount);

	UFUNCTION()
	void OnJetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						 FVector NormalImpulse, const FHitResult& Hit);

	void PrintVars();
};
