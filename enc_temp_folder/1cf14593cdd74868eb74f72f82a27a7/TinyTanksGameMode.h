// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TinyTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TINYTANKS_API ATinyTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
		void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

private:
	class ATank* Tank;
	class ATinyTanksPlayerController* TankPlayerController;

	float StartDelay = 3.f;
	void HandleGameStart();
};