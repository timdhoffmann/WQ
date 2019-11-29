// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticUtils.h"
#include "Math/UnrealMathUtility.h"

UStaticUtils::UStaticUtils(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

/** Get a correct safe normal, even in the UE4 editor */
FVector UStaticUtils::GetSafeNormal(FVector Vec, float Tolerance /* = 1.e-8f */)
{
	const float SquareSum = Vec.X * Vec.X + Vec.Y * Vec.Y + Vec.Z * Vec.Z;
	if (SquareSum == 1.f)
	{
		return Vec;
	}
	else if (SquareSum < Tolerance)
	{
		return FVector::ZeroVector;
	}
	const float Scale = 1 / FMath::Sqrt(SquareSum);
	Vec.X *= Scale;
	Vec.Y *= Scale;
	Vec.Z *= Scale;
	return Vec;
}
