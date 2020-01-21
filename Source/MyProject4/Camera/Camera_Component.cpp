// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera_Component.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpectatorPawn.h"
#include "Kismet/GameplayStatics.h" 



UCamera_Component::UCamera_Component()
{
	bShouldClampCamera_ = true;

	zoomAlpha_ = 1.f;
	cameraScrollSpeed_ = 3000.f;
	cameraActiveBorder_ = 100.f;
	minZoomLevel_ = 0.01f;
	maxZoomLevel_ = 1.f;
	minCameraOffset_ = 0.f;
	maxCameraOffset_ = 20000.f;
	movementSpeed_ = 100.f;

	Camera_Angle = FRotator(-60.f, 0.f, 0.f);
}

void UCamera_Component::GetCameraView(float deltaTime, FMinimalViewInfo& desiredView)
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this,0);
	if (playerController)
	{
		desiredView.FOV = 30.f;
		const float currentOffset = minCameraOffset_ + zoomAlpha_ * (maxCameraOffset_ - minCameraOffset_);
		const FVector focalPos = playerController->GetFocalLocation();
		desiredView.Location = focalPos	 - Camera_Angle.Vector() * currentOffset;
		desiredView.Rotation = Camera_Angle;
	}
}

void UCamera_Component::OnZoomIn()
{
	SetZoomLevel(zoomAlpha_ - 0.1f);
}

void UCamera_Component::OnZoomOut()
{
	SetZoomLevel(zoomAlpha_ + 0.1f);
}

void UCamera_Component::UpdateCameraMovement(const APlayerController* playerController) const  //Do poprawy
{
	ULocalPlayer* const localPlayer = Cast<ULocalPlayer>(playerController->Player);

	if (localPlayer && localPlayer->ViewportClient && localPlayer->ViewportClient->Viewport)
	{
		FVector2D mousePosition;
		if (!localPlayer->ViewportClient->GetMousePosition(mousePosition))
		{
			return;
		}

		FViewport* viewport = localPlayer->ViewportClient->Viewport;
		const float scrollSpeed = 60.f;
		const FIntPoint viewportSize = viewport->GetSizeXY();

		const uint32 viewLeft = FMath::TruncToInt(localPlayer->Origin.X * viewportSize.X);
		const uint32 viewRight = viewLeft + FMath::TruncToInt(localPlayer->Size.X * viewportSize.X);
		const uint32 viewTop = FMath::TruncToInt(localPlayer->Origin.Y * viewportSize.Y);
		const uint32 viewBottom = viewTop + FMath::TruncToInt(localPlayer->Size.Y * viewportSize.Y);

		const float maxSpeed = cameraScrollSpeed_ * FMath::Clamp(zoomAlpha_, minZoomLevel_, maxZoomLevel_);

		const uint32 mouseX = mousePosition.X;
		const uint32 mouseY = mousePosition.Y;
		float spectatorCameraSpeed = maxSpeed;
		//ARTSBR_SpectatorPawn* spectatorPawn = nullptr;

		if (true) //!bNoScrollZone_
		{
			if (mouseX >= viewLeft && mouseX <= (viewLeft + cameraActiveBorder_))
			{
				const float delta = 1.0f - float(mouseX - viewLeft) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveRight(-scrollSpeed * delta);
			}
			else if (mouseX >= (viewRight - cameraActiveBorder_) && mouseX <= viewRight)
			{
				const float delta = float(mouseX - viewRight + cameraActiveBorder_) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveRight(scrollSpeed * delta);
			}

			if (mouseY >= viewTop && mouseY <= (viewTop + cameraActiveBorder_))
			{
				const float delta = 1.0f - float(mouseY - viewTop) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveForward(scrollSpeed * delta);
			}
			else if (mouseY >= (viewBottom - cameraActiveBorder_) && mouseY <= viewBottom)
			{
				const float delta = float(mouseY - (viewBottom - cameraActiveBorder_)) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveForward(-scrollSpeed * delta);
			}
		}
	}
}

void UCamera_Component::MoveForward(const float value) const
{
	APawn* ownerPawn = GetOwnerPawn();

	if (ownerPawn)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(this,0);
		if (value != 0.f && controller)
		{
			// If our camera is not rotated or we want to use camera's local coordinates, we can use rotationMatrix
			//const FRotationMatrix rotationMatrix(controller->PlayerCameraManager->GetCameraRotation());
			const FVector worldSpaceAcc = /*rotationMatrix.GetScaledAxis(EAxis::X)*/ FVector(1.f, 0.f, 0.f) * movementSpeed_;

			ownerPawn->AddMovementInput(worldSpaceAcc, value);
		}
	}
}

void UCamera_Component::MoveRight(const float value) const
{
	APawn* ownerPawn = GetOwnerPawn();

	if (ownerPawn)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(this,0);
		if (value != 0.f && controller)
		{
			// If our camera is not rotated or we want to use camera's local coordinates, we can use rotationMatrix
			//const FRotationMatrix rotationMatrix(controller->PlayerCameraManager->GetCameraRotation());
			const FVector worldSpaceAcc = /*rotationMatrix.GetScaledAxis(EAxis::Y)*/ FVector(0.f, 1.f, 0.f) * movementSpeed_;

			ownerPawn->AddMovementInput(worldSpaceAcc, value);
		}
	}
}

void UCamera_Component::SetZoomLevel(float level)
{
	zoomAlpha_ = FMath::Clamp(level, minZoomLevel_, maxZoomLevel_);
}

APawn* UCamera_Component::GetOwnerPawn() const
{
	return Cast<APawn>(GetOwner());
}

void UCamera_Component::RotateX(const float value)
{
	Camera_Angle.Yaw += 10*value;

}

void UCamera_Component::RotateY(const float value)
{
	Camera_Angle.Pitch += 10*value;
}

void UCamera_Component::Set_Camera_Location(FVector Location,FRotator Rotation)
{

	APawn* ownerPawn = GetOwnerPawn();
	if (ownerPawn != nullptr)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
		Camera_Angle = Rotation;
		MoveForward(Location.X);
		MoveRight(Location.Y);
		SetZoomLevel(Location.Z);

	}
}

void UCamera_Component::Reset_Camera_Location()
{
}



/**ARTSBR_PlayerController* UCamera_Component::UGameplayStatics::GetPlayerController(this,0) const
{
	ARTSBR_PlayerController* controller = nullptr;
	APawn* owner = GetOwnerPawn();
	if (owner)
	{
		controller = Cast<ARTSBR_PlayerController>(owner->GetController());
	}

	return controller;
}**/