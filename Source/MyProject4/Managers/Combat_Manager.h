// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AI_Character/AI_Character.h"
#include "Characters/Player_Characters/Player_Character.h"
#include "Characters/Skills/Attack/Attack_Base.h"

/**
 * 
 */
class MYPROJECT4_API Combat_Manager
{
public:
	Combat_Manager(TArray<AAI_Character*>AI_Characters_To_Pass,TArray<APlayer_Character*>Player_Characters_To_Pass);
	Combat_Manager();
	~Combat_Manager();

	void Get_AI_Skill(AAI_Character* AI_Character);
	void Get_Player_Skill(APlayer_Character* Player_Character);
	void Reset_Targets();
	AMyCharacter* Calculate_AI_Move_Target(AAI_Character* AI_Character);

private:
	Attack_Base* Current_Attack;
	TArray<AAI_Character*>AI_Characters;
	TArray<APlayer_Character*>Player_Characters;
	TArray<FVector>Character_Locations;
	TArray<FVector>Valid_Targets;
	APlayer_Character* Current_Player;
	AAI_Character* Current_AI;
	

	void Get_Locations(bool IS_Player_Turn);
};
