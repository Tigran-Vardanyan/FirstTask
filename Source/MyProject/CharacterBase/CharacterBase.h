// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class MYPROJECT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Component")
	class USkeletalMeshComponent* Weapon;

	UPROPERTY(Category = "AI",BlueprintReadOnly)
	bool Death = false;
	
	UPROPERTY(Category = "AI",BlueprintReadOnly)
	float Health = 100.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Component")
	float BaseDmage = 0.1f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void MoveForward( float Value);
	UFUNCTION(BlueprintCallable)
	void MoveRight( float Value);
	UFUNCTION(BlueprintCallable)
	void LookUp( float Value);
	UFUNCTION(BlueprintCallable)
	void Turn( float Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
