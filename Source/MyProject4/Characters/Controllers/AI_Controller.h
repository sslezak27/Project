// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/MyCharacter.h"
#include "AI_Controller.generated.h"


/**
 * 
 */
UCLASS()
class MYPROJECT4_API AAI_Controller : public AAIController
{
	GENERATED_BODY()
	
	virtual void OnMoveCompleted(FAIRequestID, const FPathFollowingResult&) override;
	
	AMyCharacter* ControlledCharacter;
	
};
