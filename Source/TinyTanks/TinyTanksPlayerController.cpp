// Fill out your copyright notice in the Description page of Project Settings.


#include "TinyTanksPlayerController.h"
#include "GameFramework/Pawn.h"

void ATinyTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if(bPlayerEnabled) 		UE_LOG(LogTemp, Warning, TEXT("Enabling input"));
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}
