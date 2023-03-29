// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CR_BaseJet.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACR_BaseJet::ACR_BaseJet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("BodyMeshComponent");
	SetRootComponent(BodyMeshComponent);
	BodyMeshComponent->SetSimulatePhysics(true);
	BodyMeshComponent->SetLinearDamping(0.01f);
	BodyMeshComponent->SetAngularDamping(1.0f);
	BodyMeshComponent->SetEnableGravity(false);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(BodyMeshComponent);
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->SocketOffset = FVector(0.0f, 0.0f, 200.0f);
	SpringArmComponent->bEnableCameraLag = false;
	SpringArmComponent->bEnableCameraRotationLag = true;
	SpringArmComponent->CameraLagSpeed = 10.0f;
	SpringArmComponent->CameraRotationLagSpeed = 4.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeRotation(FRotator(-10.0f, 0.0, 0.0f));
}

// Called when the game starts or when spawned
void ACR_BaseJet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACR_BaseJet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACR_BaseJet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

