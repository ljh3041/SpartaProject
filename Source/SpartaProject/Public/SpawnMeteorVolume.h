#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"       // �츮�� ������ ����ü
#include "SpawnMeteorVolume.generated.h"

class UBoxComponent;

UCLASS()
class SPARTAPROJECT_API ASpawnMeteorVolume : public AActor
{
	GENERATED_BODY()
	
public:
    ASpawnMeteorVolume();
    AActor* SpawnItem();


    void StartWave(int32 Amount);  // ���̺� ����
    void SpawnWaveItem();  // ���� ����
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    TSubclassOf<AActor> ItemToSpawn;  // ������ ������ (�� ����)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    int32 SpawnCount = 5;  // �� �� �������� (�⺻�� 5��)
    
    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void SpawnMultipleItems();


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    USceneComponent* Scene;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
    UBoxComponent* SpawningBox;

    FVector GetRandomPointInVolume() const;


    int32 CurrentSpawnCount;
    FTimerHandle WaveSpawnTimerHandle;



};
