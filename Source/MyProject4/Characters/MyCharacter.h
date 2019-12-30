// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Skills/Attack/Attack_Base.h"

#include "Components/DecalComponent.h" 
#include "Kismet/KismetMathLibrary.h" 

#include "Math/UnrealMathUtility.h"
#include "MyCharacter.generated.h"


UCLASS()
class MYPROJECT4_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()
private:
	virtual void Turn_End();
	virtual void DIE();
	int Attack_Melee_Skill = 10;
	int Defence_Melee_Skill = 10;
	bool Is_Dodging = false;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* Targeted_Circle;
	

public:
	// Sets default values for this character's properties
	Attack_Base Current_Skill;
	AMyCharacter();
	virtual int Roll_Iniciative();
	virtual bool Do_Turn(FVector Move_Location);
	virtual void Move_End();
	virtual bool Attack_Target(AMyCharacter* Target);
	virtual void Be_Attacked(Attack_Base* Skill);
	virtual Attack_Base* Get_Skill();
	void Be_Targeted();
	void Reset_Targeted();
	virtual bool Get_Is_Attacking() const;
	virtual void End_Attack();
	virtual AMyCharacter* Get_Target() const;
	virtual bool Get_Is_Being_Attacked() const;
	virtual bool Calculate_Attack_Succes(AMyCharacter* Target);
	virtual int Get_Defence_Melee_Skill() const;
	virtual bool Get_Is_Dodging() const;
	virtual void Set_Dodge(bool Dodge);
	virtual bool Get_Is_Alive() const;
	AMyCharacter* Target_Of_Attack;
	virtual float Get_Health() const;
	virtual float Get_Max_HP() const;
	virtual int Get_Attack_Melee_Skill() const;


	bool Is_Being_Attacked = false;
	bool Is_Attacking = false;
	bool Turn_Done = false;
	bool Is_Turn = false;
	bool Move_Done = true;
	bool Is_Placed = false;
	bool Is_Alive = true;

	int Iniciative;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float HP = 100;
	float Max_HP = 100;

	int Skill_Strength;
	int Ranged_Skill_Aim;
	UPROPERTY()
	UStaticMesh* Mesh_Axe = nullptr;
	UPROPERTY()
	UStaticMesh* Mesh_Sword = nullptr;
	UStaticMesh* Get_Component(int type);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
	void Move_My_Character(const FVector& position);
	int Weapon_Type;
	Attack_Base Attack_Primary;
	Attack_Base Attack_Secondary;

	void Change_Skill(int skill);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	


};
