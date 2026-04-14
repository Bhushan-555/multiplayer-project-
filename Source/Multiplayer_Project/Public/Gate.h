// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gate.generated.h"

UCLASS()
class MULTIPLAYER_PROJECT_API AGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	
	UPROPERTY(EditAnywhere)
	float OpenSpeed = 200.f;

	UPROPERTY(EditAnywhere)
	bool bStaysOpenOnceActivated = false;

	// Positions
	FVector ClosedPosition;
	FVector OpenPosition;

	//  State
	bool bIsOpening = false;
	bool bIsClosing = false;

	// FUNCTIONS
	void OpenGate();

	void CloseGate();
};
