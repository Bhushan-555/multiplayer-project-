// Fill out your copyright notice in the Description page of Project Settings.


#include "Gate.h"

// Sets default values
AGate::AGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGate::BeginPlay()
{
	Super::BeginPlay();

	ClosedPosition = GetActorLocation();

	// Gate open & direction
	OpenPosition = ClosedPosition - FVector(0.f, 0.f, 300.f);
	
}

// Called every frame
void AGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Opening
	if (bIsOpening)
	{
		FVector Current = GetActorLocation();

		FVector NewLocation = FMath::VInterpConstantTo(Current, OpenPosition, DeltaTime, OpenSpeed);

		SetActorLocation(NewLocation, true);

		if (NewLocation.Equals(OpenPosition, 1.f))
		{
			bIsOpening = false;
		}
	}

	// Closing
	if (bIsClosing)
	{
		FVector Current = GetActorLocation();

		FVector NewLocation = FMath::VInterpConstantTo(Current, ClosedPosition, DeltaTime, OpenSpeed);

		SetActorLocation(NewLocation, true);

		if (NewLocation.Equals(ClosedPosition, 1.f))
		{
			bIsClosing = false;
		}
	}

}

void AGate::OpenGate()
{

	bIsOpening = true;
	bIsClosing = false;
}

void AGate::CloseGate()
{

	if (bStaysOpenOnceActivated) return;

	bIsClosing = true;
	bIsOpening = false;
}

