// Fill out your copyright notice in the Description page of Project Settings.

#include "Bar.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "PhysicsEngine/RadialForceComponent.h"



// Sets default values
ABar::ABar(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SceneComp->SetupAttachment(RootComponent);

	//SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	//SphereComp->SetupAttachment(SceneComp);
	//SphereComp->SetNotifyRigidBodyCollision(true);
	//SphereComp->SetSphereRadius(100.f);
	//SphereComp->OnComponentHit.AddDynamic(this, &ABar::OnCompHit);
	//SphereComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	//SphereComp->SetSimulatePhysics(true);
	//SphereComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));

	BarMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	BarMeshComp->SetupAttachment(SceneComp);
	

	CapsComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsComp->SetupAttachment(BarMeshComp);
	//CapsComp->AttachToComponent(BarMeshComp,FAttachmentTransformRules::KeepRelativeTransform);

	//CapsComp->SetupAttachment(BarMeshComp);
	CapsComp->SetNotifyRigidBodyCollision(true);
	CapsComp->OnComponentHit.AddDynamic(this, &ABar::OnCompHit);

	//BarMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	//BarMeshComp->SetupAttachment(SceneComp);
	//BarMeshComp->OnComponentHit.AddDynamic(this, &ABar::OnCompHit);

	//RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force Component"));
	//RadialForceComp->SetupAttachment(SphereComp);
	//RadialForceComp->ForceStrength = 2000.0f;
	//RadialForceComp->ImpulseStrength = 5000.0f;
	//RadialForceComp->Radius = 2000.0f;
	//RadialForceComp->bImpulseVelChange = true;
	//RadialForceComp->AddRadialImpulse(Start, Radius, Strength, RIF_Constant, true);
	//RadialForceComp->Transform

	// object array
	//Create an area  //RadialForceComp->SphereRadius
	//Sweep area// psweep radialForceComp->SpereRadius 
	//Add objects to array//  objectarray-sweep-radialForce->SphereRadius
	//loop through array for(objectArray){add radial impulse}
	//set off radial impulse to radial force

}

// Called when the game starts or when spawned
void ABar::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugSphere(GetWorld(), this->GetActorLocation(), Radius, 50, FColor::Orange, true);

	//UE_LOG( LogTemp, Warning, TEXT("Unscaled Sphere Radius: %f "), SphereComp->GetUnscaledSphereRadius());
	//UE_LOG(LogTemp, Warning, TEXT("Scaled Sphere Radius: %f "), SphereComp->GetScaledSphereRadius());
}


// Called every frame
void ABar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABar::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{	
	// If other actor exists // If other is not hitting itself// If other component exists
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
	//	UE_LOG( LogTemp, Warning, TEXT("Unscaled Sphere Radius: %f "));
		OnScreenDebugMsg(OtherActor);
		SweepArea();
	}
}

void ABar::SweepArea()
{
	const FVector Start = this->GetActorLocation();
	const FVector End = Start;
	TArray<FHitResult> HitArray;
	//float Radius = 500.f;
	float Strength = 1000.f;
	float StrengthOnSelf = 100.f;
	const FCollisionShape ShpereShape = FCollisionShape::MakeSphere(Radius);

	//DrawDebugSphere(GetWorld(), this->GetActorLocation(), 1000.f , 50, FColor::Orange, true);

	const bool bSweepHit = GetWorld()->SweepMultiByChannel(HitArray, Start, End, FQuat::Identity, ECC_WorldDynamic , ShpereShape);

	if (bSweepHit){
		for (const FHitResult HitResult : HitArray){
			//HitArray.Add(this->GetComponent<UStaticMeshComponent>());
			//UE_LOG(LogTemp, Warning, TEXT("Hit Result: %s "), *HitResult.Actor->GetName());//Check for sweeped actors

			UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((HitResult.GetActor())->GetRootComponent());
			
			if (MeshComp){
				//UE_LOG(LogTemp, Warning, TEXT("Checking for Mesh"));
				MeshComp->AddRadialImpulse(Start, Radius, Strength, RIF_Constant, true);
				this->BarMeshComp->AddRadialImpulse(Start, Radius, StrengthOnSelf, RIF_Constant, true);
				
				//Radius of blast
				// Inside sphere
				//Take sweep out of on hit... maybe not
				//Its registering whats in the sphere component
				//Using the spherecomponents radius to sweep

				//Possible mesh collission
			}
		}
	}
}

void ABar::OnScreenDebugMsg(AActor* OtherActor)
{
	if (GEngine){
		GEngine->AddOnScreenDebugMessage
		(-1, 5.0f, FColor::Green, (TEXT("I just hit: %s"), *OtherActor->GetName()));
	}
}

//UE_LOG(LogTemp, Warning, TEXT("Scaled Sphere Radius: %f "), *HitResult.Actor->GetName());