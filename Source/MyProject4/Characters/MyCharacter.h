// Fill out your copyright n	otice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Skills/Attack/Attack_Base.h"
#include "Skills/Attack_Effects/Bullet.h"

#include "Components/DecalComponent.h" 
#include "Classes/Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h" 
#include "TimerManager.h"

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
	int Ranged_Stability_X = 10;
	int Ranged_Stability_Y = 10;
	bool Is_Dodging = false;
	FVector Previous_Position;
	float Tick_Interval = 0.f;
	float Tick_To_Pass = 1.f;
	void Shoot_End();
	FTimerHandle TimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* Targeted_Circle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* Aiming_Circle;


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
	virtual bool Can_Aim();
	virtual void Shoot(FVector Location);
	AMyCharacter* Target_Of_Attack;
	virtual float Get_Health() const;
	virtual float Get_Max_HP() const;
	virtual int Get_Attack_Melee_Skill() const;
	virtual void Aim(FVector Location);
	virtual void End_Aim() const;
	virtual void Set_Mage_Projectile_Speed(float Vx, float Vy);

	int Get_Gun_Stability_Y() { return Ranged_Stability_Y; }
	int Get_Gun_Stability_X() { return Ranged_Stability_X; }


	UFUNCTION()
		void OnFire(FRotator Rotator);
	ABullet* OwnBullet = nullptr;

	bool Is_Being_Attacked = false;
	bool Is_Attacking = false;
	bool Turn_Done = false;
	bool Is_Turn = false;
	bool Move_Done = true;
	bool Is_Placed = false;
	bool Is_Alive = true;
	bool Is_Mage = true;

	int Iniciative;
	bool Is_Gunman = false;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool Is_Moving = false;
	
	float HP = 100;
	float Max_HP = 100;
	float Magic_Projectile_Speed_X = 0.0f;
	float Magic_Projectile_Speed_Y = 0.0f;
	virtual float Set_Bullet_Type(ABullet* Bullet);

	UFUNCTION()
	virtual void OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	int Skill_Strength;
	int Ranged_Skill_Aim;
	UPROPERTY()
	UStaticMesh* Mesh_Axe = nullptr;
	UPROPERTY()
	UStaticMesh* Mesh_Sword = nullptr;
	UStaticMesh* Get_Component(int type);
	
	UCapsuleComponent* Capsule = nullptr;
	
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
	void Move_My_Character(const FVector& position);
	int Weapon_Type;
	Attack_Base Attack_Primary;
	Attack_Base Attack_Secondary;

	void Change_Skill(int skill);

	// Called to bind functionality to input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABullet> ProjectileClass;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
		

};
	