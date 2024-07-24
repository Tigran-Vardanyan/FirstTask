﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase::MoveForward(float Value)
{
	if (Controller == nullptr ||  Value == 0.f)
	{
		return;
	}

	const FRotator Rotation = Controller->GetControlRotation(); 
	const FRotator RotationYaw(0.f,Rotation.Yaw,0.f);
	const FVector Direction = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction,Value);
}

void ACharacterBase::MoveRight(float Value)
{
	
	if (Controller == nullptr || Value == 0.f)
	{
		return;
	}

	const FRotator Rotation = Controller->GetControlRotation(); 
	const FRotator RotationYaw(0.f,Rotation.Yaw,0.f);
	const FVector Direction = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction,Value);
}

void ACharacterBase::LookUp(float Value)
{
	if (Value == 0.f)
	{
		return;
	}
	AddControllerPitchInput(Value);
}

void ACharacterBase::Turn(float Value)
{
	if (Value == 0.f)
	{
		return;
	}
	AddControllerYawInput(Value);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

