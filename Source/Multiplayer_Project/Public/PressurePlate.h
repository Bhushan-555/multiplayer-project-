// Fill out your copyright notice in the Description page of Project Settings.

 #pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "PressurePlate.generated.h"


UCLASS()
class MULTIPLAYER_PROJECT_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;


	UPROPERTY(EditAnywhere)
	int32 RequiredPlayerCount = 1;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> LinkedGates;

	UPROPERTY(EditAnywhere)
	float CloseDelay = 2.f;


	int32 CurrentPlayerCount = 0;

	FTimerHandle CloseTimer;


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OpenGates();

	void CloseGates();
};
