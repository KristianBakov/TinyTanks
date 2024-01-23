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
		GameOver(false);
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void ATinyTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATinyTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATinyTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

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

int32 ATinyTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}
