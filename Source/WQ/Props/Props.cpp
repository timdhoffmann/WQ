// Fill out your copyright notice in the Description page of Project Settings.


#include "Props.h"
#include "Components/MeshComponent.h"
#include "PropsMovement.h"
#include "WQCharacter.h"
#include "StaticUtils.h"
#include "Materials/MaterialInstanceDynamic.h"

/** Sets default values */
AProps::AProps()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default values
	bIsGlowing = false;
	GlowElapsed = 0.0f;
	GlowSpeed = 0.0f;
	TargetGlowMultiplier = 0.0f;

	// Create the movement component
	PropsMovementComponent = CreateDefaultSubobject<UPropsMovement>(TEXT("PropsMovementComponent"));
}

/** Called when the game starts or when spawned */
void AProps::BeginPlay()
{
	Super::BeginPlay();

	// Get the prop mesh
	TArray<UStaticMeshComponent*> Temp;
	GetComponents<UStaticMeshComponent>(Temp);
	if (Temp.Num() > 0)
	{
		Mesh = Temp[0];
	}

	SetPhysicSimulation(true);

	// Initialize the dynamic material instance
	if (IsValid(Mesh))
	{
		UMaterialInterface* Mat = Mesh->GetMaterial(0);
		MatInstanceDynamic = Mesh->CreateDynamicMaterialInstance(0, Mat);
		if (!IsValid(MatInstanceDynamic))
		{
			UE_LOG(LogTemp, Error, TEXT("Props: MatInstanceDynamic not initialized!"));
		}
	}

	// Get the initial emissive color
	FMaterialParameterInfo EmissiveColorParams;
	EmissiveColorParams.Name = "EmissiveColor";
	MatInstanceDynamic->GetVectorParameterValue(EmissiveColorParams, InitialEmissiveColor);
}

/** Called every frame */
void AProps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsGlowing)
	{
		GlowElapsed += DeltaTime * GlowSpeed;
		FLinearColor CurrentEmissiveColor;
		float CurrentMultiplier;
		if (GlowElapsed <= 0.5f)
		{
			float Status = FMath::Min(1.0f, (GlowElapsed) * 4.0f);
			CurrentEmissiveColor = FLinearColor::LerpUsingHSV(InitialEmissiveColor, TargetEmissiveColor, Status);
			CurrentMultiplier = FMath::Lerp(InitialGlowMultiplier, TargetGlowMultiplier, Status);
		}
		else
		{
			float Status = FMath::Min(1.0f, (GlowElapsed - 0.5f) * 4.0f);
			CurrentEmissiveColor = FLinearColor::LerpUsingHSV(TargetEmissiveColor, InitialEmissiveColor, Status);
			CurrentMultiplier = FMath::Lerp(TargetGlowMultiplier, InitialGlowMultiplier, Status);
		}
		MatInstanceDynamic->SetVectorParameterValue("EmissiveColor", CurrentEmissiveColor);
		MatInstanceDynamic->SetScalarParameterValue("EmissiveMultiplier", CurrentMultiplier);
		if (GlowElapsed >= 1.f)
		{
			bIsGlowing = false;
		}
	}

	if (bIsAssemblingGolem)
	{
		FVector Direction = GolemAssemblyTarget->GetSocketLocation(GolemAssemblySocket) - GetRootComponent()->GetComponentLocation();

		// Stop if we are near enough the destination
		if (Direction.SizeSquared() < 10.0f)
		{
			// Change needed parameters
			bIsAssemblingGolem = false;
			AttachToComponent(GolemAssemblyTarget, FAttachmentTransformRules::KeepWorldTransform, GolemAssemblySocket);
		}
		else
		{
			// Propulse the meshes towards the target
			GetRootComponent()->SetWorldLocation(FMath::VInterpTo(GetRootComponent()->GetComponentLocation(), GolemAssemblyTarget->GetSocketLocation(GolemAssemblySocket), DeltaTime, GolemAssemblySpeed));
		}
	}
}

