// Fill out your copyright notice in the Description page of Project Settings.


#include "PropsMovement.h"
#include "Props.h"
#include "StaticUtils.h"

// Sets default values
UPropsMovement::UPropsMovement(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxSpeed = 1200.f;
	Acceleration = 4000.f;
	Deceleration = 8000.f;
	TurningBoost = 8.0f;
	bPositionCorrected = false;

	bIsGravityEnabled = true;
	TerminalVelocity = 500.0f;
	Gravity = FVector(0, 0, -1);

	bShouldMoveAutomatically = false;

	SweepParams = FCollisionQueryParams();
	SweepParams.AddIgnoredActor(this->GetOwner()); // Ignore the character in the sweep

	ResetMoveState();
}

void UPropsMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Logic for moving automatically without a controller
	if (bShouldMoveAutomatically)
	{
		// Stop the movement if we are close enough
		if (FVector::DistSquared(UpdatedComponent->GetComponentLocation(), MoveTarget->GetComponentLocation()) <= AutomaticMovementStopRange * AutomaticMovementStopRange)
		{
			//UpdatedComponent->SetWorldLocation(MoveTarget->GetComponentLocation());
			bShouldMoveAutomatically = false;
			return;
		}

		Velocity = UStaticUtils::GetSafeNormal(MoveTarget->GetComponentLocation() - UpdatedComponent->GetComponentLocation()) * AutomaticMovementSpeed;

		//// Add gravity
		//if (bIsGravityEnabled)
		//{
		//	Velocity = ComputeFallVelocity(Velocity, DeltaTime);
		//}

		LimitWorldBounds();
		bPositionCorrected = false;

		// Move actor
		FVector Delta = Velocity * DeltaTime;

		if (!Delta.IsNearlyZero(1e-6f))
		{
			const FVector OldLocation = UpdatedComponent->GetComponentLocation();
			const FQuat Rotation = UpdatedComponent->GetComponentQuat();

			//FHitResult Hit(1.f);
			//// Update the raycast
			//UWorld* const World = GetWorld();
			//if (!World)
			//{
			//	UE_LOG(LogTemp, Error, TEXT("PropsMovement: World not found!"));
			//}
			//World->LineTraceSingleByChannel(Hit, OldLocation, OldLocation + Delta, ECollisionChannel::ECC_GameTraceChannel3, SweepParams);

			//if (Hit.IsValidBlockingHit())
			//{
			//	bShouldMoveAutomatically = false;
			//	return;
			//}
			//else
			//{
			//	UpdatedComponent->MoveComponent(Delta, Rotation, false, nullptr, EMoveComponentFlags::MOVECOMP_NoFlags, ETeleportType::ResetPhysics);
			//}

			FHitResult HitSafe(1.f);

			SafeMoveUpdatedComponent(Delta, Rotation, true, HitSafe);

			if (HitSafe.IsValidBlockingHit())
			{
				HandleImpact(HitSafe, DeltaTime, Delta);
				// Try to slide the remaining distance along the surface.
				SlideAlongSurface(Delta, 1.f - HitSafe.Time, HitSafe.Normal, HitSafe, true);
			}

			// Update velocity
			// We don't want position changes to vastly reverse our direction (which can happen due to penetration fixups etc)
			if (!bPositionCorrected)
			{
				const FVector NewLocation = UpdatedComponent->GetComponentLocation();
				Velocity = ((NewLocation - OldLocation) / DeltaTime);
			}
		}

		// Finalize
		UpdateComponentVelocity();
	}
	else
	{
		// Logic for controlled pawn
		if (!PawnOwner || !UpdatedComponent)
		{
			return;
		}

		const AController* Controller = PawnOwner->GetController();
		if (Controller && Controller->IsLocalController())
		{
			// apply input for local players but also for AI that's not following a navigation path at the moment
			if (Controller->IsLocalPlayerController() == true || Controller->IsFollowingAPath() == false || bUseAccelerationForPaths)
			{
				ApplyControlInputToVelocity(DeltaTime);
			}
			// if it's not player controller, but we do have a controller, then it's AI
			// (that's not following a path) and we need to limit the speed
			else if (IsExceedingMaxSpeed(MaxSpeed) == true)
			{
				Velocity = Velocity.GetUnsafeNormal() * MaxSpeed;
			}

			// Add gravity
			if (bIsGravityEnabled)
			{
				Velocity = ComputeFallVelocity(Velocity, DeltaTime);
			}

			LimitWorldBounds();
			bPositionCorrected = false;

			// Move actor
			FVector Delta = Velocity * DeltaTime;

			if (!Delta.IsNearlyZero(1e-6f))
			{
				const FVector OldLocation = UpdatedComponent->GetComponentLocation();
				const FQuat Rotation = UpdatedComponent->GetComponentQuat();

				FHitResult Hit(1.f);
				SafeMoveUpdatedComponent(Delta, Rotation, true, Hit);

				if (Hit.IsValidBlockingHit())
				{
					HandleImpact(Hit, DeltaTime, Delta);
					// Try to slide the remaining distance along the surface.
					SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit, true);
				}

				// Update velocity
				// We don't want position changes to vastly reverse our direction (which can happen due to penetration fixups etc)
				if (!bPositionCorrected)
				{
					const FVector NewLocation = UpdatedComponent->GetComponentLocation();
					Velocity = ((NewLocation - OldLocation) / DeltaTime);
				}
			}

			// Finalize
			UpdateComponentVelocity();
		}
	}
};


