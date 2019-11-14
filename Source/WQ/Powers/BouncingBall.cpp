// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncingBall.h"
#include "Math/UnrealMathUtility.h"
#include "StaticUtils.h"
#include "Enemies/WQAIEnemy.h"

#include "GameFramework/CharacterMovementComponent.h"

/** Sets default values */
ABouncingBall::ABouncingBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	bIsBallResizing = false;
	bIsBallTelekinesisd = false;
	TargetScale = FVector::OneVector;
	CurrentScalingStatus = 0.0f;
	CurrentScalingSpeed = 0.0f;
	Damage = 1;
}

/** Called when the game starts or when spawned */
void ABouncingBall::BeginPlay()
{
	Super::BeginPlay();

	// Get the ball mesh
	TArray<UStaticMeshComponent*> Temp;
	GetComponents<UStaticMeshComponent>(Temp);
	if (Temp.Num() > 0)
		BallMesh = Temp[0];

	// Add the collision notification and disable the notifications for now
	BallMesh->OnComponentHit.AddDynamic(this, &ABouncingBall::OnBallHit);
	BallMesh->SetNotifyRigidBodyCollision(false);
	
	// Activate all elements with zero scale, and disable physics
	SetBallActive(true);
	ResetBall();
}

/** Called every frame */
void ABouncingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsBallResizing)
	{
		CurrentScalingStatus = FMath::Min(1.0f, CurrentScalingStatus + DeltaTime * CurrentScalingSpeed);

		GetRootComponent()->SetWorldScale3D(FMath::Lerp<FVector>(InitialScale, TargetScale, CurrentScalingStatus));

		if (CurrentScalingStatus >= 1.0f)
		{
			CurrentCallback.ExecuteIfBound();
			bIsBallResizing = false;
			CurrentCallback.Unbind();
		}
	}
	else if (bIsBallTelekinesisd)
	{
		FVector Direction = TelekinesisTarget->GetComponentLocation() - GetRootComponent()->GetComponentLocation();

		// Stop if we are near enough the destination
		if (Direction.SizeSquared() < 1000.0f)
		{
			// Change needed parameters
			bIsBallTelekinesisd = false;
			SetPhysicSimulation(false);
			SetGravitySimulation(true);
			SetCollisionProfile(TEXT("BallHeld"));

			// Callback
			CurrentCallback.ExecuteIfBound();
			CurrentCallback.Unbind();
		}
		else
		{
			// Propulse the meshes towards the target
			GetRootComponent()->SetWorldLocation(FMath::VInterpTo(GetRootComponent()->GetComponentLocation(), TelekinesisTarget->GetComponentLocation(), DeltaTime, TelekinesisStrength));
		}
	}
}

/** Changes the scale of the ball elements in a given time */
void ABouncingBall::ChangeScale(FVector InitialScale, FVector FinalScale, float Duration, FSimpleCallback Callback)
{
	this->InitialScale = InitialScale;
	this->TargetScale = FinalScale;
	bIsBallResizing = true;

	CurrentScalingSpeed = 1 / Duration;

	// Takes the hypothesis that all dimensions will be scaled the same
	FVector CurrentScale = GetRootComponent()->GetComponentScale();
	CurrentScalingStatus = FMath::Abs((CurrentScale.X - InitialScale.X) / (TargetScale.X - InitialScale.X));

	// Update the new resizing callback
	CurrentCallback.Unbind();
	CurrentCallback = Callback;
}

/** Activate/deactivate the ball */
void ABouncingBall::SetBallActive(bool bState)
{
	if (BallMesh != nullptr)
	{
		BallMesh->SetActive(bState);
		BallMesh->SetHiddenInGame(!bState);
	}
}

/** Changes the simulation physics status */
void ABouncingBall::SetPhysicSimulation(bool bState)
{
	if (BallMesh != nullptr)
	{
		BallMesh->SetSimulatePhysics(bState);
		if (bState)
		{
			BallMesh->WakeAllRigidBodies();
		}
	}
}

/** Changes the gravity physics status */
void ABouncingBall::SetGravitySimulation(bool bState)
{
	if (BallMesh != nullptr)
	{
		BallMesh->SetEnableGravity(bState);
	}
}

/** Changes the collision profile */
void ABouncingBall::SetCollisionProfile(FName CollisionProfileName)
{
	if (BallMesh != nullptr)
	{
		BallMesh->SetCollisionProfileName(CollisionProfileName);
	}
}

/** Propulse the ball forward */
void ABouncingBall::Propulse(FVector Direction, float Strength)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (BallMesh != nullptr)
	{
		// Physics changes
		SetCollisionProfile(TEXT("Ball"));
		SetPhysicSimulation(true);
		//SetGravitySimulation(false);
		BallMesh->AddForce(UStaticUtils::GetSafeNormal(Direction) * Strength * BallMesh->GetMassScale(), NAME_None, true);

		// Activate the OnComponentHit call
		BallMesh->SetNotifyRigidBodyCollision(true);
	}
}

/** Get the ball back with telekinesis */
void ABouncingBall::GetBallBack(USceneComponent* TargetComponent, float Strength, FSimpleCallback Callback)
{
	// Deactivate the OnComponentHit call
	BallMesh->SetNotifyRigidBodyCollision(false);

	// Deactivate Physics & Gravity
	SetPhysicSimulation(false);
	SetGravitySimulation(false);

	// Set the elements of the telekinesis, the propulsion will take place in Tick
	bIsBallTelekinesisd = true;
	TelekinesisTarget = TargetComponent;
	TelekinesisStrength = Strength;

	// Update the new telekinesis callback
	CurrentCallback.Unbind();
	CurrentCallback = Callback;

	// Set the correct collision profile
	SetCollisionProfile(TEXT("BallTelekinesis"));
}

/** Reset the ball position and scale */
void ABouncingBall::ResetBall()
{
	GetRootComponent()->SetWorldScale3D(FVector::ZeroVector);
	SetPhysicSimulation(false);
	SetGravitySimulation(true);
	SetCollisionProfile(TEXT("BallHeld"));
}

/** Allows us to damage enemies when hit while the ball is thrown */
void ABouncingBall::OnBallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AWQAIEnemy* Enemy = Cast<AWQAIEnemy>(OtherActor);
	if (Enemy != nullptr)
	{
        Enemy->ApplyDamage( Damage );

        UCharacterMovementComponent* characterMovement = Enemy->GetCharacterMovement();
        characterMovement->AddImpulse( UStaticUtils::GetSafeNormal( NormalImpulse ) * 1000000.0f * BallMesh->GetMassScale() );
        /*
        characterMovement->Velocity = FVector::ZeroVector;
        characterMovement->UpdateComponentVelocity();*/
	}
}

