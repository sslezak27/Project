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
	int Turn_Done[7] = {};
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Begin_Combat();
	int Iniciative[7] = {};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
