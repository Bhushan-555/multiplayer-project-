// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include <Net/UnrealNetwork.h>

void AMyGameState::AddTotalScore(int32 Value)
{
	TotalScore += Value;
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameState, TotalScore);
}
