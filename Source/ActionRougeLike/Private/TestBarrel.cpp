// Fill out your copyright notice in the Description page of Project Settings.


#include "TestBarrel.h"

// Sets default values
ATestBarrel::ATestBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

