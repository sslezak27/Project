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
	//Destroy(Combat_Manager);

}

// Called when the game starts or when spawned
void AGame_Manager::BeginPlay()
{
	Super::BeginPlay();
	Starting_Positons();
	Begin_Combat();
	
}

// Called every frame
void AGame_Manager::Tick(float DeltaTime)
{
	if (Is_Calculating_Next_Order == false) {

		Super::Tick(DeltaTime);
		if (Characters[Current_Turn_Operator]->Turn_Done == true)
		{
			Characters[Current_Turn_Operator]->Turn_Done = false;
			//PrimaryActorTick.bCanEverTick = false;
			Next_Turn();
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Turn_Done"));
		}
		if (!Player_Turn) {


			if (Cast<APlayer_Character>(Characters[Current_Turn_Operator]) != nullptr)
			{
				Player_Turn = Characters[Current_Turn_Operator]->Move_Done;
				if (Player_Turn)
				{
					Manager_Combat.Reset_Targets();
	
					Player_Character->Change_Scale();
					Manager_Combat.Get_Player_Skill(Player_Character);
				}
			}
		}
	}
}

void AGame_Manager::Begin_Combat()
{// DO ZAMIANY!!!!!!!!!!
	Characters.Empty();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("POCZ¥TEK"));
	int iterator = 0;
	AAI_Character* Cast_Target_AI = nullptr;
	APlayer_Character* Cast_Target_Player = nullptr;
	//TArray<AActor*> FoundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass, FoundActors);
	for (TActorIterator<AMyCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("W Pêtli"));
		// Same as with the Object Iterator, access the subclass instance with the * or -> operators.
		if (*ActorItr != nullptr)
		{	
			Characters.Add(*ActorItr);
			if ((Cast_Target_AI=Cast<AAI_Character>(*ActorItr)) != nullptr)
			{
				AI_Characters.Add(Cast_Target_AI);
			}
			else if ((Cast_Target_Player = Cast<APlayer_Character>(*ActorItr)) != nullptr)
			{
				Player_Characters.Add(Cast_Target_Player);
			}
			//Characters[iterator]->Move_My_Character(FVector(500, -120, 108));
			iterator+=1;

		}
	}
	Manager_Combat = Combat_Manager(AI_Characters, Player_Characters);
	Roll_Iniciative();
	Move_To_Start();
	Next_Turn();
}
		



void AGame_Manager::Roll_Iniciative()
{
	for (int iterator = 0; iterator < Characters.Num(); iterator++)
	{
		Iniciative.Add(iterator, Characters[iterator]->Roll_Iniciative());
		Done_Turn.Add(iterator, 0);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(Iniciative[iterator]));
	}
	Iniciative.ValueSort([](int16 A, int16 B) {
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Sorting_ARRAY");

		return B < A; // sort keys
		});
	for (auto It = Iniciative.CreateIterator(); It; ++It)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (*FString::Printf(TEXT("(%d, \"%d\")\n"),It.Key(),It.Value())));
	}
}

void AGame_Manager::Move_To_Start()
{
	int player_iter = 0;
	int ai_iter = 0;
	for (int iterator = 0; iterator < Characters.Num(); iterator++)
	{

		if (Cast<AAI_Character>(Characters[iterator]) != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("AIMOVE"));
			ai_iter += 1;

			if (Spawned_AI_Controller == false)
			{
					Characters[iterator]->AIControllerClass = AIController;
					Characters[iterator]->SpawnDefaultController();
					AI_Game_Controller = Cast<AAI_Controller>(Characters[iterator]->Controller);
					if (AI_Game_Controller != nullptr)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("AICONTROLLER_IS_SET"));
						Spawned_AI_Controller = true;
					}
				
					//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("AICONTROLLER_IS_NOT_SET"));
		
			}
		}
	}
	
	
}

void AGame_Manager::Starting_Positons()
{
	Player_Positions.Empty();
	AI_Positions.Empty();
	int iterator = 0;
	for (TActorIterator<AStanding_Position> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (*ActorItr != nullptr)
		{
			Player_Positions.Add(*ActorItr);
			//Characters[iterator]->Move_My_Character(FVector(500, -120, 108));
			iterator += 1;

		}
	}
	iterator = 0;
	for (TActorIterator<AStanding_Position_AI> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (*ActorItr != nullptr)
		{
			AI_Positions.Add(*ActorItr);
			//Characters[iterator]->Move_My_Character(FVector(500, -120, 108));
			iterator += 1;

		}
	}

}

int AGame_Manager::Next_Turn()
{
	Is_Calculating_Next_Order = true;
	if(Spawned_AI_Controller)
	AI_Game_Controller->UnPossess();
	//if(Spawned_Player_Controller)
	//Player_Game_Controller->UnPossess();
	for (auto It = Iniciative.CreateIterator(); It; ++It)
	{
		int iterator = It.Key();
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (*FString::Printf(TEXT("(%d, \"%d\")\n"), It.Key(), It.Value())));
		if (Done_Turn[iterator] == 0)
		{

			Current_Turn_Operator = iterator;
			Done_Turn.Add(iterator, 1);
			//PrimaryActorTick.bCanEverTick = true;
			if (Characters[iterator]->Get_Is_Alive())
			{
				if ((AI_Character = Cast<AAI_Character>(Characters[iterator])) != nullptr)
				{
					AI_Game_Controller->Possess(Characters[iterator]);
					Player_Turn = false;
					Manager_Combat.Reset_Targets();
					Manager_Combat.Get_AI_Skill(AI_Character);
					AI_Character->Do_AI_Turn(Manager_Combat.Calculate_AI_Move_Target(AI_Character)); //DO ZAMIANY!!!!!!!!!!!!

				}
				else if ((Player_Character = Cast<APlayer_Character>(Characters[iterator])) != nullptr)
				{
					AI_Game_Controller->Possess(Characters[iterator]);
					Player_Turn = true;
					Player_Character->Change_Scale();
					Manager_Combat.Reset_Targets();
					Manager_Combat.Get_Player_Skill(Player_Character);
				}

				Is_Calculating_Next_Order = false;
				return 1;
			}





		}
	}
	Turn_Counter++;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(Turn_Counter));
	Roll_Iniciative();
	Next_Turn();
	return 0;
}

void AGame_Manager::Move_Player(FVector& Location)
{

	Player_Turn = !Characters[Current_Turn_Operator]->Do_Turn(Location);
}

void AGame_Manager::Attack_Player(AMyCharacter* Target)
{
	Player_Turn = !Characters[Current_Turn_Operator]->Attack_Target(Target);
}

void AGame_Manager::End_Player_Turn()
{
	if (Player_Turn == true)
	{
		if (Player_Character->Move_Done)
		{
			Player_Character->Turn_End();
		}
	}
}

