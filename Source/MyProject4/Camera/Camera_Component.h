// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Camera_Component.generated.h"

/**
 * 
 */
class APlayer_Controller;

UCLASS()
class MYPROJECT4_API UCamera_Component : public UCameraComponent
{
	GENERATED_BODY()

		

public:
	UCamera_Component();

	virtual void GetCameraView(float deltaTime, FMinimalViewInfo& desiredView) override;

	void OnZoomIn();
	void OnZoomOut();
	void UpdateCameraMovement(const APlayerController* playerController) const;
	void MoveForward(float value) const;
	void MoveRight(float value) const;
	void SetZoomLevel(float level);
	void RotateX(float value);
	void RotateY(float value);
	void Set_Camera_Location(FVector Location,FRotator Rotation);
	void Reset_Camera_Location();

	//void ClampCameraLocation(const APlayerController* playerController, FVector& outCameraLocation) const;

private:
	float minCameraOffset_;
	float maxCameraOffset_;
	FRotator Camera_Angle;

	float cameraScrollSpeed_;
	uint32 cameraActiveBorder_;
	float minZoomLevel_;
	float maxZoomLevel_;
	float zoomAlpha_;
	float movementSpeed_;

	FVector Target_Location;


	bool bShouldClampCamera_ : 1;

	FBox cameraMovementBounds_;
	FVector2D cameraMovementViewportSize_;

	APawn* GetOwnerPawn() const;
	//	ARTSBR_PlayerController* GetPlayerController() const;
	//void UpdateCameraBounds(const APlayerController* playerController) const;
};
	
