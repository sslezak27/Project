// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "Characters/MyCharacter.h"
#include "A_HUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT4_API AA_HUD : public AHUD
{
	GENERATED_BODY()
public:
	AA_HUD();
	void BeginPlay() override;
	void Tick(float deltaSeconds) override;
	void Set_Current_Player_Character(AMyCharacter* Target); //current character in play could be player or ai
	void Set_Current_Selected_Character(AMyCharacter* Target);
	void Set_Current_APlayer_In_Player(AMyCharacter* Target);
	void Set_To_Draw_Character_Sheet(bool draw);
	bool Get_To_Draw_Character_Sheet();
	bool Get_To_Draw_Game_Menu();
	void DrawGameMenu(bool draw);
	bool Get_To_Draw_Main_Menu() { return To_Draw_Main_Menu; }
	void DrawMainMenu(bool draw);

	FVector Get_Main_Menu_Locaiton(){ return Main_Menu_Location; }
	FRotator Get_Main_Menu_Rotation (){ return Main_Menu_Rotation;  }


	bool End_Player_Aim = false;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	float Get_Health_Percentage();
	float Get_Halth_Max();
	float Get_Health_Current();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void Change_Skill(int skill);

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	int Get_Current_Skill();

	AMyCharacter* Get_Current_Selected_Character();
	AMyCharacter* Get_Current_APlayer_In_Player() const;


	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		int Get_Gun_X() const  {
		if (Get_Current_APlayer_In_Player() != nullptr)
			return Get_Current_APlayer_In_Player()->Get_Gun_Stability_X();
		else
			return 0;
	}

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		int Get_Gun_Y() const  {
		if (Get_Current_APlayer_In_Player() != nullptr)
			return Get_Current_APlayer_In_Player()->Get_Gun_Stability_Y();
		else
			return 0;
	}



	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	int Get_Defence_Melee_Skill() const;
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	int Get_Attack_Melee_Skill() const;
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	float Get_Health() const;
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	float Get_Max_HP() const;
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		float Get_Dmg(int main) const;
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		float Get_Range(int main) const;
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		float Get_Fat(int main) const;
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		float Get_Hit(int main) const;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		bool Is_Skill_Magical(int main);

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void Set_Magic_Power(float X_Speed, float Y_Speed) const;
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void Cancel_Fire();


	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass); //FUNCKJA BEZPIECZNA, MO¯E BYC TYLKO 1 WIDGET TEJ FUNCJI NA RAZ
	UFUNCTION(BlueprintCallable, Category = "UMG Game")                   //FUNCJA BEZ ZAPEZPIECZEN CO DO ILOSCI WIDGETOW, TRZEBA PAMIETAC O USOWANIU
		void AddWidget(TSubclassOf<UUserWidget> NewWidgetClass); 
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void RemoveWidget(TSubclassOf<UUserWidget> NewWidgetClass, int index = -1);



	int Get_Player_Numbers() { return Player_Numbers; }
	int Get_AI_Numbers() { return AI_Numbers; }
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void Set_Player_Numbers(int number) { Player_Numbers = number; }
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void Set_AI_Numbers(int number) { AI_Numbers = number; }



private:
	// Main drawing function	
	int Current_Skill;
	virtual void DrawHUD() override;
	void DrawMain(bool draw);
	void DrawHealthBars() const;
	void DrawHealthBar(AMyCharacter* Target) const;
	void DrawCharacterSheet(AMyCharacter* Target);

	float uiScale_;
	float Health_Percentage;
	float Health_Current;
	float Health_Max;


	bool To_Draw_Main_Menu = false;

	AMyCharacter* Current_Player_Character = nullptr;
	AMyCharacter* Current_Selected_Character = nullptr;

	AMyCharacter* Current_APlayer_In_Player = nullptr; //Currently player Player Character

	bool To_Draw_Character_Sheet = false;
	bool To_Draw_Game_Menu = false;
//	void ChangeWidget(TSubclassOf<UUserWidget> NewWidgetClass);


	UFont* HUD_Font = nullptr;
	UTexture2D* Health_Void = nullptr;
	UTexture2D* Health_Bard = nullptr;
	UTexture2D* Health_Lost = nullptr;


	UTexture2D* Character_Sheet_Bg = nullptr;
	UTexture2D* Character_Sheet_Space = nullptr;

	UTexture2D* Skill_Bg = nullptr;
	UTexture2D* Skill_Box = nullptr;


	int Player_Numbers = 0;
	int AI_Numbers = 0;

	
protected:
	UPROPERTY()
		UUserWidget* CurrentWidget;
	UPROPERTY()
		TArray<UUserWidget*> MenuWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> Character_Sheet_Widget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> Character_Main_Widget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> Manu_Pause_Widget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> Main_Menu_Widget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		FVector Main_Menu_Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		FRotator Main_Menu_Rotation;
};
