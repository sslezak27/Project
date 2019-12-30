// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"

UCLASS()
class MYPROJECT4_API AArrow : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArrow();
	AArrow(float SpeedY, float Speedx,FRotator rotacja);
	FHitResult* Colizja;
	void Setup_Component(float SpeedY, float Speedx, FRotator rotacja);

private:
	bool Alive = true;
	float Vx = 0;
	float Vy = 0;
	float gravity = 10;
	UStaticMeshComponent* Arrow = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
