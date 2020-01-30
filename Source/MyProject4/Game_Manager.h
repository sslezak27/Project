// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Standing_Position.h"
#include "Standing_Position_AI.h"
#include "Characters/AI_Character/AI_Character.h"
#include "Characters/Player_Characters/Player_Character.h"
#include "Characters/Controllers/AI_Controller.h"
#include "Managers/Combat_Manager.h"
#include "HUD/A_Hud.h"

#include "Game_Manager.generated.h"


UCLASS()
class MYPROJECT4_API AGame_Manager : public AActor
{
	GENERATED_BODY()
		int16 Turn_Counter = 0;
public:	
	// Sets default values for this actor's properties
	AGame_Manager();
	int Turn_Done[7] = {};
	AA_HUD* HUD_ = nullptr;
	//TActorIterator<AMyCharacter>* Characters[7] = {};
	TArray<AMyCharacter*> Characters;
	bool Player_Turn = false;    //Obs³uga tury gracza
	void Move_Player(FVector &Location);
	void Attack_Player(AMyCharacter* Target);
	void End_Player_Turn();
	void Reset_Player_Targets();
	bool Can_Player_Aim();
	void Player_Aim(FVector Location);
	void Player_Shoot(FVector Location);
	void Player_End_Aim();
	void Begin_Combat();


	UFUNCTION()
		void Spawn_Player_Actors(int number, TArray<int> bounds);
	UFUNCTION()
		void Spawn_AI_Actors(int number, TArray<int> bounds);

 
	TArray<AAI_Character*> AI_Characters;
	TArray<APlayer_Character*> Player_Characters;


private:
	//UClass* PlayerController = APlayer_Controller::StaticClass();
	UClass* AIController = AAI_Controller::StaticClass();
	AAI_Controller* AI_Game_Controller = nullptr;
	//APlayer_Controller* Player_Game_Controller = nullptr;
	AController* Default_Controller = nullptr;
	bool Spawned_Player_Controller = false;
	bool Spawned_AI_Controller = false;
	Combat_Manager Manager_Combat;

	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AMyCharacter> Player_BP;
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AMyCharacter> AI_BP;

	bool Game_Started = false;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Roll_Iniciative();
	void Move_To_Start();
	void Starting_Positons();
	int Next_Turn();
	bool Is_Calculating_Next_Order = true;

	APlayer_Character*  Player_Character = nullptr; //CURRENT CHARACTERS DOING STUFF
	AAI_Character* AI_Character = nullptr;

	TMap<int16, int16> Iniciative;
	TArray<AStanding_Position*> Player_Positions;
	TArray<AStanding_Position_AI*> AI_Positions;
	TMap<int8, int8> Done_Turn;
	int8 Current_Turn_Operator = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
