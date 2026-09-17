// Fill out your copyright notice in the Description page of Project Settings.

#include "AsteroidSpawner.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAsteroidSpawner::AAsteroidSpawner()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Area"));
    SetRootComponent(SpawnArea);

    MinSpawnDelay = 0.5f;
    MaxSpawnDelay = 2.5f;
    RandomSpawnDelay = 0.0f;
}

// Called when the game starts or when spawned
void AAsteroidSpawner::BeginPlay()
{
    Super::BeginPlay();
    StartSpawnTimer();
}

FVector AAsteroidSpawner::GetRandomSpawnPoint()
{
    const FVector SpawnOrigin = SpawnArea->Bounds.Origin;
    const FVector SpawnLimits = SpawnArea->Bounds.BoxExtent;

    return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnLimits);
}

// Called every frame
void AAsteroidSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAsteroidSpawner::SpawnActors()
{
    if (!ActorToSpawn || !GetWorld())
    {
        return;
    }

    FActorSpawnParameters Parameters;
    Parameters.Owner = this;
    Parameters.Instigator = GetInstigator();
    Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    GetWorld()->SpawnActor<APickUpBase>(
        ActorToSpawn,
        GetRandomSpawnPoint(),
        FRotator::ZeroRotator,
        Parameters
    );

    StartSpawnTimer();
}

void AAsteroidSpawner::StartSpawnTimer()
{
    RandomSpawnDelay = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);

    GetWorld()->GetTimerManager().SetTimer(
        SpawnTimerHandle,
        this,
        &AAsteroidSpawner::SpawnActors,
        RandomSpawnDelay,
        false
    );
}