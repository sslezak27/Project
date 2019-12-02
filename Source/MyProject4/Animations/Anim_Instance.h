// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/MyCharacter.h"

#include "Anim_Instance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API UAnim_Instance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float characterMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isCharacterAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isGettingHit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isDodging;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool isAlive = true;
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
		void UpdateAnimationProperties();
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
		void Animation_Combat_End();
private:
	AMyCharacter* MyCharacter;
	AMyCharacter* Target_Of_Attack;
};
