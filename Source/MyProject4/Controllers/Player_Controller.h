// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/MyCharacter.h"
#include "Characters/Player_Characters/Player_Character.h"
#include "Characters/AI_Character/AI_Character.h"
#include "Game_Manager.h"
#include "Camera/Camera_Pawn.h"
#include "HUD/A_Hud.h"

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

		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			void Change_Skill(int skill);

private:
	AGame_Manager* GameManager = nullptr;
	AAI_Character* Enemy_Character = nullptr;
	AMyCharacter* A_Character = nullptr;
	bool Can_Camera_Rotate = false;
	AA_HUD* HUD = nullptr;

	void Select_Location();
	void End_Player_Turn();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void Bring_Character_Sheet();




	void MoveCameraForward(float value);
	void MoveCameraRight(float value);
	void ZoomIn();
	void ZoomOut();
	void Rotate_Camera_X(float value);
	void Rotate_Camera_Y(float value);
	void Enable_Camera_Rotation();
	void Disable_Camera_Rotation();


	float Ticks_Passed = 0;
	const float Ticks_To_Pass = 2.0; 

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* PossessedPawn) override;
	APlayer_Character* ControlledCharacter = nullptr;
	APawn* PawnToPosses = nullptr;
	virtual void BeginPlay() override;

};
