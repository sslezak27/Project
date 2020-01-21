// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat_Manager.h"

Combat_Manager::Combat_Manager()
{

}

Combat_Manager::Combat_Manager(TArray<AAI_Character*>AI_Characters_To_Pass, TArray<APlayer_Character*>Player_Characters_To_Pass)
{
	AI_Characters = AI_Characters_To_Pass;
	Player_Characters = Player_Characters_To_Pass;
}

Combat_Manager::~Combat_Manager()
{
}



void Combat_Manager::Get_AI_Skill(AAI_Character* AI_Character)
{
	Current_AI = AI_Character;
	Current_Attack = AI_Character->Get_Skill();
	if (Current_Attack != nullptr)
	{
		Get_Locations(false);
	}
}
void Combat_Manager::Get_Player_Skill(APlayer_Character* Player_Character)
{
	Current_Player = Player_Character;
	Current_Attack = Player_Character->Get_Skill();
	if (Current_Attack != nullptr)
	{
		Get_Locations(true);
	}
}

void Combat_Manager::Get_Locations(bool IS_Player_Turn)
{
	Character_Locations.Empty();
	Valid_Targets.Empty();
	if (!IS_Player_Turn)
	{
		for (int Iterator = 0; Iterator < Player_Characters.Num(); Iterator++)
		{

				FVector Location = Player_Characters[Iterator]->GetActorLocation();
				Character_Locations.Add(Location);
				if ((Current_AI->GetActorLocation() - Location).Size() <= Current_Attack->Attack_Range && (Player_Characters[Iterator]->Is_Alive))
				
				{
					Valid_Targets.Add(Location);
					Player_Characters[Iterator] ->Be_Targeted();
				}
			
		}
	}
	else
	{
		for (int Iterator = 0; Iterator < AI_Characters.Num(); Iterator++)
		{

				FVector Location = AI_Characters[Iterator]->GetActorLocation();
				Character_Locations.Add(Location);
				//Character_Locations.Add(AI_Characters[Iterator]->GetActorLocation());
				for(int iterator = 0;iterator < Character_Locations.Num();iterator++)
				if ((Current_Player->GetActorLocation() - Location).Size() <= Current_Attack->Attack_Range && (AI_Characters[Iterator]->Is_Alive))
				{
					Valid_Targets.Add(Location);
					AI_Characters[Iterator]->Be_Targeted();
				}
			
		}

	}
}
void Combat_Manager::Reset_Targets()
{

	for (int Iterator = 0; Iterator < Player_Characters.Num(); Iterator++)
	{
			Player_Characters[Iterator]->Reset_Targeted();

	}
	for (int Iterator = 0; Iterator < AI_Characters.Num(); Iterator++)
	{
		AI_Characters[Iterator]->Reset_Targeted();

	}
}

AMyCharacter* Combat_Manager::Calculate_AI_Move_Target(AAI_Character* AI_Character)
{
	float const AI_Target_HP_Weight = AI_Character->AI_HP_Weight;
	float const AI_Target_Move_Weight = AI_Character->AI_Move_Weight;
	TMap<int16, float> Weight;   //1st is index 2 is weight
	float Temp_Weight = 0;  //Waga wyliczona
	int16 Highest_Index = 0; //Index postaci z najwy¿sz¹ wag¹

	for (int Iterator = 0; Iterator < Player_Characters.Num(); Iterator++)
	{
		if (Player_Characters[Iterator]->Is_Alive)
		{
			Temp_Weight = 0;
			if ((AI_Character->GetActorLocation() - Character_Locations[Iterator]).Size() <= AI_Character->Get_Skill()->Attack_Range)
			{
				Temp_Weight += 100000;
			}
			else
			{
				Temp_Weight -= (AI_Character->GetActorLocation() - Character_Locations[Iterator]).Size() * AI_Target_Move_Weight;
			}
			Temp_Weight += Player_Characters[Iterator]->Get_Health() * AI_Target_HP_Weight;
			Weight.Add(Iterator, Temp_Weight);
		}
	}
	Weight.ValueSort([](float A, float B) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Sorting_ARRAY");
		return B < A; // sort keys
	});
	for (auto& element : Weight)
	{
		Highest_Index = element.Key;
		break;
	} 
	return Player_Characters[Highest_Index];
}

