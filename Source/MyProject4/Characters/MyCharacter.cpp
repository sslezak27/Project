// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Controllers/AI_Controller.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Targeted_Circle = CreateDefaultSubobject<UDecalComponent>("Targeted_Circle");
	Targeted_Circle->SetupAttachment(RootComponent);
	Aiming_Circle = CreateDefaultSubobject<UDecalComponent>("Aiming_Ciricle");
	Aiming_Circle->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Characters/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		Targeted_Circle->SetDecalMaterial(DecalMaterialAsset.Object); 
		Aiming_Circle->SetDecalMaterial(DecalMaterialAsset.Object);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "SUCCES");

	}

	Aiming_Circle->DecalSize = FVector(1, 1, 1);
	Aiming_Circle->SetWorldScale3D(FVector(0, 0, 0));
	Targeted_Circle->DecalSize = FVector(1, 1, 1);
	Targeted_Circle->SetWorldScale3D(FVector(0, 0, 0));

	Aiming_Circle->SetWorldRotation(FRotator(180,180, 180));
	Attack_Melee_Skill = FMath::FRandRange(1, 100);
	Defence_Melee_Skill = FMath::FRandRange(1, 100);
	Ranged_Skill_Aim = FMath::FRandRange(1, 100);
	Skill_Strength = FMath::FRandRange(1, 100);
	Weapon_Type = FMath::FRandRange(0, 6) - 0.001;
	Capsule = GetCapsuleComponent();
	Ranged_Stability_X = FMath::FRandRange(1, 100);
	Ranged_Stability_Y = FMath::FRandRange(1, 100);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Swordasset(TEXT("StaticMesh'/Game/CloseCombat/Weapon/Swords/FuturisticSword/Meshes/SM_FuturisticSword.SM_FuturisticSword'"));
	if (Swordasset.Succeeded())
	{
		if (UStaticMesh* cast_Mesh = Cast<UStaticMesh>(Swordasset.Object))
			Mesh_Sword = cast_Mesh;
		else
			Mesh_Sword = nullptr;

	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Axeasset(TEXT("StaticMesh'/Game/CloseCombat/Weapon/Swords/SwordOfDarkness/Meshes/SM_SwordOfDarkness.SM_SwordOfDarkness'"));
	if (Axeasset.Succeeded())
	{
		Mesh_Axe = Axeasset.Object;

	}

	//PrimaryActorTick.bStartWithTickEnabled = true;



}



int AMyCharacter::Roll_Iniciative()
{
	Iniciative = 1;
	return 1;
}
bool AMyCharacter::Do_Turn(FVector Move_Location)
{	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Turn Started");
	//if(Is_Placed)
	Move_My_Character(GetActorLocation() - FVector(FMath::FRandRange(-150, 150), FMath::FRandRange(-150,150), 0));
	return true;
}

void AMyCharacter::Move_End()
{
	Is_Moving = false;

	Turn_End();
}

void AMyCharacter::Turn_End()
{
	if (!Is_Placed)
	{
		Is_Placed = true;
	}
	Is_Attacking = false;
	Turn_Done = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Turn Ended");
}
// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Capsule->OnComponentHit.AddDynamic(this, &AMyCharacter::OnCapsuleHit);
	Capsule->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);
	//Move_My_Character(FVector(500, -120, 108));
	
}

float AMyCharacter::Set_Bullet_Type(ABullet* Bullet)
{
	switch (Current_Skill.Ranged_Type)
	{
	case 0:
		Bullet->Init_Bullet(Current_Skill.Ranged_Speed);
		return Magic_Projectile_Speed_Y;
	case 1:
		Bullet->Init_Rubber_Bullet(Current_Skill.Ranged_Speed);
		return Magic_Projectile_Speed_Y;
	case 2:
		Bullet->Init_Fireball(Magic_Projectile_Speed_X);
		return Magic_Projectile_Speed_Y;
	default:
		Bullet->Init_Bullet(Current_Skill.Ranged_Speed);
		return Magic_Projectile_Speed_Y;
	}

}

