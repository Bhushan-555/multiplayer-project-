// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathVolume.h"
#include <Multiplayer_Project/Multiplayer_ProjectCharacter.h>


// Sets default values
ADeathVolume::ADeathVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Box->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ADeathVolume::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ADeathVolume::OnOverlapBegin);
	
}

// Called every frame
void ADeathVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!HasAuthority()) return;

    AMultiplayer_ProjectCharacter* Char = Cast<AMultiplayer_ProjectCharacter>(OtherActor);

    if (Char)
    {
        if (bInstantKill)
        {
            // direct kill
            Char->Server_TakeDamage(9999.f);
        }
        else
        {
            // high damage but not instant
            Char->Server_TakeDamage(100.f);
        }
    }
}

