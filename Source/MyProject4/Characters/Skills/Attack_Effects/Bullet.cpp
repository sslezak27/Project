// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	
	RootComponent = CollisionComp;
	CollisionComp->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;


}

void ABullet::InitVelocity(const FVector& ShootDirection)
{

	if (ProjectileMovement)
	{
		// set the projectile's velocity to the desired direction
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	}
}



// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::Init_Bullet(float speed)
{
	CollisionComp->InitSphereRadius(15.0f);
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->Bounciness = 0.3f;
	ProjectileMovement->ProjectileGravityScale = 0.4f;
	ProjectileMovement->Friction = 0.1f;
}

void ABullet::Init_Fireball(float Speed)
{
	CollisionComp->InitSphereRadius(15.0f);
	ProjectileMovement->InitialSpeed = Speed * 2000.f;
	ProjectileMovement->MaxSpeed = Speed* 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.1f;
	ProjectileMovement->ProjectileGravityScale = 1.0f;
	ProjectileMovement->Friction = 0.1f;
}

void ABullet::Init_Rubber_Bullet(float speed)
{
	CollisionComp->InitSphereRadius(15.0f);
	ProjectileMovement->InitialSpeed = speed * 1000.f;
	ProjectileMovement->MaxSpeed = speed* 1000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.5f;
	ProjectileMovement->ProjectileGravityScale = 1.0f;
	ProjectileMovement->Friction = 0.1f;
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(ProjectileMovement->Velocity.Z));
	if (abs(ProjectileMovement->Velocity.Z) <= 50 && Can_Damage)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(ProjectileMovement->Velocity.Z));
		Can_Damage = false;
	}
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{	
		OtherComponent->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);
	}

}
