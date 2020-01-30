// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MYPROJECT4_API Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();
	FVector Calculate_Path(int &Action_points,const FVector &Starting_Location, FVector &Move_Location,double const Yaw);
	double Calculate_Absolute_Yaw(const FVector& Starting_Location, const FVector& Move_Location) const;
	float const Distance_Const = 20.0;
	bool Is_Move_Valid(int& Action_points, const FVector& Starting_Location, FVector& Move_Location);
	bool Is_Valid_Attack_Target(float Attack_Range, const FVector& Starting_Location, FVector& Move_Location);
private:
	FVector Calculate_Destination_Vector(int const ratio, const FVector& Location, double const Yaw); 
	float Scale_Norm(const FVector2D& Move_Location);
		FVector Norm_Vector(const FVector& Move_Location);
		FVector Calculate_Vector(FVector Move_Location, float Scale);
};
