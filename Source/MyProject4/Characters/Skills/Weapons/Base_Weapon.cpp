// Fill out your copyright notice in the Description page of Project Settings.	


#include "Base_Weapon.h"
/**/
Base_Weapon::Base_Weapon()
{
	Attack_Primary = Attack_Base(25, 20, 70, 30,0, 1);
	Attack_Secondary = Attack_Base(5, 15, 50, 50, 0, 45);

	Attack_Primary_Sword = Attack_Base(25, 2000, 70, 30, 0, 1);
	Attack_Secondary_Sword = Attack_Base(5, 15, 50, 50, 0, 45);

	Attack_Primary_Axe = Attack_Base(70, 5000, 20, 30, 0, 1);
	Attack_Secondary_Axe = Attack_Base(20, 10, 50, 50, 0, 45);
	//Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	//Axe = CreateDefaultSubobject<UStaticMesh>(TEXT("Axe"));
	//Sword = CreateDefaultSubobject<UStaticMesh>(TEXT("Sword"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh> Swordasset(TEXT("StaticMesh'/Game/CloseCombat/Weapon/Swords/FuturisticSword/Meshes/SM_FuturisticSword.SM_FuturisticSword'"));
	if (Swordasset.Succeeded()&& Swordasset.Object != nullptr)
	{
		if (UStaticMesh* Mesh = Cast<UStaticMesh>(Swordasset.Object))
			Sword = Mesh;
		else
			Sword = nullptr;
	
	}	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Axeasset(TEXT("StaticMesh'/Game/CloseCombat/Weapon/Swords/SwordOfDarkness/Meshes/SM_SwordOfDarkness.SM_SwordOfDarkness'"));
	if (Axeasset.Succeeded())
	{
		Axe = Axeasset.Object;

	}



}

Attack_Base Base_Weapon::Get_Attack_Primary(int type)
{

	switch (type)
	{
	case 0:
		return Attack_Primary_Axe;
		break;
	case 1:
		return Attack_Primary_Sword;
		break;
	default:
		return Attack_Primary;
		break;
	}
	return Attack_Primary;
}
Attack_Base Base_Weapon::Get_Attack_Secondary(int type)
{
	switch (type)
	{
	case 0:
		return Attack_Secondary_Axe;
		break;
	case 1:
		return Attack_Secondary_Sword;
		break;
	default:
		return Attack_Primary;
		break;
	}
	return Attack_Primary;
}

UStaticMesh* Base_Weapon::Get_Component(int type)
{
	switch(type)
	{
	case 0:
		return Axe;
		break;
	case 1:
	//	if (Sword != nullptr)
		if (UStaticMesh* Mesh = Cast<UStaticMesh>(Sword))
			return Mesh;
		else
			return nullptr;
	//	else
			//return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
}
