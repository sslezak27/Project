// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Controller.h"

APlayer_Controller::APlayer_Controller()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	
	

}

void APlayer_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Idzdocelu", IE_Pressed, this, &APlayer_Controller::Select_Location);
	InputComponent->BindAction("Koniec_Tury", IE_Pressed, this, &APlayer_Controller::End_Player_Turn);



	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APlayer_Controller::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &APlayer_Controller::ZoomOut);


	InputComponent->BindAxis("Move_Camera_Forward", this, &APlayer_Controller::MoveCameraForward);
	InputComponent->BindAxis("Move_Camera_Right", this, &APlayer_Controller::MoveCameraRight);

	InputComponent->BindAction("Enable_Camera_Rotation", IE_Pressed, this, &APlayer_Controller::Enable_Camera_Rotation);
	InputComponent->BindAction("Enable_Camera_Rotation", IE_Released, this, &APlayer_Controller::Disable_Camera_Rotation);

	InputComponent->BindAxis("Rotate_Camera_X", this, &APlayer_Controller::Rotate_Camera_X);
	InputComponent->BindAxis("Rotate_Camera_Y", this, &APlayer_Controller::Rotate_Camera_Y);


	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "BINDED_CONTROLLER");
	GameManager = GetWorld()->SpawnActor<AGame_Manager>(FVector(0, 0, 50), FRotator::ZeroRotator);


}

void APlayer_Controller::End_Player_Turn()
{
	if (GameManager->Player_Turn == true)
	{
		GameManager->End_Player_Turn();
	}
}

void APlayer_Controller::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);
}

void APlayer_Controller::Select_Location()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "SELECTED LOCATION");
	if (GameManager->Player_Turn == true)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, Hit);
		if (Hit.GetActor() != nullptr)
		{
			if ((Enemy_Character = Cast<AAI_Character>(Hit.GetActor())) != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "HIT_ENEMY");
				GameManager->Attack_Player(Enemy_Character);

			}
			else if (Hit.bBlockingHit)
			{


				// We hit something, move there
				GameManager->Move_Player(Hit.Location);
				//ControlledCharacter->Move_My_Character(Hit.Location);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "CALLING_MOVE");
			}
			else
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "CALLING_NOTHING");
		}
		


	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "CALLING_NO THING");
}



void APlayer_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//OBS�UGA CAMERY

ACamera_Pawn* APlayer_Controller::GetMainSpectatorPawn() const
{
	return Cast<ACamera_Pawn>(GetPawn());
}

void APlayer_Controller::ZoomIn()
{
	ACamera_Pawn* spectatorPawn;  //Klasa zarz�dzaj�ca kamera
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Called Zoom");
	if ((spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Zooming");
		spectatorPawn->OnMouseScrollUp();
	}
}


void APlayer_Controller::ZoomOut()
{
	ACamera_Pawn* spectatorPawn;
	if ((spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Zooming");
		spectatorPawn->OnMouseScrollDown();
	}
}


void APlayer_Controller::MoveCameraForward(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Called Move Camera");

	ACamera_Pawn* spectatorPawn;
	if (value != 0.f && (spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, " Move Camera");

		spectatorPawn->MoveForward(value);
	}

}

void APlayer_Controller::MoveCameraRight(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Called Move Camera");

	ACamera_Pawn* spectatorPawn;
	if (value != 0.f && (spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, " Move Camera");

		spectatorPawn->MoveRight(value);
	}

}

void APlayer_Controller::Enable_Camera_Rotation()
{
	Can_Camera_Rotate = true;
}

void APlayer_Controller::Disable_Camera_Rotation()
{
	Can_Camera_Rotate = false;
}

void APlayer_Controller::Rotate_Camera_X(float value)
{
	if (Can_Camera_Rotate)
	{
		ACamera_Pawn* spectatorPawn;

		if (value != 0.f && (spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
		{

			spectatorPawn->OnMouseRotateX(value);
		}

	}

}

void APlayer_Controller::Rotate_Camera_Y(float value)
{
	if (Can_Camera_Rotate)
	{
		ACamera_Pawn* spectatorPawn;

		if (value != 0.f && (spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
		{

			spectatorPawn->OnMouseRotateY(value);
		}

	}

}