bool UPropsMovement::LimitWorldBounds()
{
	AWorldSettings* WorldSettings = PawnOwner ? PawnOwner->GetWorldSettings() : NULL;
	if (!WorldSettings || !WorldSettings->bEnableWorldBoundsChecks || !UpdatedComponent)
	{
		return false;
	}

	const FVector CurrentLocation = UpdatedComponent->GetComponentLocation();
	if (CurrentLocation.Z < WorldSettings->KillZ)
	{
		Velocity.Z = FMath::Min(GetMaxSpeed(), WorldSettings->KillZ - CurrentLocation.Z + 2.0f);
		return true;
	}

	return false;
}

void UPropsMovement::ApplyControlInputToVelocity(float DeltaTime)
{
	const FVector ControlAcceleration = GetPendingInputVector().GetClampedToMaxSize(1.f);

	const float AnalogInputModifier = (ControlAcceleration.SizeSquared() > 0.f ? ControlAcceleration.Size() : 0.f);
	const float MaxPawnSpeed = GetMaxSpeed() * AnalogInputModifier;
	const bool bExceedingMaxSpeed = IsExceedingMaxSpeed(MaxPawnSpeed);

	if (AnalogInputModifier > 0.f && !bExceedingMaxSpeed)
	{
		// Apply change in velocity direction
		if (Velocity.SizeSquared() > 0.f)
		{
			// Change direction faster than only using acceleration, but never increase velocity magnitude.
			const float TimeScale = FMath::Clamp(DeltaTime * TurningBoost, 0.f, 1.f);
			Velocity = Velocity + (ControlAcceleration * Velocity.Size() - Velocity) * TimeScale;
		}
	}
	else
	{
		// Dampen velocity magnitude based on deceleration.
		if (Velocity.SizeSquared() > 0.f)
		{
			const FVector OldVelocity = Velocity;
			const float VelSize = FMath::Max(Velocity.Size() - FMath::Abs(Deceleration) * DeltaTime, 0.f);
			Velocity = Velocity.GetSafeNormal() * VelSize;

			// Don't allow braking to lower us below max speed if we started above it.
			if (bExceedingMaxSpeed && Velocity.SizeSquared() < FMath::Square(MaxPawnSpeed))
			{
				Velocity = OldVelocity.GetSafeNormal() * MaxPawnSpeed;
			}
		}
	}

	// Apply acceleration and clamp velocity magnitude.
	const float NewMaxSpeed = (IsExceedingMaxSpeed(MaxPawnSpeed)) ? Velocity.Size() : MaxPawnSpeed;
	Velocity += ControlAcceleration * FMath::Abs(Acceleration) * DeltaTime;
	Velocity = Velocity.GetClampedToMaxSize(NewMaxSpeed);

	ConsumeInputVector();
}

bool UPropsMovement::ResolvePenetrationImpl(const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotationQuat)
{
	bPositionCorrected |= Super::ResolvePenetrationImpl(Adjustment, Hit, NewRotationQuat);
	return bPositionCorrected;
}


void UPropsMovement::SetGravity(bool bState)
{
	bIsGravityEnabled = bState;
}

FVector UPropsMovement::ComputeFallVelocity(const FVector& InitialVelocity, float DeltaTime) const
{
	FVector FallVelocity = InitialVelocity;

	if (DeltaTime > 0.0f)
	{
		// Apply gravity
		FallVelocity += Gravity * DeltaTime;

		// Clamp the velocity
		if (FallVelocity.SizeSquared() > FMath::Square(TerminalVelocity))
		{
			const FVector GravityDir = Gravity.GetSafeNormal();
			if ((FallVelocity | Gravity) > FMath::Abs(TerminalVelocity))
			{
				FallVelocity = FVector::PointPlaneProject(FallVelocity, FVector::ZeroVector, GravityDir) + GravityDir * TerminalVelocity;
			}
		}
	}

	return FallVelocity;
}

void UPropsMovement::MoveAutomaticallyTo(USceneComponent* Target, float Speed, float StopRange)
{
	bShouldMoveAutomatically = true;
	MoveTarget = Target;
	AutomaticMovementSpeed = Speed;
	AutomaticMovementStopRange = StopRange;
}

void UPropsMovement::StopAutomaticMovement()
{
	bShouldMoveAutomatically = false;
}

