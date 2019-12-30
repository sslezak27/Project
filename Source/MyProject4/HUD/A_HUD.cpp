// Fill out your copyright notice in the Description page of Project Settings.


#include "A_HUD.h"


#include "Components/CapsuleComponent.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

AA_HUD::AA_HUD()
{
	PrimaryActorTick.bCanEverTick = false;

	const ConstructorHelpers::FObjectFinder<UTexture2D> topInfoBarTextureAsset(TEXT("Texture2D'/Game/Assets/HUD/Icon/Textures/PlayerHealthBar/T_HealthBar_Ico.T_HealthBar_Ico'"));
	if (topInfoBarTextureAsset.Object) Health_Void = topInfoBarTextureAsset.Object;

	const ConstructorHelpers::FObjectFinder<UTexture2D> topInfoBarTextureAsset3(TEXT("Texture2D'/Game/Assets/HUD/Icon/Textures/PlayerHealthBar/T_HealthBarFull_Ico.T_HealthBarFull_Ico'"));
	if (topInfoBarTextureAsset3.Object) Health_Bard = topInfoBarTextureAsset3.Object;

	const ConstructorHelpers::FObjectFinder<UTexture2D> topInfoBarTextureAsset2(TEXT("Texture2D'/Game/Assets/HUD/Icon/Textures/PlayerHealthBar/T_HealthBarGlass_Ico.T_HealthBarGlass_Ico'"));
	if (topInfoBarTextureAsset2.Object) Health_Lost = topInfoBarTextureAsset2.Object;




	const ConstructorHelpers::FObjectFinder<UTexture2D> topInfoBarTextureAsset4(TEXT("Texture2D'/Game/Assets/HUD/Icon/Textures/Skills/T_2D_BorderSkill_BG.T_2D_BorderSkill_BG'"));
	if (topInfoBarTextureAsset4.Object) Character_Sheet_Bg = topInfoBarTextureAsset4.Object;

	const ConstructorHelpers::FObjectFinder<UTexture2D> topInfoBarTextureAsset5(TEXT("Texture2D'/Game/Assets/HUD/Icon/Textures/Skills/T_SkillBox_Ico.T_SkillBox_Ico'"));
	if (topInfoBarTextureAsset5.Object) Character_Sheet_Space = topInfoBarTextureAsset5.Object;

	const ConstructorHelpers::FObjectFinder<UFont> uiFontAsset(TEXT("Font'/Game/Assets/Fonts/Perpetua_Font.Perpetua_Font'"));
	if (uiFontAsset.Object) HUD_Font = uiFontAsset.Object;
}
	
void AA_HUD::BeginPlay()
{
	Super::BeginPlay();
	//ChangeWidget(Character_Sheet_Widget);
}

void AA_HUD::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void AA_HUD::DrawHUD()
{
	Super::DrawHUD();

	if (GEngine && GEngine->GameViewport)
	{
		FVector2D viewportSize;
		GEngine->GameViewport->GetViewportSize(viewportSize);
		uiScale_ = viewportSize.X / 2048.f;
	}
	DrawHealthBars();
	//if (Current_APlayer_In_Player != nullptr)
/**	{
		DrawMain(1);
	}
	if (To_Draw_Character_Sheet)
	{
		//DrawCharacterSheet(Current_Player_Character	);
	}**/
}

void AA_HUD::DrawMain(bool draw)
{
	if (draw == true)
	{
		ChangeWidget(Character_Main_Widget);
	}
	else
		ChangeWidget(nullptr);

}

void AA_HUD::DrawHealthBars() const
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "CALLING_DRAW_HELTHBAR");

	DrawHealthBar(Current_Player_Character);
	DrawHealthBar(Current_Selected_Character);
}

