// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "Net/UnrealNetwork.h"

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerState, Lives);
	DOREPLIFETIME(AMyPlayerState, Scores);
}

void AMyPlayerState::AddScore(int32 Value)
{
	SetScore(GetScore() + Value);
}