/** Called to bind functionality to input */
void AProps::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/** Changes the simulation physics status */
void AProps::SetPhysicSimulation(bool bState)
{
	if (IsValid(Mesh))
	{
		Mesh->SetSimulatePhysics(bState);
		if (bState)
		{
			Mesh->WakeAllRigidBodies();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Props: MESH NOT DEFINED!"));
	}
}

/** Changes the gravity physics status */
void AProps::SetGravitySimulation(bool bState)
{
	if (IsValid(Mesh))
	{
		Mesh->SetEnableGravity(bState);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Props: MESH NOT DEFINED!"));
	}
}

/** Remove physical sims, move the prop towards a target */
void AProps::FlyTowards(FVector Target, float Speed)
{
	//SetPhysicSimulation(false);
	//GetRootComponent()->AttachToComponent(NewParent, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	//PropsMovementComponent->MoveAutomaticallyTo(NewParent, Speed, MagnetizationRadius);
	SetGravitySimulation(false);
	Mesh->AddForce(UStaticUtils::GetSafeNormal(Target - GetRootComponent()->GetComponentLocation()) * Speed, NAME_None, true);
	Mesh->SetCollisionProfileName(TEXT("PropsHeld"));
}

/** Stop the flying */
void AProps::FlyStop()
{
	//DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	//SetPhysicSimulation(true);
	//PropsMovementComponent->StopAutomaticMovement();
	Mesh->SetCollisionProfileName(TEXT("Props"));
	SetGravitySimulation(true);
}

/** Propulse physically */
void AProps::Propulse(FVector Direction, float Strength)
{
	Mesh->AddForce(Direction * Strength * Mesh->GetMassScale(), NAME_None, true);
}

/** Set the material glowing, Duration of 0.0f means infinite, Color of black means the InitialEmissiveColor */
void AProps::SetGlow(float Multiplier, float Duration, FLinearColor Color, bool bShouldRandPropulse)
{
	if (Duration == 0.0f)
	{
		bIsGlowing = false;
		MatInstanceDynamic->SetScalarParameterValue("EmissiveMultiplier", Multiplier);
		TargetEmissiveColor = Color == FLinearColor::Black ? InitialEmissiveColor : Color;
		MatInstanceDynamic->SetVectorParameterValue("EmissiveColor", TargetEmissiveColor);
	}
	else
	{
		// Set the glow targets and needed values
		GlowElapsed = 0.0f;
		GlowSpeed = 1 / Duration;
		TargetGlowMultiplier = Multiplier;
		TargetEmissiveColor = Color == FLinearColor::Black ? InitialEmissiveColor : Color;

		// Get the initial glow multiplier value if we are not in the middle of another glow
		if (!bIsGlowing) // Not already launched
		{
			bIsGlowing = true;
			FMaterialParameterInfo EmissiveMultiplierParams;
			EmissiveMultiplierParams.Name = "EmissiveMultiplier";
			MatInstanceDynamic->GetScalarParameterValue(EmissiveMultiplierParams, InitialGlowMultiplier);
		}
	}

	// Add a random force for more visual feedback
	if (bShouldRandPropulse && IsValid(Mesh))
	{
		Mesh->AddForce(FVector(FMath::RandRange(0.0f, 40000.0f), FMath::RandRange(0.0f, 40000.0f), FMath::RandRange(0.0f, 40000.0f)), NAME_None, true);
	}
}

/** Make the prop go towards its golem destination */
void AProps::AssembleGolem(USceneComponent* Target, FName SocketName, float Speed)
{
	bIsAssemblingGolem = true;
	SetGlow(0.0f);
	SetPhysicSimulation(false);
	Mesh->SetCollisionProfileName(TEXT("IgnoreAll")); // Avoid having the props collectable again by the magnet
	GolemAssemblyTarget = Target;
	GolemAssemblySocket = SocketName;
	GolemAssemblySpeed = Speed;
}

