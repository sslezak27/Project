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
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

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
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			void Change_Players_Locations(int boundxl, int boundxh, int boundyl, int boundyh, int z);
		UFUNCTION(BlueprintCallable, Category = "UMG Game")
			void Change_AI_Locations(int boundxl, int boundxh, int boundyl, int boundyh, int z);



private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TArray<int> Spawn_Locations_Players = { 0,0,0,0,0 };
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		TArray<int> Spawn_Locations_AI = { 0,0,0,0,0 };
	AGame_Manager* GameManager = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		TSubclassOf<AGame_Manager> GameManager_BP;
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		USoundCue* Sound;
	UPROPERTY(EditDefaultsOnly, Category = "ActorSpawning")
		USoundCue* Main_Menu_Sound;

	UAudioComponent* Audio_Component;


	AAI_Character* Enemy_Character = nullptr;
	AMyCharacter* A_Character = nullptr;
	bool Can_Camera_Rotate = false;
	AA_HUD* HUD = nullptr;
	bool Is_aiming = false;

	bool Started_Game = false;

	void Select_Location();
	void End_Player_Turn();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void Bring_Character_Sheet();
	void Aim();
	void Shoot(FVector Location);





	void MoveCameraForward(float value);
	void MoveCameraRight(float value);
	void ZoomIn();
	void ZoomOut();
	void Rotate_Camera_X(float value);
	void Rotate_Camera_Y(float value);
	void Enable_Camera_Rotation();
	void Disable_Camera_Rotation();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void Bring_Menu();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void Bring_Main_Menu();
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void Spawn_Game_Manager();




	float Ticks_Passed = 0;
	const float Ticks_To_Pass = 2.0; 

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* PossessedPawn) override;
	APlayer_Character* ControlledCharacter = nullptr;
	APawn* PawnToPosses = nullptr;
	virtual void BeginPlay() override;

};
