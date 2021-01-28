// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TopDown_AssignmentCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDown_AssignmentCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDown_AssignmentCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileOrigin; // This acts as the offset that we usually create all in blueprint (empty Scene component)

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> LinearSpellActor;  

	void Shoot();

	UFUNCTION(BlueprintCallable)
	void StartRoll();

	UFUNCTION(BlueprintCallable)
	void EndRoll();

	UFUNCTION(BlueprintCallable)
	void AreaAttack();

	UFUNCTION(BlueprintImplementableEvent)
	void Attack();

	UPROPERTY(BlueprintReadWrite)
	int HP = 100;

	UPROPERTY(BlueprintReadWrite)
	int Mana = 100;

	UPROPERTY(BlueprintReadWrite)
	bool bIsBusy;

	UPROPERTY(BlueprintReadWrite)
	bool bIsAttackActive;

	UPROPERTY(BlueprintReadWrite)
	bool bIsRolling;

	bool bIsImmune;

	void OnDamage(int damage);

	UPROPERTY(BlueprintReadOnly)
	bool bIsCursed;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

};

