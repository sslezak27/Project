// Fill out your copyright notice in the Description page of Project Settings.


#include "Attack_Base.h"

Attack_Base::Attack_Base()
{
}

Attack_Base::~Attack_Base()
{
}
Attack_Base::Attack_Base(float Dmg, float Range,float Fatigue, float Hit_Chance, int8 Type,float Stun, float Vx, float Vy, float grav)
{
	Attack_Dmg = Dmg;
	Attack_Range = Range;
	Base_Hit_Chance = Hit_Chance;
	Attack_Type = Type;
	Ranged_Vx = Vx;
	Ranged_Vy = Vy;
	gravity = grav;
	Attack_Fatigue = Fatigue;
	Stun_Chance = Stun;

}
float Attack_Base::Calculate_Attack_Yaw(const FVector& Starting_Location, const FVector& Target_Location)
{
	FVector Distance = -Starting_Location + Target_Location;
	float Distx = sqrt( (Distance.X) * (Distance.X) + (Distance.Y) * (Distance.Y));
	float time = Distx / Ranged_Vx;
	float DistanceY = Target_Location.Z - Starting_Location.Z;
	Ranged_Vy = DistanceY / time - gravity * time / 2.0f;
	return Ranged_Vy;
}

