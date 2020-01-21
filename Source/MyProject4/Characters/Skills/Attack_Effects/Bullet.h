// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Bullet.generated.h"

UCLASS()
class MYPROJECT4_API ABullet : public AActor
{
	
	GENERATED_BODY()
private:

public:	
	// Sets default values for this actor's properties
	ABullet();
	/** inits velocity of the projectile in the shoot direction */
	void InitVelocity(const FVector& ShootDirection);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	float damage = 0.0f;
	virtual void Tick(float DeltaTime) override;
	void Init_Bullet(float speed);
	void Init_Fireball(float Speed);
	void Init_Rubber_Bullet(float speed);
	bool Can_Damage = true;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
