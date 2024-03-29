// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsPlayerInRange())
	{
		//look at player
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{
	if(!Tank) return;
	if (IsPlayerInRange() && Tank->bIsAlive)
	{
		Fire();
	}
}

bool ATower::IsPlayerInRange()
{
	if (!Tank) return false;
	float DistanceToPlayer = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	return DistanceToPlayer <= FireRange;
}
