// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Instance.h"

void UAnim_Instance::UpdateAnimationProperties()
{
	APawn* character = TryGetPawnOwner();


	if (character && (MyCharacter = Cast<AMyCharacter>(character)) != nullptr)
	{

		isCharacterAttacking = MyCharacter->Get_Is_Attacking();
		isGettingHit = MyCharacter->Get_Is_Being_Attacked();
		isDodging = MyCharacter->Get_Is_Dodging();
		isAlive = MyCharacter->Get_Is_Alive();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("(%d)"),isCharacterAttacking));
		characterMovementSpeed = MyCharacter->GetVelocity().Size();
	}
}

void UAnim_Instance::Animation_Combat_End()
{
	if (isCharacterAttacking)
	{
		isCharacterAttacking = false;
		MyCharacter->End_Attack();
	}
	isGettingHit = false;
	isDodging = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Combat_Animation_Ended"));

	MyCharacter->Set_Dodge(false);
	
}

