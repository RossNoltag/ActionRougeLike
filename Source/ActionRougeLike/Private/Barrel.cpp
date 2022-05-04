// Fill out your copyright notice in the Description page of Project Settings.

//Code is perfect, configure settings if not working

#include "Barrel.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ABarrel::ABarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SceneComp = CreateDefaultSubobject<USphereComponent>(TEXT("Scene Component"));
	//RootComponent = SceneComp;
	//SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	//SphereComp->SetupAttachment(SceneComp);
	//SphereComp->SetCollisionProfileName("Barrel");

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force Component"));
	RadialForceComp->SetupAttachment(MeshComp);
	RadialForceComp->ForceStrength = 20.0f;
	RadialForceComp->ImpulseStrength = 3000.0f;
	RadialForceComp->Radius = 500.0f;
	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	
}

// Called when the game starts or when spawned
//void ABarrel::BeginPlay()
//{
//	Super::BeginPlay();

	//MeshComp->OnComponentHit.AddDynamic(this, &ABarrel::OnHit);
//}

// Called every frame
//void ABarrel::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}

void ABarrel::PostInitializeComponents() {

	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &ABarrel::OnActorHit);
}


void ABarrel::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	//UE_LOG(LogTemp, Warning, TEXT("Component Hit"));
	RadialForceComp->FireImpulse();
	UE_LOG(LogTemp, Warning, TEXT("Other Actor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 5.0f, true);
}
