// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Character.h"
#include "Components/InputComponent.h"


APlayer_Character::APlayer_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//Super::AMyCharacter();
	PrimaryActorTick.bCanEverTick = true;
	//PrimaryActorTick.bStartWithTickEnabled = true;

	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Characters/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
		if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "SUCCES");

	}
	CursorToWorld->DecalSize = FVector(1.0f, 1.0f, 1.0f);
	//CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
	if(GEngine)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "CONSTRUCTED THIS uadhkgaejjeagfkjaeguejgkfulkesgfluisrgrsgjflsgfksljrhglkgrslkrs");

	Active_Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
	//Weapon = CreateDefaultSubobject<Base_Weapon>(TEXT("WEAPON"));

	Attack_Base Temp_Skill(20.0f, 50.f, 70.f, 1, 500.f, 0.f,0, 10);
	Current_Skill = Temp_Skill;
}

void APlayer_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();
	//Active_Weapon = Base_Weapon->Get_Component(Weapon_Type);
	Attack_Primary = BaseWeapon.Get_Attack_Primary(Weapon_Type);
	Attack_Secondary = BaseWeapon.Get_Attack_Secondary(Weapon_Type);
	Current_Skill = Attack_Primary;
	//UStaticMesh* Mesh_To_Set = Get_Component(Weapon_Type);
	UStaticMesh* Mesh_To_Set = BaseWeapon.Get_Component(Weapon_Type);;
	if (Mesh_To_Set != nullptr)
	{
		Active_Weapon->SetStaticMesh(Mesh_To_Set);
		if (Active_Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true), FName("Socket_Weapon")))
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "WE DID IT BOYSZZZZZZZZZx");
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "WE DID IT BOYSZZZZZZZZZxMISSSIONFAILED");
}
void APlayer_Character::Jumps()
{
	
}

int APlayer_Character::Roll_Iniciative()
{
	return Iniciative + FMath::FRandRange(0, 300);
}
bool APlayer_Character::Do_Turn(FVector Move_Location)
{	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "PLAYER_Turn_Started");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(HP));

	//if (Is_Placed)
	Move_Done = true;
	Is_Turn = false;
	//FRotator Current_Rotator = GetViewRotation();
	//double Yaw = Pathfinder.Calculate_Absolute_Yaw(GetActorLocation(), Move_Location);
	//
	//FaceRotation(Current_Rotator);

	if (Pathfinder.Is_Move_Valid(Action_Points_Current, GetActorLocation(), Move_Location))
	{
		Move_Location = Pathfinder.Calculate_Path(Action_Points_Current, GetActorLocation(), Move_Location,0);
		Reset_Scale();
		//Move_My_Character(Move_Location);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Movin");
		Move_My_Character(FVector(Move_Location.X,Move_Location.Y,0.0f));
		Move_Done = false;
		return true;
	}
	else
		return false;
	//Move_My_Character(GetActorLocation() - FVector(FMath::FRandRange(-500, 500), FMath::FRandRange(-500, 500), 0));
}

void APlayer_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayer_Character::Turn_End()
{
	Reset_Scale();	
	Is_Turn = false;
	if (!Is_Placed)
	{
		Is_Placed = true;
	}
	Move_Done = true;
	Turn_Done = true;
	Is_Attacking = false;
	Target_Of_Attack = nullptr;
	Is_Being_Attacked = false;
	Action_Points_Current = Action_Points_Max;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Turn Ended");
}


void APlayer_Character::Move_End()
{
	if (Action_Points_Current < 5)
	{
		Turn_End();
	}
	else
		Move_Done = true;

}

void APlayer_Character::Reset_Scale()
{
	CursorToWorld->SetWorldScale3D(FVector(0, 0, 0));

}

void APlayer_Character::Change_Scale()
{
	float max_range = Action_Points_Current * Pathfinder.Distance_Const;
	CursorToWorld->SetWorldScale3D(FVector(max_range, max_range, max_range));

}

bool APlayer_Character::Attack_Target(AMyCharacter* Target)
{
	Is_Turn = false;


	if(!Is_Attacking && Target->Get_Health() > 0)
	{
		if (Current_Skill.Attack_Type == 0)
		{
			if ((GetActorLocation() - Target->GetTargetLocation()).Size() <= Current_Skill.Attack_Range)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "ATTACK_TARGET 1");
				FRotator Current_Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());

				//Current_Rotator.Yaw =
				FaceRotation(Current_Rotator);
				Reset_Scale();
				Is_Attacking = true;
				Target_Of_Attack = Target;
				if (Calculate_Attack_Succes(Target))
					Target->Be_Attacked(&Current_Skill);
				else
					Target->Set_Dodge(true);
				//Turn_End();

				return true;

			}
			else if (Action_Points_Current > 0)
			{
				if (Do_Turn(Target->GetTargetLocation())) {
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "ATTACK_TARGET 2");

					return true;
				}
				else
					return false;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "ATTACK_TARGET 3");
				return false;
			}
		}

		else if (Current_Skill.Attack_Type == 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "ATTACK_TARGET RANGED");
			FRotator Current_Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());

			//Current_Rotator.Yaw =
			FaceRotation(Current_Rotator);
			Reset_Scale();
			Is_Attacking = true;
			Target_Of_Attack = Target;
			FVector Current_Location = GetActorLocation();
			FVector Arrow_Location = FVector(Current_Location.X, Current_Location.Y, Current_Location.Y + 100.f);

			Current_Arrow = GetWorld()->SpawnActor<AArrow>(Arrow_Location, Current_Rotator);
			Current_Arrow->Setup_Component(Current_Skill.Calculate_Attack_Yaw(Arrow_Location,Target->GetActorLocation()), Current_Skill.Ranged_Vx, Current_Rotator);
			//Turn_End();

			return true;
		}
		else
			return false;
	}
	else
		return false;
}