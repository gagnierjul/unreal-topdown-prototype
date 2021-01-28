// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TOPDOWN_ASSIGNMENT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

	float HitValue;

	UFUNCTION(BlueprintCallable)
	void OnHit();

	UPROPERTY(BlueprintReadWrite)
	int HP = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void CheckIsDead();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int DamageValue);
};
