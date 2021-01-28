// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "CursedTrap.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWN_ASSIGNMENT_API ACursedTrap : public ATrap
{
	GENERATED_BODY()

public:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
