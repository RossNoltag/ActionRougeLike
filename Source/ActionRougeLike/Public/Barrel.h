// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrel.generated.h"

class UStaticMeshCompnent;
class URadialForceComponent;
class USphereComponent;
class USceneComponent;

UCLASS()
class ACTIONROUGELIKE_API ABarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComp;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	URadialForceComponent* RadialForceComp;

	UFUNCTION()
	void OnHit();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
