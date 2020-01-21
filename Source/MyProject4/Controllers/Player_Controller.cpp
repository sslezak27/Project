// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Controller.h"

APlayer_Controller::APlayer_Controller()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;


	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	//CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Characters/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);


	}
	CursorToWorld->DecalSize = FVector(1, 1, 1);
	CursorToWorld->SetWorldScale3D(FVector(0, 0, 0));


	Audio_Component = CreateDefaultSubobject<UAudioComponent>(TEXT("PropellerAudioComp"));
	// I don't want the sound playing the moment it's created.
	Audio_Component->bAutoActivate = false; // don't play the sound immediately.
	// I want the sound to follow the pawn around, so I attach it to the Pawns root.
	Audio_Component->SetupAttachment(RootComponent);
	//CursorToWorld->SetWorld	Rotation(FRotator(0, PI / 2, 0));
	//CursorToWorld->SetWorldLocation()
	
	

}

void APlayer_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();


	InputComponent->BindAction("Idzdocelu", IE_Pressed, this, &APlayer_Controller::Select_Location);
	InputComponent->BindAction("Koniec_Tury", IE_Pressed, this, &APlayer_Controller::End_Player_Turn);
	InputComponent->BindAction("Aim", IE_Pressed, this, &APlayer_Controller::Aim);
	InputComponent->BindAction("Esc", IE_Pressed, this, &APlayer_Controller::Bring_Menu).bExecuteWhenPaused = true;
	InputComponent->BindAction("Character_Sheet", IE_Pressed, this, &APlayer_Controller::Bring_Character_Sheet).bExecuteWhenPaused = true;


	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APlayer_Controller::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &APlayer_Controller::ZoomOut);


	InputComponent->BindAxis("Move_Camera_Forward", this, &APlayer_Controller::MoveCameraForward);
	InputComponent->BindAxis("Move_Camera_Right", this, &APlayer_Controller::MoveCameraRight);

	InputComponent->BindAction("Enable_Camera_Rotation", IE_Pressed, this, &APlayer_Controller::Enable_Camera_Rotation);
	InputComponent->BindAction("Enable_Camera_Rotation", IE_Released, this, &APlayer_Controller::Disable_Camera_Rotation);

	InputComponent->BindAxis("Rotate_Camera_X", this, &APlayer_Controller::Rotate_Camera_X);
	InputComponent->BindAxis("Rotate_Camera_Y", this, &APlayer_Controller::Rotate_Camera_Y);


	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "BINDED_CONTROLLER");

	



	
}

void APlayer_Controller::End_Player_Turn()
{
	if (Started_Game)
	{
		if (GameManager->Player_Turn == true)
		{
			GameManager->End_Player_Turn();
		}
	}
}

void APlayer_Controller::Bring_Character_Sheet()
{
	if (Started_Game)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Called_Bring_This");

		if (HUD->Get_To_Draw_Character_Sheet())
		{
			HUD->Set_To_Draw_Character_Sheet(false);
			SetPause(false);
		}
		else
		{
			HUD->Set_To_Draw_Character_Sheet(true);
			SetPause(true);
		}
	}
}

void APlayer_Controller::Aim()
{
	if (Started_Game)
	{
		if (Is_aiming)
		{
			Is_aiming = false;
			GameManager->Player_End_Aim();
			//CursorToWorld->DecalSize = FVector(0.0f, 0.0f, 0.0f); 
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "NO AIM");
		}
		else
		{
			Is_aiming = GameManager->Can_Player_Aim();
			if (Is_aiming)
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "AIM");
			else
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "NO AIM NO GAIN");
			CursorToWorld->SetWorldScale3D(FVector(10, 10, 10));
		}
	}
}

void APlayer_Controller::Shoot(FVector Location)
{
	if (Started_Game)
	{
		Is_aiming = false;
		//		CursorToWorld->DecalSize = FVector(0.0f, 0.0f, 0.0f);
		GameManager->Player_Shoot(Location);
	}
}

void APlayer_Controller::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);
}

void APlayer_Controller::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());

	if (HUD == nullptr)
	{
		HUD = Cast<AA_HUD>(GetHUD());
		Bring_Main_Menu();
	}


}

void APlayer_Controller::Select_Location()
{
	if (Started_Game)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "SELECTED LOCATION");
		if (GameManager->Player_Turn == true)
		{
			FHitResult Hit;
			GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, Hit);
			if (Hit.GetActor() != nullptr)
			{
				if (Is_aiming)
					Shoot(Hit.Location);
				else
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



		}

	}
}



