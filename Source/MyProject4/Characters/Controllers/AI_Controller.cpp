// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Controller.h"



void AAI_Controller::OnMoveCompleted(FAIRequestID, const FPathFollowingResult&)
{
	APawn* ControlledPawn = K2_GetPawn();
	ControlledCharacter = Cast< AMyCharacter >(ControlledPawn);
	if (ControlledCharacter != nullptr)
	{
		ControlledCharacter->Move_End();
	}

}
