// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Game_Manager.generated.h"

UCLASS()
class MYPROJECT4_API AGame_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGame_Manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Begin_Combat();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
