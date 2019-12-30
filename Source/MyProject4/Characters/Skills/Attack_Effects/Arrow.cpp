// Fill out your copyright notice in the Description page of Project Settings.

#include "Arrow.h"

// Sets default values
AArrow::AArrow()
{
	PrimaryActorTick.bCanEverTick = true;
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));

	Arrow->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DecalMaterialAsset(TEXT("Material'/Game/CloseCombat/Weapon/Swords/SwordTest/Meshes/SM_Sword.SM_Sword'"));
	if (DecalMaterialAsset.Succeeded())
	{
		Arrow->SetStaticMesh(DecalMaterialAsset.Object);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "SUCCES");

	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "FAILED");
}
AArrow::AArrow(float SpeedY, float Speedx, FRotator rotacja)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));

	Arrow->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DecalMaterialAsset(TEXT("Material'/Game/CloseCombat/Weapon/Swords/SwordTest/Meshes/SM_Sword.SM_Sword'"));
	if (DecalMaterialAsset.Succeeded())
	{
		Arrow->SetStaticMesh(DecalMaterialAsset.Object);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "SUCCES");

	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "FAILED");
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
/**
*/

void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Alive)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "FLYING");
		FVector CurrentLocation = GetActorLocation();
		FRotator CurrentRotation = GetActorRotation();
		SetActorLocation(FVector(CurrentLocation.X + (Vx * DeltaTime*sin(CurrentRotation.Roll)), CurrentLocation.Y + (Vx * DeltaTime * sin(CurrentRotation.Yaw)), CurrentLocation.Z + Vy * DeltaTime),true,Colizja);
		Vy -= gravity * DeltaTime;
		
		SetActorRotation(FRotator(CurrentRotation.Roll, CurrentRotation.Yaw, CurrentRotation.Pitch));
	}

}

void AArrow::Setup_Component(float SpeedY, float Speedx, FRotator rotacja)
{
	Vx = Speedx;
	Vy = SpeedY;
	SetActorRotation(rotacja);
}

