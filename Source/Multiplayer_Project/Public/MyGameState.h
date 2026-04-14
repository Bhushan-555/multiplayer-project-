// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_PROJECT_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 TotalScore = 0;

	void AddTotalScore(int32 Value);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
