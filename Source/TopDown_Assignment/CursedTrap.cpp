// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDown_AssignmentCharacter.h"
#include "CursedTrap.h"

void ACursedTrap::NotifyActorBeginOverlap(AActor* OtherActor) 
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ATopDown_AssignmentCharacter* myCharacter = Cast<ATopDown_AssignmentCharacter>(OtherActor);

	if (myCharacter != nullptr) {
		myCharacter->bIsCursed = true;
	}
}
