// Fill out your copyright notice in the Description page of Project Settings.


#include "TinyTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "TinyTanksPlayerController.h"

void ATinyTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (TankPlayerController)
		{
			TankPlayerController->SetPlayerEnabledState(false);
		}
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}

void ATinyTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATinyTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATinyTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (TankPlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Disabling input"));
		TankPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
			TankPlayerController,
			&ATinyTanksPlayerController::SetPlayerEnabledState,
			true);

		GetWorldTimerManager().SetTimer(
			PlayerEnableHandle,
			PlayerEnableDelegate,
			StartDelay,
			false);

	}
}
