// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "Collectable.generated.h"


UCLASS()
class MULTIPLAYER_PROJECT_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Collision;

	
	UPROPERTY(EditAnywhere, Category = "Collectable")
	int32 ScoreValue = 10;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	bool bRespawns = true;

	UPROPERTY(EditAnywhere, Category = "Collectable")
	float RespawnDelay = 3.f;

	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void RespawnItem();

	FTimerHandle RespawnTimer;

	
};
