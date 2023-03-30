// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/CR_Jet.h"

DEFINE_LOG_CATEGORY_STATIC(LogJet, All, All);

// Sets default values
ACR_Jet::ACR_Jet()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACR_Jet::BeginPlay()
{
	Super::BeginPlay();
	check(BodyMeshComponent);

	ThrustSpeed = StartThrustSpeed;
	CurrentSpeed = StartThrustSpeed;

	BodyMeshComponent->OnComponentHit.AddDynamic(this, &ACR_Jet::OnJetHit);
}

// Called every frame
void ACR_Jet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePosition(DeltaTime);
	PrintVars();
}

void ACR_Jet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Thrust", this, &ACR_Jet::UpdateThrust);
	PlayerInputComponent->BindAxis("UpDown", this, &ACR_Jet::UpdatePitch);
	PlayerInputComponent->BindAxis("RightLeft", this, &ACR_Jet::UpdateRoll);
}

void ACR_Jet::UpdateThrust(float Amount)
{
	const float NewThrustSpeed = Amount * FApp::GetDeltaTime() * ThrustMultiplier * ThrustAcceleration + ThrustSpeed;
	ThrustSpeed = FMath::Clamp(NewThrustSpeed, MinThrustSpeed, MaxThrustSpeed);
}

void ACR_Jet::UpdatePosition(float DeltaTime)
{
	CalculateSpeed(DeltaTime);
	// 	
		// const FVector2D InputRange = FVector2D(0.0f, MinTrustSpeed);
		// const FVector2D OutputRange = FVector2D(Gravity, 0.0f);
		// AppliedGravity = FMath::GetMappedRangeValueClamped(InputRange, OutputRange, CurrentSpeed);
	//
	FVector NewPosition = GetActorForwardVector() * CurrentSpeed * DeltaTime;
	// 	// NewPosition.Z = NewPosition.Z - (AppliedGravity * DeltaTime);
	//
	BodyMeshComponent->SetPhysicsLinearVelocity(NewPosition);
	// 	// AddActorWorldOffset(NewPosition, true);
	// 	
}

void ACR_Jet::UpdatePitch(float Amount)
{
	const float DeltaTime = FApp::GetDeltaTime();
	TargetPitch = Amount;
	CurrentPitch = FMath::FInterpTo(CurrentPitch, TargetPitch, DeltaTime, RotationSpeed);

	const float NewPosition = CurrentPitch * DeltaTime * RotationSpeed;
	AddActorLocalRotation(FRotator(NewPosition, 0.0f, 0.0f));
}

void ACR_Jet::UpdateRoll(float Amount)
{
	const float DeltaTime = FApp::GetDeltaTime();
	TargetRoll = Amount;
	CurrentRoll = FMath::FInterpTo(CurrentRoll, TargetRoll, DeltaTime, RotationSpeed);

	const float NewPosition = CurrentRoll * DeltaTime * RotationSpeed;
	AddActorLocalRotation(FRotator(0.0f, 0.0f, NewPosition));
}

void ACR_Jet::OnJetHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                       FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	const float AngleBetween = FVector::DotProduct(GetActorForwardVector(), Hit.Normal);
	const float AngleBetweenDegrees = FMath::Abs(FMath::RadiansToDegrees(AngleBetween));

	CalculateSpeedOnHit(AngleBetweenDegrees);
}

// void ACR_Jet::UpdateYaw(float Amount)
// {
// 	const float DeltaTime = FApp::GetDeltaTime();
// 	TargetYaw = Amount;
// 	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, RotationSpeed);
//
// 	const float NewPosition = CurrentYaw * DeltaTime * RotationSpeed;
// 	AddActorLocalRotation(FRotator(0.0f, NewPosition, 0.0f));
// }

void ACR_Jet::CalculateSpeed(float DeltaTime)
{
	if (ThrustSpeed < CurrentSpeed)
	{
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed, ThrustSpeed, DeltaTime, Drag);
	}
	else
	{
		CurrentSpeed = ThrustSpeed;
	}
}

void ACR_Jet::CalculateSpeedOnHit(float HitDegrees)
{
	if (!GetWorld()) return;
	
	if (HitDegrees > MaxAngleToDestroyOnHit)
	{
		StopSpeed();
	}
	else
	{
		const FVector2D InputRange = FVector2D(0.0f, MaxAngleToDestroyOnHit);
		const FVector2D OutputRange = FVector2D(1, 0.0f);
		const float SpeedModification = FMath::GetMappedRangeValueClamped(InputRange, OutputRange, HitDegrees);
		ThrustSpeed = ThrustSpeed * SpeedModification;
	}
}

void ACR_Jet::StopSpeed()
{
	ThrustSpeed = 0.0f;
	CurrentSpeed = 0.0f;
}

void ACR_Jet::PrintVars()
{
	UE_LOG(LogJet, Display, TEXT("CurrentSpeed: %f"), CurrentSpeed);
	UE_LOG(LogJet, Display, TEXT("TrustSpeed: %f"), ThrustSpeed);
}
