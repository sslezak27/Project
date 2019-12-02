#include "Camera_Pawn.h"


ACamera_Pawn::ACamera_Pawn(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	//GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;

	cameraComponent = CreateDefaultSubobject<UCamera_Component>(TEXT("Camera Component"));
	//if(&cameraComponent != nullptr)
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "CreatedObject");

}

void ACamera_Pawn::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0,0,200));
}

void ACamera_Pawn::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ACamera_Pawn::MoveForward(const float value)
{
	if (value != 0.f)
	{
		cameraComponent->MoveForward(value);
	}
}

void ACamera_Pawn::MoveRight(const float value)
{
	if (value != 0.f)
	{
		cameraComponent->MoveRight(value);
	}
}

void ACamera_Pawn::OnMouseScrollUp()
{
	cameraComponent->OnZoomIn();
}

void ACamera_Pawn::OnMouseScrollDown()
{
	cameraComponent->OnZoomOut();
}

void ACamera_Pawn::OnMouseRotateY(const float value)
{
	if (value != 0.f)
	{
		cameraComponent->RotateY(value);
	}

}

void ACamera_Pawn::OnMouseRotateX(const float value)
{
	if (value != 0.f)
	{
		cameraComponent->RotateX(value);
	}

}