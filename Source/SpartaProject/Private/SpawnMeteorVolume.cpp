#include "SpawnMeteorVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"


ASpawnMeteorVolume::ASpawnMeteorVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);

    ItemToSpawn = nullptr;

}


AActor* ASpawnMeteorVolume::SpawnItem()
{
    if (!ItemToSpawn) return nullptr;

    AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
        ItemToSpawn,
        GetRandomPointInVolume(),
        FRotator::ZeroRotator
    );

    return SpawnedActor;
}

FVector ASpawnMeteorVolume::GetRandomPointInVolume() const
{
    const FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
    const FVector BoxOrigin = SpawningBox->GetComponentLocation();

    return BoxOrigin + FVector(
        FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
        FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
        FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
    );
}

void ASpawnMeteorVolume::SpawnMultipleItems()
{
    if (!ItemToSpawn || SpawnCount <= 0) return;

    for (int32 i = 0; i < SpawnCount; i++)
    {
        GetWorld()->SpawnActor<AActor>(
            ItemToSpawn,
            GetRandomPointInVolume(),  // 랜덤 위치에 생성
            FRotator::ZeroRotator
        );
    }
}

void ASpawnMeteorVolume::StartWave(int32 Amount)
{
    SpawnCount = Amount;
    CurrentSpawnCount = 0;  // 현재 스폰된 개수 초기화
    if (Amount > 0)
    {
        GetWorldTimerManager().SetTimer(
            WaveSpawnTimerHandle,
            this,
            &ASpawnMeteorVolume::SpawnWaveItem,
            10.0f / Amount,  // 스폰 주기 (초)
            true  // 반복 실행
        );
    }
    
}

void ASpawnMeteorVolume::SpawnWaveItem()
{
    if (CurrentSpawnCount >= SpawnCount - 1)  // 목표 개수만큼 스폰하면 타이머 종료
    {
        GetWorldTimerManager().ClearTimer(WaveSpawnTimerHandle);
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("Meteor Spawned"));
    if (ItemToSpawn)
    {
        SpawnItem();
        CurrentSpawnCount++;  // 현재 스폰 개수 증가
    }
}