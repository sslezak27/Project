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


}

void APlayer_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void APlayer_Character::Jumps()
{
	/**GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "CALLED_IT");
	
	if (APlayer_Controller* PC = Cast<APlayer_Controller>(GetController()))
	{
		FHitResult Hit;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			Change_Ownership();
			//if(Cast<AAI_Controller>(GetController()) != nullptr)
				//SimpleMoveToLocation(Hit.ImpactPoint);
		//	else
			//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "SUM_THING_WONG");
		}
	}
	**/
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