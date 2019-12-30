// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MyCharacter.h"
#include "Characters/Controllers/AI_Controller.h"
#include "Pathfinding/Pathfinder.h"
#include "Characters/Skills/Attack_Effects/Arrow.h"
#include "Characters/Skills/Weapons/Base_Weapon.h"

#include "Player_Character.generated.h"


/**
 * 
 */
UCLASS()
class MYPROJECT4_API APlayer_Character : public AMyCharacter
{
	GENERATED_BODY()
	public:
		APlayer_Character();
		virtual int Roll_Iniciative() override;
		virtual bool Do_Turn(FVector Move_Location) override;
		virtual void Tick(float DeltaTime) override;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
			class UDecalComponent* CursorToWorld;
		virtual void Move_End() override;				
		AAI_Controller* AI_Controller = nullptr;
		void Reset_Scale(); //Resetuje rozmiar ko³a
		void Change_Scale(); //Zmienia rozmiar ko³a
		bool Attack_Target(AMyCharacter* Target) override;
		virtual void Turn_End() override;

		int const Action_Points_Max = 40;
		int Action_Points_Current = 40;

	private:

		AArrow* Current_Arrow = nullptr;


		void Jumps();
		Pathfinder Pathfinder;
//	UPROPERTY(VisibleDefaultsOnly, Category = "Sword") // This is so we can set the mesh in the editor
	//	UStaticMeshComponent* Weapon;
	UPROPERTY(VisibleDefaultsOnly, Category = "Sword") // This is so we can set the mesh in the editor
		UStaticMeshComponent* Active_Weapon;
public:
//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sword") // This is so we can set the mesh in the editor
	//UPROPERTY()
	Base_Weapon BaseWeapon;

	protected:
		
			virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
			int Iniciative = 50;
protected:
	virtual void BeginPlay() override;
};
