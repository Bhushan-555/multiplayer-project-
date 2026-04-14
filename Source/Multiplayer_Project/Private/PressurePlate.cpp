// Fill out your copyright notice in the Description page of Project Settings.

 #include "PressurePlate.h"
#include <Multiplayer_Project/Multiplayer_ProjectCharacter.h>
#include <Gate.h>


// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
	
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	 if (!HasAuthority()) return;

	 AMultiplayer_ProjectCharacter* Char = Cast<AMultiplayer_ProjectCharacter>(OtherActor);

	 if (Char)
	 {
		 CurrentPlayerCount++;

		 // Timer cancel 
		 GetWorld()->GetTimerManager().ClearTimer(CloseTimer);

		 // Only open if enough players
		 if (CurrentPlayerCount >= RequiredPlayerCount)
		 {
			 OpenGates();
		 }
	 }
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!HasAuthority()) return;

	AMultiplayer_ProjectCharacter* Char = Cast<AMultiplayer_ProjectCharacter>(OtherActor);

	if (Char)
	{
		CurrentPlayerCount--;

		if (CurrentPlayerCount <= 0)
		{
			GetWorld()->GetTimerManager().SetTimer(
				CloseTimer,
				this,
				&APressurePlate::CloseGates,
				CloseDelay,
				false
			);
		}
	}
}

void APressurePlate::OpenGates()
{
	for (AActor* GateActor : LinkedGates)
	{
		AGate* Gate = Cast<AGate>(GateActor);

		if (Gate)
		{
			Gate->OpenGate();
		}
	}
}

void APressurePlate::CloseGates()
{
	//  FINAL CHECK 
	if (CurrentPlayerCount >= RequiredPlayerCount)
	{
		return;
	}

	for (AActor* GateActor : LinkedGates)
	{
		AGate* Gate = Cast<AGate>(GateActor);

		if (Gate)
		{
			Gate->CloseGate();
		}
	}
}




