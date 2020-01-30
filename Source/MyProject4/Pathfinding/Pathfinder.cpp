// Fill out your copyright notice in the Description page of Project Settings.


#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

FVector Pathfinder::Calculate_Path(int& Action_points,const FVector &Starting_Location,FVector &Move_Location, double const Yaw)
{
	float Distance = FVector::Dist(Starting_Location, Move_Location);
	int Action_Cost = FMath::FloorToInt(Distance / Distance_Const);
	if (Action_Cost <= Action_points)
	{
			Action_points -= Action_Cost;
			return Move_Location;
	}
	else
	{
		Distance = Distance_Const * Action_points;
		Action_points = 0;
		//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(Action_points));
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::FromInt(Action_Cost));
		//	FVector Dzeil_Move_Locaton = FVector(Move_Location.X - Starting_Location.X, Move_Location.Y - Starting_Location.Y,Move_Location.Z);
			FVector Dzeil_Move_Locaton = FVector(Move_Location.X-Starting_Location.X, Move_Location.Y-Starting_Location.Y, Move_Location.Z);
			//FVector Temp_Move_Location = Calculate_Destination_Vector((Action_points / (double)Action_Cost), Move_Location, Yaw);
			FVector Temp_Move_Location = Calculate_Vector(Norm_Vector(Dzeil_Move_Locaton),Distance) + Starting_Location ;
		/*	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (*FString::Printf(TEXT("(%f, %f \"%f\")\n"), Starting_Location.X, Starting_Location.Y, Starting_Location.Z)));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (*FString::Printf(TEXT("(%f, %f \"%f\")\n"), Move_Location.X, Move_Location.Y, Move_Location.Z )));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (*FString::Printf(TEXT("(%f, %f \"%f\")\n"), Temp_Move_Location.X, Temp_Move_Location.Y, Temp_Move_Location.Z)));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (FString::FromInt(Distance)));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (FString::FromInt(Temp_Move_Location.X)));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (FString::SanitizeFloat(Yaw)));*/


			return Temp_Move_Location;
	}
}

double Pathfinder::Calculate_Absolute_Yaw(const FVector& Starting_Location, const FVector& Move_Location) const
{
	float Vector_Size = (Move_Location - Starting_Location).Size();
	//double X = (Move_Location - Starting_Location).X;
	float Y = (Move_Location - Starting_Location).Y;


	return asin(Y/Vector_Size);
}

bool Pathfinder::Is_Move_Valid(int& Action_points, const FVector& Starting_Location, FVector& Move_Location)
{
	float Distance = FVector::Dist(Starting_Location, Move_Location);
	if (Distance > Distance_Const)
	{
		return true;
	}
	return false;
}

bool Pathfinder::Is_Valid_Attack_Target(float Attack_Range, const FVector& Starting_Location, FVector& Move_Location)
{

	if ((Starting_Location - Move_Location).Size() <= Attack_Range)
	{
		return true;
	}
	else
	return false;
}

FVector Pathfinder::Calculate_Destination_Vector(int const ratio, const FVector& Location, double const Yaw)
{
	float Vector_Size = Location.Size() * ratio;
	float Y = Vector_Size * sin(Yaw);
	float X = Vector_Size * cos(Yaw);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (FString::SanitizeFloat(Yaw)));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (FString::SanitizeFloat(Y)));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (FString::SanitizeFloat(X)));


	return FVector(X,Y,Location.Z);
}

float Pathfinder::Scale_Norm(const FVector2D& Move_Location)
{
	float Length;
	if ((Length = Move_Location.Size()) > 0)
		return Length;
	else
		return 0.0f;
}

FVector Pathfinder::Norm_Vector(const FVector& Move_Location)
{
	float Scale= Scale_Norm(FVector2D(Move_Location.X,Move_Location.Y));
	if (Scale != 0.0f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, (FString::SanitizeFloat(Move_Location.Z)));
		return FVector(Move_Location.X/Scale,Move_Location.Y/Scale,Move_Location.Z);
		//return FVector(Move_Location.X, Move_Location.Y, Move_Location.Z);
	}

	else
		return Move_Location;
}

FVector Pathfinder::Calculate_Vector(FVector Move_Location,float Scale)
{
	return FVector(Move_Location.X * Scale, Move_Location.Y * Scale, Move_Location.Z);
}