// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character.h"

AAI_Character::AAI_Character()
{
	//AMyCharacter();
}

int AAI_Character::Roll_Iniciative()
{
	return Iniciative + FMath::FRandRange(-50, 50);

}
bool AAI_Character::Do_AI_Turn(AMyCharacter* Target_Character)
{
	FVector Move_Location = Target_Character->GetActorLocation();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "AI_TURN_STARTED");
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(HP));
	//FRotator Current_Rotator = GetViewRotation();
	double Yaw = Pathfinder.Calculate_Absolute_Yaw(GetActorLocation(), Move_Location);
	//Current_Rotator.Yaw = Yaw;
	//FaceRotation(Current_Rotator);
	//if (Is_Placed)
	if (Pathfinder.Is_Valid_Attack_Target(Current_Skill.Attack_Range, GetActorLocation(), Move_Location))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "IT'S ATTACKING");

		Attack_Target(Target_Character);
		//Turn_End();
	}
	else if (Pathfinder.Is_Move_Valid(Action_Points_Current, GetActorLocation(), Move_Location))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "IT'S DOING IT");

		Move_Location = Pathfinder.Calculate_Path(Action_Points_Current, GetActorLocation(), Move_Location,Yaw);
	//	Move_My_Character(Move_Location);
		Move_My_Character(FVector(Move_Location.X, Move_Location.Y, 0.0f));
	}
	else
	{
		Turn_End();
	}
	return true;
}

void AAI_Character::Turn_End()
{
	Turn_Done = true;
	Is_Attacking = false;
	Target_Of_Attack = nullptr;
	Is_Being_Attacked = false;
	Action_Points_Current = Action_Points_Max;
}