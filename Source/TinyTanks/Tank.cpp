// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include <EnhancedInputSubsystems.h>

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	//Setup input mapping context
	if (auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(InputMove, ETriggerEvent::Triggered, this, &ATank::Move);
}

void ATank::Move(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();

	//moving forard/backward
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(MoveVector.Y * FVector::ForwardVector * DeltaTime * Speed, true);

	//turning
	AddActorLocalRotation(FRotator(0.0f, MoveVector.X * DeltaTime * 180.0f, 0.0f), true);
}
