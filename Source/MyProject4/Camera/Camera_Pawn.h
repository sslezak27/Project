// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "Camera_Component.h"
#include "Camera_Pawn.generated.h"


 
UCLASS()
class MYPROJECT4_API ACamera_Pawn : public ASpectatorPawn
{
	
	GENERATED_BODY()

		friend class APlayer_Controller;

public:
	ACamera_Pawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	UCamera_Component* GetCameraComponent()
	{
		return cameraComponent;
	}

private:
	void MoveForward(float value);
	void MoveRight(float value);
	void OnMouseScrollUp();
	void OnMouseScrollDown();
	void OnMouseRotateX(float value);
	void OnMouseRotateY(float value);


	UCamera_Component* cameraComponent;
};
