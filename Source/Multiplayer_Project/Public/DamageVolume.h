// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Containers/Map.h"
#include "DamageVolume.generated.h"

UCLASS()
class MULTIPLAYER_PROJECT_API ADamageVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:


    UPROPERTY(VisibleAnywhere)
    UBoxComponent* Box;

    UPROPERTY(EditAnywhere)
    float Damage = 10.f;

    UPROPERTY(EditAnywhere)
    float TickRate = 1.0f;

  
    TMap<AActor*, FTimerHandle> PlayerTimers;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void ApplyDamage(AActor* Player);


};
