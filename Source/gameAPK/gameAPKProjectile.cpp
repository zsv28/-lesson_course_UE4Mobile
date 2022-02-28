// Copyright Epic Games, Inc. All Rights Reserve

#include "gameAPKProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Actor.h>
#include <Materials/MaterialInstanceDynamic.h>
#include <Materials/Material.h>

AgameAPKProjectile::AgameAPKProjectile() 
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AgameAPKProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AgameAPKProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());

		
		UMaterialInterface* Material = nullptr;
		UStaticMeshComponent* Component = Cast<UStaticMeshComponent>(OtherActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		if (Component)
		{
			Material = Component->GetMaterial(0);
		}
		UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(Material, this);
		if (Component)
		{
			Component->SetMaterial(0, DynamicMaterialInstance);
		}
		DynamicMaterialInstance->SetScalarParameterValue("ScalarParameter", 2.0f);
		DynamicMaterialInstance->SetTextureParameterValue("TextureParameter", NewTextureRef);
		DynamicMaterialInstance->SetVectorParameterValue("ColorParameter", FLinearColor(1, 0, 0, 1));
	}
	
	Destroy();
}