void AA_HUD::DrawHealthBar(AMyCharacter* Target) const
{
	if (Target != nullptr && Target->Get_Health() > 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "CALLEDTARGETs");

		// punkt przy³o¿enia
		FVector center = Target->GetActorLocation();
		// rozmiary
		//center.X = center.X * 2;
		//center.Y = center.Y * 2 + 100;
		FVector extent = FVector(60.f, 34.f, 131.75f);
		// Zamiania pozycje w swiecie na ta na ekranie
		FVector2D center2D = FVector2D(Canvas->Project(FVector(center.X, center.Y, center.Z + extent.Z)));
		float actorExtent = 150.f;
		float healthPercentage = 0.5f;
		float yOffset = 10.f;
		healthPercentage = Target->Get_Health() / Target->Get_Max_HP();
		//actorExtent = Target->GetCapsuleComponent()->GetScaledCapsuleRadius(); // Roziar hitboxa kapsu³y
		FVector pos1 = Canvas->Project(FVector(center.X, center.Y - actorExtent * 2, center.Z + extent.Z));
		FVector pos2 = Canvas->Project(FVector(center.X, center.Y + actorExtent * 2, center.Z + extent.Z)); //pozycje +-
		float barWidth = (pos2 - pos1).Size2D(); //rozmiar paska
		float barHeight = barWidth * 0.2f;
		// Draw a background color first
			/* Background tile */
		barWidth += 2.f;
		barHeight += 2.f;
		float x = center2D.X - barWidth * 0.5f;
		float y = center2D.Y;

		FCanvasTileItem tileItem3(FVector2D(x, y), Health_Void->Resource, FVector2D(barWidth, barHeight), FLinearColor(0.0f, 0.0f, 0.0f, 0.5f));
		tileItem3.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(tileItem3);

		FCanvasTileItem tileItem2(FVector2D(x, y), Health_Lost->Resource, FVector2D(barWidth, barHeight), FLinearColor(0.0f, 0.0f, 0.0f, 0.5f));
		tileItem2.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(tileItem2);
		/* Background tile */
		// Draw the health indicator
			/* Health tile */
		FCanvasTileItem tileItem(FVector2D(x, y), Health_Lost->Resource, FVector2D(barWidth, barHeight), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
		tileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(tileItem);

		barWidth -= 2.f;
		barHeight -= 2.f;

		x = center2D.X - barWidth * 0.5f;
		y = center2D.Y + 1.f;

		tileItem.Position = FVector2D(x, y);
		tileItem.SetColor(FLinearColor(1.0f, 0.2f, 0.1f, 2.f));
		tileItem.Size = FVector2D(barWidth * healthPercentage, barHeight);
		Canvas->DrawItem(tileItem);
		/* Health tile */


	}

}

