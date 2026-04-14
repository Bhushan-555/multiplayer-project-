// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MyPlayerState.h"
#include "MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/GameStateBase.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Collision
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName(TEXT("Trigger"));


}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACollectable::OnOverlapBegin);
}

// Called every frame
void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character)
	{
		return;
	}

	APlayerState* PS = Character->GetPlayerState();
	if (!PS)
	{
		return;
	}

	AMyPlayerState* MyPS = Cast<AMyPlayerState>(PS);
	if (!MyPS)
	{
		return;
	}

	//Player Score
	MyPS->AddScore(ScoreValue);

	//Total Score (GameState)
	AMyGameState* MyGS = GetWorld()->GetGameState<AMyGameState>();
	if (MyGS)
	{
		MyGS->AddTotalScore(ScoreValue);
	}

	// Disable collision (avoid double trigger)
	SetActorEnableCollision(false);

	//  Hide collectible
	SetActorHiddenInGame(true);

	// Respawn or Destroy
	if (bRespawns)
	{
		GetWorld()->GetTimerManager().SetTimer(
			RespawnTimer,
			this,
			&ACollectable::RespawnItem,
			RespawnDelay,
			false
		);
	}
	else
	{
		Destroy();
	}
}
void ACollectable::RespawnItem()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}




