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
            GetRandomPointInVolume(),  // ���� ��ġ�� ����
            FRotator::ZeroRotator
        );
    }
}

void ASpawnMeteorVolume::StartWave(int32 Amount)
{
    SpawnCount = Amount;
    CurrentSpawnCount = 0;  // ���� ������ ���� �ʱ�ȭ
    if (Amount > 0)
    {
        GetWorldTimerManager().SetTimer(
            WaveSpawnTimerHandle,
            this,
            &ASpawnMeteorVolume::SpawnWaveItem,
            10.0f / Amount,  // ���� �ֱ� (��)
            true  // �ݺ� ����
        );
    }
    
}

void ASpawnMeteorVolume::SpawnWaveItem()
{
    if (CurrentSpawnCount >= SpawnCount - 1)  // ��ǥ ������ŭ �����ϸ� Ÿ�̸� ����
    {
        GetWorldTimerManager().ClearTimer(WaveSpawnTimerHandle);
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("Meteor Spawned"));
    if (ItemToSpawn)
    {
        SpawnItem();
        CurrentSpawnCount++;  // ���� ���� ���� ����
    }
}