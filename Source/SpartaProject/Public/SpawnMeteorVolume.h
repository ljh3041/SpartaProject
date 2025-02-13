#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawnRow.h"       // 우리가 정의한 구조체
#include "SpawnMeteorVolume.generated.h"

class UBoxComponent;

UCLASS()
class SPARTAPROJECT_API ASpawnMeteorVolume : public AActor
{
	GENERATED_BODY()
	
public:
    ASpawnMeteorVolume();
    AActor* SpawnItem();


    void StartWave(int32 Amount);  // 웨이브 시작
    void SpawnWaveItem();  // 개별 스폰
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    TSubclassOf<AActor> ItemToSpawn;  // 스폰할 아이템 (한 종류)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
    int32 SpawnCount = 5;  // 몇 개 스폰할지 (기본값 5개)
    
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
