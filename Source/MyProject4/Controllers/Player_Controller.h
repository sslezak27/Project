// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/MyCharacter.h"
#include "Characters/Player_Characters/Player_Character.h"
#include "Characters/AI_Character/AI_Character.h"
#include "Game_Manager.h"
#include "Camera/Camera_Pawn.h"

#include "GameFramework/PlayerController.h"
#include "Player_Controller.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API APlayer_Controller : public APlayerController
{
	GENERATED_BODY()
	public:
		APlayer_Controller();
		ACamera_Pawn* GetMainSpectatorPawn() const;
		virtual void Tick(float DeltaTime) override;

private:
	AGame_Manager* GameManager = nullptr;
	AAI_Character* Enemy_Character = nullptr;
	bool Can_Camera_Rotate = false;

	void Select_Location();
	void End_Player_Turn();
	void MoveCameraForward(float value);
	void MoveCameraRight(float value);
	void ZoomIn();
	void ZoomOut();
	void Rotate_Camera_X(float value);
	void Rotate_Camera_Y(float value);
	void Enable_Camera_Rotation();
	void Disable_Camera_Rotation();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* PossessedPawn) override;
	APlayer_Character* ControlledCharacter = nullptr;
	APawn* PawnToPosses = nullptr;

};
