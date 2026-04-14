// Fill out your copyright notice in the Description page of Project Settings.


#include "MovablePlatform.h"
#include <Net/UnrealNetwork.h>
#include <ShObjIdl_core.h>
#include <Multiplayer_Project/Multiplayer_ProjectCharacter.h>

// Sets default values
AMovablePlatform::AMovablePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;
    SetReplicateMovement(true);

    PlatformState = EPlatformState::Idle;


    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMovablePlatform::BeginPlay()
{
	Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMovablePlatform::OnOverlapBegin);

    if (HasAuthority())
    {
        PointA = GetActorLocation();
        PointB = PointA + FVector(500.f, 0.f, 0.f);

        if (bAutoActivate)
        {
            PlatformState = EPlatformState::Moving;
        }
    }
}

// Called every frame
void AMovablePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


    if (HasAuthority())
    {
        if (PlatformState == EPlatformState::Moving)
        {
            FVector Current = GetActorLocation();
            FVector Target = PointB;

            FVector NewLocation = FMath::VInterpConstantTo(Current, Target, DeltaTime, MoveSpeed);

            SetActorLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);

            if (NewLocation.Equals(Target, 5.f))
            {
                PlatformState = EPlatformState::Paused;

                GetWorld()->GetTimerManager().SetTimer(
                    PauseTimer,
                    this,
                    &AMovablePlatform::ResumeMovement,
                    PauseDurationAtEndpoint,
                    false
                );
            }
        }
    }
}

void AMovablePlatform::ResumeMovement()
{
    if (!HasAuthority()) return;

    if (bLooping)
    {
        FVector Temp = PointA;
        PointA = PointB;
        PointB = Temp;

        PlatformState = EPlatformState::Moving;
    }
}

void AMovablePlatform::OnRep_PlatformState()
{
	UE_LOG(LogTemp, Warning, TEXT("Platform state changed"));
}

void AMovablePlatform::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMovablePlatform, PlatformState);

    DOREPLIFETIME(AMovablePlatform, PointA);
    DOREPLIFETIME(AMovablePlatform, PointB);
}

void AMovablePlatform::ActivatePlatform()
{
    if (!HasAuthority()) return;

    if (PlatformState == EPlatformState::Moving)
    {
        return; // already moving
    }

    PlatformState = EPlatformState::Moving;
}

void AMovablePlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!HasAuthority()) return;

    AMultiplayer_ProjectCharacter* Char = Cast<AMultiplayer_ProjectCharacter>(OtherActor);

    if (Char)
    {
        ActivatePlatform();
    }
}

