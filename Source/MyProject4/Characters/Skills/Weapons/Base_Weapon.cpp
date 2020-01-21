// Fill out your copyright notice in the Description page of Project Settings.	


#include "Base_Weapon.h"
/**/
Base_Weapon::Base_Weapon()
{
	Attack_Primary = Attack_Base(25, 20, 70, 30,0, 1);
	Attack_Secondary = Attack_Base(5, 15, 50, 50, 0, 45);

	Attack_Primary_Sword = Attack_Base(50, 200, 70, 0, 0, 1);
	Attack_Secondary_Sword = Attack_Base(60, 1000, 0, 0, 1, 45, 2);

	Attack_Primary_Axe = Attack_Base(70, 200, 50, 30, 0, 1);
	Attack_Secondary_Axe = Attack_Base(60, 1000, 0, 0, 1,4,2);

	Attack_Primary_AR4 = Attack_Base(10, 200, 50, 30, 0, 1);
	Attack_Secondary_AR4 = Attack_Base(40, 3000, 0, 0, 1, 4, 1);

	Attack_Primary_KA = Attack_Base(5, 200, 50, 30, 0, 1);
	Attack_Secondary_KA = Attack_Base(60, 4000, 0, 0, 1, 6, 1);

	Attack_Primary_AK = Attack_Base(15, 200, 50, 30, 0, 1);
	Attack_Secondary_AK = Attack_Base(50, 3000, 0, 0, 1, 4, 1);

	Attack_Primary_SMG = Attack_Base(30, 200, 50, 30, 0, 1);
	Attack_Secondary_SMG = Attack_Base(30, 1000, 0, 0, 1, 3, 1);




	//Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	//Axe = CreateDefaultSubobject<UStaticMesh>(TEXT("Axe"));
	//Sword = CreateDefaultSubobject<UStaticMesh>(TEXT("Sword"));

	if (Sword == nullptr)
	{	
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Swordasset(TEXT("StaticMesh'/Game/CloseCombat/Weapon/Swords/FuturisticSword/Meshes/SM_FuturisticSword.SM_FuturisticSword'"));
		if (Swordasset.Succeeded() && Swordasset.Object != nullptr)
		{
			if (UStaticMesh* Mesh = Cast<UStaticMesh>(Swordasset.Object))
				Sword = Mesh;
			else
				Sword = nullptr;

		}
	}
	if (Axe == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Axeasset(TEXT("StaticMesh'/Game/CloseCombat/Weapon/Swords/SwordOfDarkness/Meshes/SM_SwordOfDarkness.SM_SwordOfDarkness'"));
		if (Axeasset.Succeeded())
		{
			Axe = Axeasset.Object;

		}
	}	
	if (AR4 == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ARasset(TEXT("StaticMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SM_AR4_X.SM_AR4_X'"));
		if (ARasset.Succeeded())
		{
			AR4 = ARasset.Object;

		}
	}
	if (KA == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> KAasset(TEXT("StaticMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/KA_Val/SM_KA_Val_X.SM_KA_Val_X'"));
		if (KAasset.Succeeded())
		{
			KA = KAasset.Object;

		}
	}
	if (AK == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> AKasset(TEXT("StaticMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47/SM_KA47_X.SM_KA47_X'"));
		if (AKasset.Succeeded())
		{
			AK = AKasset.Object;

		}
	}
	if (SMG == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SMGasset(TEXT("StaticMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/SMG11/SM_SMG11_X.SM_SMG11_X'"));
		if (SMGasset.Succeeded())
		{
			SMG = SMGasset.Object;

		}
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
	case 2:
		return Attack_Primary_AR4;
		break;
	case 3:
		return Attack_Primary_KA;
		break;
	case 4:
		return Attack_Primary_AK;
		break;
	case 5:
		return Attack_Primary_AKU;
		break;
	case 6:
		return Attack_Primary_SMG;
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
	case 2:
		return Attack_Secondary_AR4;
		break;
	case 3:
		return Attack_Secondary_KA;
		break;
	case 4:
		return Attack_Secondary_AK;
		break;
	case 5:
		return Attack_Secondary_AKU;
		break;
	case 6:
		return Attack_Secondary_SMG;
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
		return Sword;
	//	else
			//return nullptr;
		break;
	case 2:
		return AR4;
		break;
	case 3:
		return KA;
		break;
	case 4:
		return AK;
		break;
	case 5:
		return AKU;
		break;
	case 6:
		return SMG;
		break;
	default:
		return nullptr;
		break;
	}
}
