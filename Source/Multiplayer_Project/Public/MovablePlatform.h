// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "MovablePlatform.generated.h"


UENUM(BlueprintType)
enum class EPlatformState : uint8
{
	Idle,
	Moving,
	Paused
};

UCLASS()
class MULTIPLAYER_PROJECT_API AMovablePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovablePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:


	UPROPERTY(ReplicatedUsing = OnRep_PlatformState)
	EPlatformState PlatformState;


	UPROPERTY(Replicated, EditAnywhere)
	FVector PointA;

	UPROPERTY(Replicated, EditAnywhere)
	FVector PointB;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 200.f;

	UPROPERTY(EditAnywhere)
	float PauseDurationAtEndpoint = 2.f;

	UPROPERTY(EditAnywhere)
	bool bLooping = true;

	FTimerHandle PauseTimer;


	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere)
	bool bAutoActivate = true;


	UFUNCTION()
	void ResumeMovement();

	UFUNCTION()
	void OnRep_PlatformState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void ActivatePlatform();


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
