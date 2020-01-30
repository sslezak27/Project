// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager_laptop.h"
#include "Characters/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
AGameManager_laptop::AGameManager_laptop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameManager_laptop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameManager_laptop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameManager_laptop::Begin_Combat()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("3333333"));
	//TArray<AActor*> FoundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass, FoundActors);
	for (TActorIterator<AMyCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("22222211111"));
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (*ActorItr != nullptr)
		{
			ActorItr->Move_My_Character(FVector(500, -120, 108));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, ActorItr->GetActorLocation().ToString());
		}
	}
	//for (AMyCharacter* TActor : FoundActors)
	//	{
	//		AMyCharacter* MyActor = Cast<AMyCharacter*>(TActor);

	//		if (MyActor != nullptr)
	//			TActor::Move_My_Character(FVector(500, -120, 30));
	//	}
}

