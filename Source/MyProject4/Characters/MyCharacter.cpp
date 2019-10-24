// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Move_My_Character(FVector(500, -120, 108));
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::Move_My_Character(const FVector& position)
{
	UNavigationPath* path = UNavigationSystemV1::FindPathToLocationSynchronously(this, this->GetActorLocation(), position);

	if (path && path->IsValid())
	{
		FAIMoveRequest req;
		req.SetAcceptanceRadius(50);
		req.SetUsePathfinding(true);

		AAIController* ai = Cast<AAIController>(this->GetController());
		if (ai)
		{
			ai->RequestMove(req, path->GetPath());
		}
	}
}

