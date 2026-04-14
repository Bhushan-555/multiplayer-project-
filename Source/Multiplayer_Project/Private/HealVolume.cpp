// Fill out your copyright notice in the Description page of Project Settings.


#include "HealVolume.h"
#include <Multiplayer_Project/Multiplayer_ProjectCharacter.h>


// Sets default values
AHealVolume::AHealVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    RootComponent = Box;

    Box->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void AHealVolume::BeginPlay()
{
	Super::BeginPlay();

    Box->OnComponentBeginOverlap.AddDynamic(this, &AHealVolume::OnOverlapBegin);
    Box->OnComponentEndOverlap.AddDynamic(this, &AHealVolume::OnOverlapEnd);
	
}

// Called every frame
void AHealVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!HasAuthority()) return;

    if (OtherActor)
    {
        float CurrentTime = GetWorld()->GetTimeSeconds();

        // cooldown check
        if (LastHealTime.Contains(OtherActor))
        {
            float LastTime = LastHealTime[OtherActor];

            if (CurrentTime - LastTime < HealCooldownPerPlayer)
            {
                return; // cooldown active
            }
        }

        FTimerHandle Timer;

        GetWorld()->GetTimerManager().SetTimer(Timer, [this, OtherActor]()
            {
                ApplyHeal(OtherActor);
            }, TickInterval, true);

        PlayerTimers.Add(OtherActor, Timer);
    }
}

void AHealVolume::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!HasAuthority()) return;

    if (PlayerTimers.Contains(OtherActor))
    {
        GetWorld()->GetTimerManager().ClearTimer(PlayerTimers[OtherActor]);
        PlayerTimers.Remove(OtherActor);
    }
}

void AHealVolume::ApplyHeal(AActor* Player)
{
    if (!HasAuthority()) return;

    AMultiplayer_ProjectCharacter* Char = Cast<AMultiplayer_ProjectCharacter>(Player);

    if (Char)
    {
        Char->Server_Heal(HealPerTick);

        // last heal time update
        LastHealTime.Add(Player, GetWorld()->GetTimeSeconds());
    }
}

