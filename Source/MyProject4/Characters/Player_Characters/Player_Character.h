// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MyCharacter.h"
#include "Player_Character.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API APlayer_Character : public AMyCharacter
{
	GENERATED_BODY()
	public:
		virtual int Roll_Iniciative() override;
	protected:
		int Iniciative = 98;
	
};
