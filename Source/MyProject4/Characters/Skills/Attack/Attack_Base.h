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

	Attack_Base(float Dmg, float Range, float Hit_Chance, float Fatigue, int8 Type,float Stun = 0,int8 RangedType = 0);

	float Attack_Dmg = 50;
	float Attack_Range = 1000; //Pathfinder const
	float Base_Hit_Chance = 50;
	int8 Attack_Type = 0;   // TYPY ATAKÓW!!!!! 0- meele, 1-ranged
	int8 Ranged_Type = 0; // TYPY POCISKÓW 0-Pocisk, 1- gumowy pocisk 2- kula ognia
	float Ranged_Vx = 10;
	float Ranged_Vy = 0;
	float gravity = 10;
	float Attack_Fatigue = 0;
	float Ranged_Speed = 0;


	float Calculate_Attack_Yaw(const FVector& Starting_Location, const FVector& Target_Location);

private:



};