void AA_HUD::DrawCharacterSheet(AMyCharacter* Target)
{
	// Get window width to draw the bar to make it fill the entire top side
	const float gridWidth = GEngine->GameViewport->Viewport->GetSizeXY().X;
	// Set grid height as the texture's height
	float gridHeight = GEngine->GameViewport->Viewport->GetSizeXY().Y;


	FCanvasTileItem tileItem3(FVector2D(0, 0), Character_Sheet_Bg->Resource, FVector2D(gridWidth, gridHeight), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	tileItem3.BlendMode = SE_BLEND_Translucent;
	//tileItem3.UV1 = FVector2D(0.5f, 0.5f);
	Canvas->DrawItem(tileItem3);

	const FString gameText("Melee Attack:  ");
	const FString gameText2("Melee Defence:  ");
	float textWidth = 0;
	float textHeight = 0;


	FCanvasTileItem tileItemWhite(FVector2D(0.2f*gridWidth, 0.2f*gridHeight), Character_Sheet_Space->Resource, FVector2D(0.1f*gridWidth, 0.1f*gridHeight), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	tileItemWhite.BlendMode = SE_BLEND_Translucent;
	//tileItem3.UV1 = FVector2D(0.5f, 0.5f);
	Canvas->DrawItem(tileItemWhite);

	tileItemWhite.Position = FVector2D(0.2f * gridWidth, 0.4f * gridHeight);
	Canvas->DrawItem(tileItemWhite);


	GetTextSize(gameText, textWidth, textHeight, HUD_Font);
	if (HUD_Font!= nullptr && Target != nullptr)
	{
		DrawText((gameText2+FString::FromInt(Target->Get_Defence_Melee_Skill())), FLinearColor::White, (0.2f*gridWidth), (0.22f*gridHeight), HUD_Font);
		DrawText((gameText+FString::FromInt(Target->Get_Attack_Melee_Skill())), FLinearColor::White, (0.2f*gridWidth), (0.42f*gridHeight), HUD_Font);
	}

}

void AA_HUD::Set_Current_Player_Character(AMyCharacter* Target)
{
	Current_Player_Character = Target;
}

void AA_HUD::Set_Current_Selected_Character(AMyCharacter* Target)
{
	Current_Selected_Character = Target;
}

void AA_HUD::Set_Current_APlayer_In_Player(AMyCharacter* Target)
{
	Current_APlayer_In_Player = Target;
	if (Current_APlayer_In_Player != nullptr)
		DrawMain(true);
	else
		DrawMain(false);

}

void AA_HUD::Set_To_Draw_Character_Sheet(bool draw)
{
	To_Draw_Character_Sheet = draw;
	if (To_Draw_Character_Sheet == true)
	{

		ChangeWidget(Character_Sheet_Widget);
	}
	else if (Current_APlayer_In_Player != nullptr)
		DrawMain(true);
	else
	{
		ChangeWidget(nullptr);
	}
}

bool AA_HUD::Get_To_Draw_Character_Sheet()
{
	return To_Draw_Character_Sheet;
}

float AA_HUD::Get_Health_Percentage()
{
	if (Get_Current_APlayer_In_Player() != nullptr)

	{
		float healthPercentage = Get_Current_APlayer_In_Player()->Get_Health() / Get_Current_APlayer_In_Player()->Get_Max_HP();
		return healthPercentage;
	}
	else
		return 0;
}

float AA_HUD::Get_Halth_Max()
{
	if (Get_Current_APlayer_In_Player() != nullptr)
		return Get_Current_APlayer_In_Player()->Get_Max_HP();
	else
		return 0;
}

float AA_HUD::Get_Health_Current()
{
	if (Get_Current_APlayer_In_Player() != nullptr)
		return Get_Current_APlayer_In_Player()->Get_Health();
	else
		return 0;
}

void AA_HUD::Change_Skill(int skill)
{
	if (Get_Current_APlayer_In_Player() != nullptr)
	{
		Get_Current_APlayer_In_Player()->Change_Skill(skill);
		Current_Skill = skill;
	}
		
}

int AA_HUD::Get_Current_Skill()
{
	return Current_Skill;
}

AMyCharacter* AA_HUD::Get_Current_Selected_Character()
{
	return Current_Selected_Character;
}

AMyCharacter* AA_HUD::Get_Current_APlayer_In_Player() const
{
	return Current_APlayer_In_Player;
}

int AA_HUD::Get_Defence_Melee_Skill() const
{
	if (Get_Current_APlayer_In_Player() != nullptr)
		return Get_Current_APlayer_In_Player()->Get_Defence_Melee_Skill();
	else
		return 0;
}

int AA_HUD::Get_Attack_Melee_Skill() const
{
	if (Get_Current_APlayer_In_Player() != nullptr)
		return  Get_Current_APlayer_In_Player()->Get_Attack_Melee_Skill();
	else
		return 0;
}

float AA_HUD::Get_Health() const
{
	if (Get_Current_APlayer_In_Player() != nullptr)
		return  Get_Current_APlayer_In_Player()->Get_Health();
	else
		return 0;
}

float AA_HUD::Get_Max_HP() const
{
	if (Get_Current_APlayer_In_Player() != nullptr)
		return  Get_Current_APlayer_In_Player()->Get_Max_HP();
	else
		return 0;
}

float AA_HUD::Get_Dmg(int main) const
{
	if (Get_Current_APlayer_In_Player() != nullptr)
		if (main == 0)
			return Get_Current_APlayer_In_Player()->Attack_Primary.Attack_Dmg;
		else
			return Get_Current_APlayer_In_Player()->Attack_Secondary.Attack_Dmg;
	else
		return 0;
}

float AA_HUD::Get_Range(int main) const
{
	if (Get_Current_APlayer_In_Player() != nullptr)
		if(main == 0)
			return Get_Current_APlayer_In_Player()->Attack_Primary.Attack_Range;
		else
			return Get_Current_APlayer_In_Player()->Attack_Secondary.Attack_Range;
	else
		return 0;
}

float AA_HUD::Get_Fat(int main) const
{
	if (Get_Current_APlayer_In_Player() != nullptr)
		if (main == 0)
			return Get_Current_APlayer_In_Player()->Attack_Primary.Attack_Fatigue;
		else
			return Get_Current_APlayer_In_Player()->Attack_Secondary.Attack_Fatigue;
	else
		return 0;
}

float AA_HUD::Get_Hit(int main) const
{
	if (Get_Current_APlayer_In_Player() != nullptr)
		if (main == 0)
			return Get_Current_APlayer_In_Player()->Attack_Primary.Base_Hit_Chance;
		else
			return Get_Current_APlayer_In_Player()->Attack_Secondary.Base_Hit_Chance;
	else
		return 0;
}

void AA_HUD::ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{

	if (CurrentWidget != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "avav");
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "bbvbvbv");
			CurrentWidget->AddToViewport();
		}
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "duas");
}
