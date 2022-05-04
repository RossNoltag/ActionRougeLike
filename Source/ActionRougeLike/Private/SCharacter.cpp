// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "RInteractionComponent.h"

// Sets default values
ASCharacter::ASCharacter(){
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Constructor method/function, loaded first when file is called
	//This where we initialize our variables

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<URInteractionComponent>("Interaction Component");

	// bOrientRotationToMovement = alows the character to turn and run in the left or right direction
	// if bUseCOntrollerRotationYaw is true this wont come into effect
	GetCharacterMovement()->bOrientRotationToMovement = true;

	
	//if true the pawn will turn on the yaw axis with the camera, so i want it off
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay(){
	Super::BeginPlay();
	//Begin play is called when everything is initialized
	//Can possibly initialize timers etc
}


// Called every frame
void ASCharacter::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	DebugLines();
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookAround", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASCharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
}

void ASCharacter::MoveForward(float Value){	
	//Getting the Controlls rotation and setting Pitch and Roll
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	//Want to add input from player, transalte to movment
	//To move the Character in the forward of the Controller(Controller class)
	AddMovementInput(ControlRotation.Vector(), Value);
}

void ASCharacter::MoveRight(float Value){
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	//Rotation matrix is to get the right vector, of the Controller
	FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
	//Axis
	//X=Forward (Red)
	//Y=Right	(Green)
	//Z=Up		(Blue)
}

/*
void ASCharacter::MoveJump(){	
	UE_LOG(LogTemp, Warning, TEXT("Jump"));
	Jump();
	//AddMovementInput(GetActorForwardVector(), Value);
}
*/

void ASCharacter::PrimaryAttack(){
	PlayAnimMontage(PrimaryAttackAnim);
    GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed,0.2f);
	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
	//FVector MeshLocation = GetMesh()->GetSocketLocation("Muzzle_01");
}

// Timer to slow down projectile launch to give the animation time to catchup
void ASCharacter::PrimaryAttack_TimeElapsed(){
	UE_LOG(LogTemp, Warning, TEXT("TimeElapse Called"));

	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	//Spawn From Location
	FTransform SpawmTM = FTransform(GetControlRotation(), HandLocation);
	//Set Spawn Parameters
	FActorSpawnParameters SpawnParams;
	//What to do with collision - The rules for collision
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	SpawnParams.Instigator = this;
	
	//Spawn Projectile
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawmTM, SpawnParams);
}

void ASCharacter::PrimaryInteract(){
	if (InteractionComp)
	{
		//UE_LOG(LogTemp, Warning, TEXT("PrimaryInteract"));
		InteractionComp->PrimaryInteract();
	}
}

void ASCharacter::DebugLines(){
	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

