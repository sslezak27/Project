// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MyCharacter.h"
#include "Pathfinding/Pathfinder.h"
#include "Characters/Skills/Weapons/Base_Weapon.h"

#include "AI_Character.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API AAI_Character : public AMyCharacter
{
	GENERATED_BODY()
	public:
		AAI_Character();
		virtual int Roll_Iniciative() override;
		virtual bool Do_AI_Turn(AMyCharacter* Target_Character);
		float AI_HP_Weight = FMath::FRandRange(1, 10);
		float AI_Move_Weight = FMath::FRandRange(1, 10);
		virtual void Turn_End() override;
		Base_Weapon BaseWeapon;

	private:
		Pathfinder Pathfinder;
		int Action_Points_Current = 40;
		int const Action_Points_Max = 40;
		UPROPERTY(VisibleDefaultsOnly, Category = "Sword") // This is so we can set the mesh in the editor
			UStaticMeshComponent* Active_Weapon;

	protected:
		int Iniciative = 50;
		virtual void BeginPlay() override;

	
};
