// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDown_AssignmentPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "TopDown_AssignmentCharacter.h"
#include "Engine/World.h"

ATopDown_AssignmentPlayerController::ATopDown_AssignmentPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATopDown_AssignmentPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ATopDown_AssignmentPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATopDown_AssignmentPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATopDown_AssignmentPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATopDown_AssignmentPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATopDown_AssignmentPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ATopDown_AssignmentPlayerController::OnResetVR);

	InputComponent->BindAction("LinearRangedAttack", IE_Pressed, this, &ATopDown_AssignmentPlayerController::OnShoot);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ATopDown_AssignmentPlayerController::OnAttack);

	InputComponent->BindAction("AreaAttack", IE_Pressed, this, &ATopDown_AssignmentPlayerController::OnAreaAttack);
}

void ATopDown_AssignmentPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATopDown_AssignmentPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ATopDown_AssignmentCharacter* MyPawn = Cast<ATopDown_AssignmentCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ATopDown_AssignmentPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ATopDown_AssignmentPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ATopDown_AssignmentPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ATopDown_AssignmentPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ATopDown_AssignmentPlayerController::OnShoot()
{
	//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, TEXT("Bang"));
	auto MyCharacter = Cast< ATopDown_AssignmentCharacter>(GetPawn());

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		FVector Direction = Hit.ImpactPoint - MyCharacter->GetActorLocation();
		Direction.Z = 0;
		MyCharacter->SetActorRotation(FRotationMatrix::MakeFromX(Direction).Rotator());
	}

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyCharacter->GetActorLocation());
	MyCharacter->Mana -= 5;
	MyCharacter->Shoot();
}

void ATopDown_AssignmentPlayerController::OnAttack()
{
	//GEngine->AddOnScreenDebugMessage(0, 2, FColor::Blue, TEXT("Swoosh"));

	auto MyCharacter = Cast< ATopDown_AssignmentCharacter>(GetPawn());

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		FVector Direction = Hit.ImpactPoint - MyCharacter->GetActorLocation();
		Direction.Z = 0;
		MyCharacter->SetActorRotation(FRotationMatrix::MakeFromX(Direction).Rotator());
	}

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyCharacter->GetActorLocation());

	MyCharacter->Attack();
}

void ATopDown_AssignmentPlayerController::OnAreaAttack()
{
	auto MyCharacter = Cast< ATopDown_AssignmentCharacter>(GetPawn());

	MyCharacter->AreaAttack();
}
