// Fill out your copyright notice in the Description page of Project Settings.
#include "Barrel.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
ABarrel::ABarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USphereComponent>(TEXT("Scene Component"));
	RootComponent = SceneComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComp->SetupAttachment(SceneComp);
	SphereComp->SetCollisionProfileName("Barrel");

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	MeshComp->SetupAttachment(SceneComp);
	MeshComp->SetNotifyRigidBodyCollision(true);
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force Component"));
	RadialForceComp->SetupAttachment(SceneComp);
	RadialForceComp->ForceStrength = 20.0f;
	RadialForceComp->ImpulseStrength = 5000.0f;
	RadialForceComp->Radius = 1000.0f;
	RadialForceComp->bImpulseVelChange = true;
	
}

// Called when the game starts or when spawned
void ABarrel::BeginPlay()
{
	Super::BeginPlay();

	//MeshComp->OnComponentHit.AddDynamic(this, &ABarrel::OnHit);

}

// Called every frame
void ABarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrel::OnHit() {

	UE_LOG(LogTemp, Warning, TEXT("On Hit Component"));
}