void AMyCharacter::OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "IS BEING SHOT AT");

	ABullet* Other_Bullet = Cast<ABullet>(OtherActor);
	if (Is_Alive && Other_Bullet != nullptr && Other_Bullet != OwnBullet)
	{
		//Is_Being_Attacked = true;
		if (Other_Bullet->Can_Damage)
		{
			HP -= Other_Bullet->damage;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(HP));
			if (HP <= 0)
			{

				DIE();
				if (OtherComponent->IsSimulatingPhysics())
				{
					Capsule->AddImpulseAtLocation(Other_Bullet->ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);
				}
			}
		}
	}
}

void AMyCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "IS BEING OVERLAPPED AT");

	ABullet* Other_Bullet = Cast<ABullet>(OtherActor);
	if(Other_Bullet  != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "IS BULLET OVERLAPPED");
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "NO BULLET OVLAP");
	if (Is_Alive && Other_Bullet != nullptr)
	{
		//Is_Being_Attacked = true;
		if (Other_Bullet->Can_Damage)
		{
			HP -= Other_Bullet->damage;
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(HP));
			if (HP <= 0)
			{

				DIE();

				//Capsule->AddImpulseAtLocation(Other_Bullet->ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);
			}
		}

	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Is_Moving)
	{
		Tick_Interval += DeltaTime;
		if (Tick_Interval >= Tick_To_Pass)
		{
			Tick_Interval = 0.f;
			if ((Previous_Position - GetActorLocation()).Size() <= 5)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "ENDED");
				Move_End();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "NOT YET");
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt((Previous_Position - GetActorLocation()).Size()));
				Previous_Position = GetActorLocation();
			}
		}
	}


}

void AMyCharacter::Change_Skill(int skill)
{
	switch(skill)
	{
	case 0:
		Current_Skill = Attack_Primary;
		break;
	case 1:
		Current_Skill = Attack_Secondary;
		break;
	default:
		Current_Skill = Attack_Primary;
		break;
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::Move_My_Character(const FVector& position)
{
	UNavigationPath* path = UNavigationSystemV1::FindPathToLocationSynchronously(this, this->GetActorLocation(), position);

	/**if (path && path->IsValid())
	{
		FAIMoveRequest req;
		req.SetAcceptanceRadius(50);
		req.SetUsePathfinding(true);
		**/
		AAI_Controller* ai = Cast<AAI_Controller>(this->GetController());
		if (ai)
		{
			Is_Moving = true;
			//ai->RequestMove(req, path->GetPath());
			ai->MoveToLocation(position,0.5f,false,true,true,true,0,true);
		}
	//}
}

bool AMyCharacter::Attack_Target(AMyCharacter* Target)
{
	Is_Attacking = true;
	Target_Of_Attack = Target;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "MY_CHARACTER_ATTACK_CALLED");
	if (Calculate_Attack_Succes(Target))
		Target->Be_Attacked(&Current_Skill);
	else
		Target->Set_Dodge(true);
	return true;
}

bool AMyCharacter::Calculate_Attack_Succes(AMyCharacter* Target)
{
	float Chance_To_Hit = Current_Skill.Base_Hit_Chance * Attack_Melee_Skill / Target->Get_Defence_Melee_Skill();
	if (FMath::FRandRange(1, 100) <= Chance_To_Hit)
	{
		return true;
	}
	else
		return false;
}

void AMyCharacter::Be_Attacked(Attack_Base* Skill)
{
	if (Is_Alive)
	{
		Is_Being_Attacked = true;
		HP -= Skill->Attack_Dmg;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(HP));
		if (HP <= 0)
		{
			Set_Dodge(false);
			DIE();
		}
	}
}

Attack_Base* AMyCharacter::Get_Skill()
{
	return &Current_Skill;
}

void AMyCharacter::Be_Targeted()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "YOUCALLED");
	Targeted_Circle-> SetWorldScale3D(FVector(100, 100, 100));
}

void AMyCharacter::DIE()
{
	Capsule->SetSimulatePhysics(true);
	Is_Alive = false;
}

