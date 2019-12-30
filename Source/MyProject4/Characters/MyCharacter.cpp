// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Controllers/AI_Controller.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Targeted_Circle = CreateDefaultSubobject<UDecalComponent>("Targeted_Circle");
	Targeted_Circle->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Characters/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		Targeted_Circle->SetDecalMaterial(DecalMaterialAsset.Object);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "SUCCES");

	}
	Targeted_Circle->DecalSize = FVector(1, 1, 1);
	Targeted_Circle->SetWorldScale3D(FVector(0, 0, 0));
	Attack_Melee_Skill = FMath::FRandRange(1, 100);
	Defence_Melee_Skill = FMath::FRandRange(1, 100);
	Ranged_Skill_Aim = FMath::FRandRange(1, 100);
	Skill_Strength = FMath::FRandRange(1, 100);
	Weapon_Type = FMath::FRandRange(0, 2) - 0.001;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Swordasset(TEXT("StaticMesh'/Game/CloseCombat/Weapon/Swords/FuturisticSword/Meshes/SM_FuturisticSword.SM_FuturisticSword'"));
	if (Swordasset.Succeeded())
	{
		if (UStaticMesh* cast_Mesh = Cast<UStaticMesh>(Swordasset.Object))
			Mesh_Sword = cast_Mesh;
		else
			Mesh_Sword = nullptr;

	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Axeasset(TEXT("StaticMesh'/Game/CloseCombat/Weapon/Swords/SwordOfDarkness/Meshes/SM_SwordOfDarkness.SM_SwordOfDarkness'"));
	if (Axeasset.Succeeded())
	{
		Mesh_Axe = Axeasset.Object;

	}

	//PrimaryActorTick.bStartWithTickEnabled = true;



}



int AMyCharacter::Roll_Iniciative()
{
	Iniciative = 1;
	return 1;
}
bool AMyCharacter::Do_Turn(FVector Move_Location)
{	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Turn Started");
	//if(Is_Placed)
	Move_My_Character(GetActorLocation() - FVector(FMath::FRandRange(-150, 150), FMath::FRandRange(-150,150), 0));
	return true;
}

void AMyCharacter::Move_End()
{
	Turn_End();
}

void AMyCharacter::Turn_End()
{
	if (!Is_Placed)
	{
		Is_Placed = true;
	}
	Is_Attacking = false;
	Turn_Done = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Turn Ended");
}
// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Move_My_Character(FVector(500, -120, 108));
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::Change_Skill(int skill)
{
	switch(skill)
	{
	case 0:
		Current_Skill = Attack_Primary;
		break;
	case 1:
		Current_Skill = Attack_Secondary;
		break;
	default:
		Current_Skill = Attack_Primary;
		break;
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::Move_My_Character(const FVector& position)
{
	UNavigationPath* path = UNavigationSystemV1::FindPathToLocationSynchronously(this, this->GetActorLocation(), position);

	/**if (path && path->IsValid())
	{
		FAIMoveRequest req;
		req.SetAcceptanceRadius(50);
		req.SetUsePathfinding(true);
		**/
		AAI_Controller* ai = Cast<AAI_Controller>(this->GetController());
		if (ai)
		{
			//ai->RequestMove(req, path->GetPath());
			ai->MoveToLocation(position);
		}
	//}
}

bool AMyCharacter::Attack_Target(AMyCharacter* Target)
{
	Is_Attacking = true;
	Target_Of_Attack = Target;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "MY_CHARACTER_ATTACK_CALLED");
	if (Calculate_Attack_Succes(Target))
		Target->Be_Attacked(&Current_Skill);
	else
		Target->Set_Dodge(true);
	return true;
}

bool AMyCharacter::Calculate_Attack_Succes(AMyCharacter* Target)
{
	float Chance_To_Hit = Current_Skill.Base_Hit_Chance * Attack_Melee_Skill / Target->Get_Defence_Melee_Skill();
	if (FMath::FRandRange(1, 100) <= Chance_To_Hit)
	{
		return true;
	}
	else
		return false;
}

void AMyCharacter::Be_Attacked(Attack_Base* Skill)
{
	if (Is_Alive)
	{
		Is_Being_Attacked = true;
		HP -= Skill->Attack_Dmg;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(HP));
		if (HP <= 0)
		{
			Set_Dodge(false);
			DIE();
		}
	}
}

Attack_Base* AMyCharacter::Get_Skill()
{
	return &Current_Skill;
}

void AMyCharacter::Be_Targeted()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "YOUCALLED");
	Targeted_Circle-> SetWorldScale3D(FVector(100, 100, 100));
}

void AMyCharacter::DIE()
{
	Is_Alive = false;
}

void AMyCharacter::Reset_Targeted()
{
	Targeted_Circle->SetWorldScale3D(FVector(0, 0, 0));
}


bool AMyCharacter::Get_Is_Attacking() const
{
	return Is_Attacking;
}

void AMyCharacter::End_Attack()
{
	Turn_End();
}

AMyCharacter* AMyCharacter::Get_Target() const
{
	return Target_Of_Attack;
}

bool AMyCharacter::Get_Is_Being_Attacked() const
{
	return Is_Being_Attacked;
}

int AMyCharacter::Get_Defence_Melee_Skill() const
{
	return Defence_Melee_Skill;
}

bool AMyCharacter::Get_Is_Dodging() const
{
	return Is_Dodging;
}

void AMyCharacter::Set_Dodge(bool Dodge)
{
	Is_Dodging = Dodge;
	Is_Being_Attacked = false;
}

bool AMyCharacter::Get_Is_Alive() const
{
	return Is_Alive;
}

float AMyCharacter::Get_Health() const
{
	return HP;
}
float AMyCharacter::Get_Max_HP() const
{
	return Max_HP;
}

int AMyCharacter::Get_Attack_Melee_Skill() const
{
	return Attack_Melee_Skill;
}


UStaticMesh* AMyCharacter::Get_Component(int type)
{
	switch (type)
	{
	case 0:
		return Mesh_Axe;
		break;
	case 1:
		//	if (Sword != nullptr)
		//if (UStaticMesh* Mesh = Cast<UStaticMesh>(Sword))
			return Mesh_Sword;
		//else
			//return nullptr;
		//	else
				//return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
}