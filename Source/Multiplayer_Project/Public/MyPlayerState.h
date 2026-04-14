// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_PROJECT_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	


public:

	UPROPERTY(Replicated,EditAnywhere, BlueprintReadWrite)
	int32 Lives = 3;

	UPROPERTY(Replicated,EditAnywhere, BlueprintReadWrite)
    int32 Scores = 0;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Value);
};
