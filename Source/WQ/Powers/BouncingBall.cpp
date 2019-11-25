// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncingBall.h"
#include "Math/UnrealMathUtility.h"
#include "StaticUtils.h"
#include "Enemies/WQAIEnemy.h"
#include "NiagaraComponent.h" 
#include "Components/SphereComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"

/** Sets default values */
ABouncingBall::ABouncingBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	TargetScale = FVector::OneVector;
	Damage = 1;

    isCacac = false;

    SlowmoEnabled = true;
    IsInSlowDown = false;
    SlowmoDuration = 1.0f;
    SlowmoDelay = 0.3f;
    SlowmoLeverage = 0.1f;
}

/** Called when the game starts or when spawned */
void ABouncingBall::BeginPlay()
{
	Super::BeginPlay();

	// Set the initial state
	State = EBoucingBallEnum::BBE_General;

	// Get the ball collider & the Niagara component
	TArray<USphereComponent*> Temp;
	GetComponents<USphereComponent>(Temp);
	if (Temp.Num() > 0)
	{
		BallCollider = Temp[0];
	}
	TArray<UNiagaraComponent*> TempNiagara;
	GetComponents<UNiagaraComponent>(TempNiagara);
	if (TempNiagara.Num() > 0)
	{
		BallNiagara = TempNiagara[0];
	}

	// Add the end of Niagara animation notification
	BallNiagara->OnSystemFinished.AddDynamic(this, &ABouncingBall::OnBallComplete);

	// Add the collision notification and disable the notifications for now
	BallCollider->OnComponentHit.AddDynamic(this, &ABouncingBall::OnBallHit);
	BallCollider->SetNotifyRigidBodyCollision(false);
	
	// Activate all elements with zero scale, and disable physics
	SetBallActive(true);
	ResetBall();
}

/** Called every frame */
void ABouncingBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (State == EBoucingBallEnum::BBE_Telekinesis)
	{
		FVector Direction = TelekinesisTarget->GetComponentLocation() - GetRootComponent()->GetComponentLocation();

		// Stop if we are near enough the destination
		if (Direction.SizeSquared() < 100.0f)
		{
			// Change needed parameters
			State = EBoucingBallEnum::BBE_General;
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
void ABouncingBall::ChangeScale(FSimpleCallback Callback)
{
	State = EBoucingBallEnum::BBE_Charging;

	// Launch the animation
	BallNiagara->SetPaused(false);

	// Update the new resizing callback
	CurrentCallback.Unbind();
	CurrentCallback = Callback;
}

/** Activate/deactivate the ball */
void ABouncingBall::SetBallActive(bool bState)
{
	if (IsValid(BallNiagara))
	{
		BallNiagara->SetActive(bState);
		BallNiagara->SetHiddenInGame(!bState);
	}

	if (IsValid(BallCollider))
	{
		BallCollider->SetActive(bState);
	}
}

/** Changes the simulation physics status */
void ABouncingBall::SetPhysicSimulation(bool bState)
{
	if (IsValid(BallCollider))
	{
		BallCollider->SetSimulatePhysics(bState);
		if (bState)
		{
			BallCollider->WakeAllRigidBodies();
		}
	}
}

/** Changes the gravity physics status */
void ABouncingBall::SetGravitySimulation(bool bState)
{
	if (IsValid(BallCollider))
	{
		BallCollider->SetEnableGravity(bState);
	}
}

/** Changes the collision profile */
void ABouncingBall::SetCollisionProfile(FName CollisionProfileName)
{
	if (IsValid(BallCollider))
	{
		BallCollider->SetCollisionProfileName(CollisionProfileName);
	}
}

/** Propulse the ball forward */
void ABouncingBall::Propulse(FVector Direction, float Strength)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	if (IsValid(BallCollider))
	{
		// Physics changes
		SetCollisionProfile(TEXT("Ball"));
		SetPhysicSimulation(true);
		//SetGravitySimulation(false);
		BallCollider->AddForce(UStaticUtils::GetSafeNormal(Direction) * Strength * BallCollider->GetMassScale(), NAME_None, true);

		// Activate the OnComponentHit call
		BallCollider->SetNotifyRigidBodyCollision(true);
	}
}

/** Get the ball back with telekinesis */
void ABouncingBall::GetBallBack(USceneComponent* TargetComponent, float Strength, FSimpleCallback Callback)
{
	// Deactivate the OnComponentHit call
	BallCollider->SetNotifyRigidBodyCollision(false);

	// Deactivate Physics & Gravity
	SetPhysicSimulation(false);
	SetGravitySimulation(false);

	// Set the elements of the telekinesis, the propulsion will take place in Tick
	State = EBoucingBallEnum::BBE_Telekinesis;
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
	BallNiagara->ResetSystem();
	BallNiagara->SetPaused(true);
	//GetRootComponent()->SetWorldScale3D(FVector::ZeroVector);
	SetPhysicSimulation(false);
	SetGravitySimulation(true);
	SetCollisionProfile(TEXT("BallHeld"));
}

/** Allows us to damage enemies when hit while the ball is thrown */
void ABouncingBall::OnBallHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AWQAIEnemy* Enemy = Cast<AWQAIEnemy>(OtherActor);
	if (Enemy != nullptr && !isCacac)
	{
        //BallMesh->SetNotifyRigidBodyCollision( false );

        Enemy->ApplyDamage( Damage );

        UCharacterMovementComponent* characterMovement = Enemy->GetCharacterMovement();
        characterMovement->AddImpulse( UStaticUtils::GetSafeNormal( NormalImpulse ) * 1000000.0f * BallCollider->GetMassScale() );

        FTimerDelegate TimerDel;
        TimerDel.BindUFunction( this, FName( "TriggerSlowdown" ), Enemy );

        isCacac = true;

        if ( SlowmoEnabled ) {
            velocityBackup = BallCollider->GetPhysicsLinearVelocity();
            
            UE_LOG( LogTemp, Error, TEXT( "%f %f %f" ), velocityBackup.X, velocityBackup.Y, velocityBackup.Z );

            SetPhysicSimulation( false );
            SetPhysicSimulation( true );

            SetGravitySimulation( false );
            BallCollider->SetPhysicsLinearVelocity( velocityBackup * 0.0000001f );

            GetWorld()->GetTimerManager().SetTimer( SlowDownTriggerTimerHandle, TimerDel, SlowmoDelay, false );
        }
	}
}

/** Allows us to call the callback when the Niagara animation is finished playing */
void ABouncingBall::OnBallComplete(UNiagaraComponent* NiagaraComponent)
{
	BallNiagara->SetPaused(true);
	State = EBoucingBallEnum::BBE_General;
	CurrentCallback.ExecuteIfBound();
	CurrentCallback.Unbind();
}

void ABouncingBall::TriggerSlowdown( AWQAIEnemy* touchedActor )
{
    // Apply bullet time thingy
    if ( IsInSlowDown ) {
        touchedActor->SetTimeDilation( 1.0f );

        BallCollider->SetPhysicsLinearVelocity( velocityBackup );
        SetGravitySimulation( true );

        isCacac = false;
    } else {
        touchedActor->SetTimeDilation( SlowmoLeverage );
        
        FTimerDelegate TimerDel;
        TimerDel.BindUFunction( this, FName( "TriggerSlowdown" ), touchedActor );
        GetWorld()->GetTimerManager().SetTimer( SlowDownTriggerTimerHandle, TimerDel, SlowmoDuration, false );
    }

    IsInSlowDown = !IsInSlowDown;
}