void APlayer_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Started_Game)
	{

		Ticks_Passed += DeltaTime;
		if (Ticks_Passed >= Ticks_To_Pass) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "CALLING_NOTHING");
			Ticks_Passed = 0;
			FHitResult Hit;
			GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, Hit);
			if (Hit.GetActor() != nullptr)
			{
				if ((A_Character = Cast<AMyCharacter>(Hit.GetActor())) != nullptr)
				{
					//if (HUD->Get_Current_Selected_Character() != A_Character)
					//{	
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "CALLING_YOURMOMG");
					HUD->Set_Current_Selected_Character(A_Character);
					//}

				}
				else
					HUD->Set_Current_Selected_Character(nullptr);


			}
		}
		if (Is_aiming)
		{
			if (HUD->End_Player_Aim)
			{
				Aim();
			}
			else
			{
				FHitResult Hit;
				GetHitResultUnderCursor(ECollisionChannel::ECC_WorldDynamic, false, Hit);
				GameManager->Player_Aim(Hit.Location);
			}
		}


		if (Audio_Component->IsPlaying() == false)
		{
			Audio_Component->Play();
		}


	}



	
}

void APlayer_Controller::Change_Skill(int skill)
{
	if (Started_Game)
	{
		HUD->Change_Skill(skill);
		GameManager->Reset_Player_Targets();
	}
}

void APlayer_Controller::Change_Players_Locations(int boundxl, int boundxh, int boundyl, int boundyh, int z)
{
	Spawn_Locations_Players[0] = boundxl;
	Spawn_Locations_Players[1] = boundxh;
	Spawn_Locations_Players[2] = boundyl;
	Spawn_Locations_Players[3] = boundyh;
	Spawn_Locations_Players[4] = z;
}

void APlayer_Controller::Change_AI_Locations(int boundxl, int boundxh, int boundyl, int boundyh, int z)
{
	Spawn_Locations_AI[0] = boundxl;
	Spawn_Locations_AI[1] = boundxh;
	Spawn_Locations_AI[2] = boundyl;
	Spawn_Locations_AI[3] = boundyh;
	Spawn_Locations_AI[4] = z;

}

//OBS£UGA CAMERY

ACamera_Pawn* APlayer_Controller::GetMainSpectatorPawn() const
{
	return Cast<ACamera_Pawn>(GetPawn());
}

void APlayer_Controller::ZoomIn()
{
	if (Started_Game)
	{
		ACamera_Pawn* spectatorPawn;  //Klasa zarz¹dzaj¹ca kamera
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Called Zoom");
		if ((spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Zooming");
			spectatorPawn->OnMouseScrollUp();
		}
	}
}


void APlayer_Controller::ZoomOut()
{
	if (Started_Game)
	{
		ACamera_Pawn* spectatorPawn;
		if ((spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Zooming");
			spectatorPawn->OnMouseScrollDown();
		}
	}
}


void APlayer_Controller::MoveCameraForward(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Called Move Camera");
	if (Started_Game)
	{
		ACamera_Pawn* spectatorPawn;
		if (value != 0.f && (spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, " Move Camera");

			spectatorPawn->MoveForward(value);
		}
	}

}

void APlayer_Controller::MoveCameraRight(float value)
{
	if (Started_Game)
	{//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Called Move Camera");

		ACamera_Pawn* spectatorPawn;
		if (value != 0.f && (spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, " Move Camera");

			spectatorPawn->MoveRight(value);
		}
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

void APlayer_Controller::Bring_Menu()
{
	if (Started_Game)
	{
		if (HUD->Get_To_Draw_Game_Menu())
		{
			HUD->DrawGameMenu(false);
			SetPause(false);
		}
		else
		{
			HUD->DrawGameMenu(true);
			SetPause(true);
		}
	}
}

void APlayer_Controller::Bring_Main_Menu()
{
	if (HUD->Get_To_Draw_Main_Menu())
	{	
		HUD->DrawMainMenu(false);
		Audio_Component->SetSound(Sound);
		Audio_Component->Play();
	}
	else
	{
		ACamera_Pawn* spectatorPawn;
		if ((spectatorPawn = Cast<ACamera_Pawn>(GetPawn())) != nullptr)
		{

			spectatorPawn->Set_Camera_Location(HUD->Get_Main_Menu_Locaiton(), HUD->Get_Main_Menu_Rotation());
		}
		HUD->DrawMainMenu(true);
		Started_Game = false;
		Audio_Component->SetSound(Main_Menu_Sound);
		Audio_Component->Play();
	}

}

void APlayer_Controller::Spawn_Game_Manager()
{
	GameManager = GetWorld()->SpawnActor<AGame_Manager>(GameManager_BP,FVector(0, 0, 50), FRotator::ZeroRotator);
	if (GameManager != nullptr && HUD != nullptr && GameManager->HUD_ == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, " SPAWNED HUD");
		GameManager->HUD_ = HUD;



		//AA_HUD* HUD_Temp = Cast<AA_HUD>(HUD);
		//if(HUD_Temp != nullptr)
		//GameManager->HUD = HUD_Temp;
		GameManager->Spawn_Player_Actors(HUD->Get_Player_Numbers(),Spawn_Locations_Players);
		GameManager->Spawn_AI_Actors(HUD->Get_AI_Numbers(),Spawn_Locations_AI);
		Started_Game = true;
		GameManager->Begin_Combat();
	}
	
}

void APlayer_Controller::Rotate_Camera_X(float value)
{
	if (Started_Game)
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
}

void APlayer_Controller::Rotate_Camera_Y(float value)
{
	if (Started_Game)
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
}