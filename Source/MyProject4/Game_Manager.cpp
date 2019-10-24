// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_Manager.h"
#include "Characters/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
AGame_Manager::AGame_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGame_Manager::BeginPlay()
{
	Super::BeginPlay();
	Begin_Combat();
	
}

// Called every frame
void AGame_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGame_Manager::Begin_Combat()
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

