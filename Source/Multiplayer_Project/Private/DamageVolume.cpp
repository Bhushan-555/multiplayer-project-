// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageVolume.h"
#include <Multiplayer_Project/Multiplayer_ProjectCharacter.h>

// Sets default values
ADamageVolume::ADamageVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Box->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ADamageVolume::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &ADamageVolume::OnOverlapBegin);
	
	Box->OnComponentEndOverlap.AddDynamic(this, &ADamageVolume::OnOverlapEnd);
}

// Called every frame
void ADamageVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADamageVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority()) return;

	if (OtherActor)
	{
		FTimerHandle Timer;

		GetWorld()->GetTimerManager().SetTimer(Timer, [this, OtherActor]()
			{
				ApplyDamage(OtherActor);
			}, TickRate, true);

		PlayerTimers.Add(OtherActor, Timer);
	}
}

void ADamageVolume::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!HasAuthority()) return;

	if (PlayerTimers.Contains(OtherActor))
	{
		GetWorld()->GetTimerManager().ClearTimer(PlayerTimers[OtherActor]);
		PlayerTimers.Remove(OtherActor);
	}
}

void ADamageVolume::ApplyDamage(AActor* Player)
{
	if (!HasAuthority()) return;

	AMultiplayer_ProjectCharacter* Char = Cast<AMultiplayer_ProjectCharacter>(Player);

	if (Char)
	{
		Char->Server_TakeDamage(Damage);
	}
}

