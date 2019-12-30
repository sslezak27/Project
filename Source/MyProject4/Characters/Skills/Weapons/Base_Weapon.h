// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Characters/Skills/Attack/Attack_Base.h"
#include "GameFramework/Actor.h"



/**
 * 
 */

class MYPROJECT4_API Base_Weapon
{

public:
	Base_Weapon();
	Attack_Base Get_Attack_Primary(int type);
	Attack_Base Get_Attack_Secondary(int type);

	

	UStaticMesh* Get_Component(int type);
private:
	
	Attack_Base Attack_Primary;
	Attack_Base Attack_Secondary;
	UPROPERTY(VisibleDefaultsOnly, Category = "Sword") // This is so we can set the mesh in the editor
	UStaticMesh* Weapon;
	UPROPERTY()
	UStaticMesh* Axe;

	Attack_Base Attack_Primary_Sword;
	Attack_Base Attack_Secondary_Sword;
	Attack_Base Attack_Primary_Axe;
	Attack_Base Attack_Secondary_Axe;

	UPROPERTY() 
	UStaticMesh* Sword;


};
