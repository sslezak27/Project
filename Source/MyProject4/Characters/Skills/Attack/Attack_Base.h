// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MYPROJECT4_API Attack_Base
{
public:
	Attack_Base();
	~Attack_Base();

	float Attack_Dmg = 50;
	float const Attack_Range = 1000; //Pathfinder const
	float Base_Hit_Chance = 50;

};