void AMyCharacter::Shoot_End()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	Turn_End();
}

void AMyCharacter::Reset_Targeted()
{
	Targeted_Circle->SetWorldScale3D(FVector(0, 0, 0));
}


bool AMyCharacter::Get_Is_Attacking() const
{
	return Is_Attacking;
}

void AMyCharacter::End_Attack()
{
	Turn_End();
}

AMyCharacter* AMyCharacter::Get_Target() const
{
	return Target_Of_Attack;
}

bool AMyCharacter::Get_Is_Being_Attacked() const
{
	return Is_Being_Attacked;
}

int AMyCharacter::Get_Defence_Melee_Skill() const
{
	return Defence_Melee_Skill;
}

bool AMyCharacter::Get_Is_Dodging() const
{
	return Is_Dodging;
}

void AMyCharacter::Set_Dodge(bool Dodge)
{
	Is_Dodging = Dodge;
	Is_Being_Attacked = false;
}

bool AMyCharacter::Get_Is_Alive() const
{
	return Is_Alive;
}

float AMyCharacter::Get_Health() const
{
	return HP;
}
float AMyCharacter::Get_Max_HP() const
{
	return Max_HP;
}

int AMyCharacter::Get_Attack_Melee_Skill() const
{
	return Attack_Melee_Skill;
}

void AMyCharacter::Aim(FVector Location)
{
	FRotator Current_Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);
	FaceRotation(Current_Rotator);
	Aiming_Circle->SetWorldLocation(Location);
}

void AMyCharacter::End_Aim() const
{
	Aiming_Circle->SetWorldScale3D(FVector(0, 0, 0));
}

void AMyCharacter::Set_Mage_Projectile_Speed(float Vx, float Vy)
{
	Magic_Projectile_Speed_X = Vx;
	Magic_Projectile_Speed_Y = Vy;
}

void AMyCharacter::OnFire(FRotator Rotator)
{
	if (ProjectileClass != NULL)
	{
		// Get the camera transform
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		//CameraLoc = GetActorLocation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the camera to find the final muzzle position
		FVector const MuzzleLocation = CameraLoc + FTransform(Rotator).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = Rotator;
		MuzzleRotation.Pitch += 10.0f;          // skew the aim upwards a bit
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// spawn the projectile at the muzzle
			OwnBullet = World->SpawnActor<ABullet>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (OwnBullet)
			{
				
				// find launch direction
				OwnBullet->damage = Current_Skill.Attack_Dmg;
				MuzzleRotation.Pitch += MuzzleRotation.Pitch + Set_Bullet_Type(OwnBullet) + FMath::FRandRange(-100, 100) / Ranged_Stability_Y;
				//MuzzleRotation.Yaw += MuzzleRotation.Yaw + FMath::FRandRange(-100, 100) / Ranged_Stability_Y;
				FVector const LaunchDir = MuzzleRotation.Vector();
				OwnBullet->InitVelocity(LaunchDir);
			}
		}
	}
}


UStaticMesh* AMyCharacter::Get_Component(int type)
{
	switch (type)
	{
	case 0:
		return Mesh_Axe;
		break;
	case 1:
		//	if (Sword != nullptr)
		//if (UStaticMesh* Mesh = Cast<UStaticMesh>(Sword))
			return Mesh_Sword;
		//else
			//return nullptr;
		//	else
				//return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
}

bool AMyCharacter::Can_Aim()
{
	if (Current_Skill.Attack_Type == 1)
	{
		Aiming_Circle->SetWorldScale3D(FVector(1000,1000, 1000));
		return true;
	}
	else
		return false;
}

void AMyCharacter::Shoot(FVector Location)
{
	Aiming_Circle->SetWorldScale3D(FVector(0, 0, 0));
	FRotator Current_Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);

	//Current_Rotator.Yaw =
	FaceRotation(Current_Rotator);
	OnFire(Current_Rotator);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyCharacter::Shoot_End, 0.5f, true, -1.f);

}
