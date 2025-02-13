#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"


UCLASS()
class SPARTAPROJECT_API AMyGameState : public AGameState
{
	GENERATED_BODY()
public:

    virtual void BeginPlay() override;

    AMyGameState();
    // ���� ������ �����ϴ� ����
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
    int32 Score;

    // ���� �������� ������ ���� ����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
    int32 SpawnedCoinCount;
    // �÷��̾ ������ ���� ����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
    int32 CollectedCoinCount;

    // �� ������ �����Ǵ� �ð� (�� ����)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
    float LevelDuration;
    // ���� ���� ���� ���� �ε���
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
    int32 CurrentLevelIndex;
    // ��ü ������ ����
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
    int32 MaxLevels;
    // ���� ���� �� �̸� �迭. ���� �ִ� �ε����� ���ʴ�� ����
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
    TArray<FName> LevelMapNames;


    // �� ������ ������ ������ �ð��� �帣���� �����ϴ� Ÿ�̸�
    FTimerHandle LevelTimerHandle;
    FTimerHandle HUDUpdateTimerHandle;

    // ���� ������ �д� �Լ�
    UFUNCTION(BlueprintPure, Category = "Score")
    int32 GetScore() const;

    // ������ �߰����ִ� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Score")
    void AddScore(int32 Amount);

    // ������ ������ ������ �� (��� ���� ����) ����Ǵ� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Level")
    void OnGameOver();



    // ������ ������ ��, ������ ���� �� Ÿ�̸� ����
    void StartLevel();
    // ���� ���� �ð��� ����Ǿ��� �� ȣ��
    void OnLevelTimeUp();
    // ������ �ֿ��� �� ȣ��
    void OnCoinCollected();
    // ������ ���� �����ϰ� ���� ������ �̵�
    void EndLevel();
    void UpdateHUD();



    //���⼭���� ���� ����
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
    int32 CurrentWave;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
    int32 MaxWavesPerLevel; // �� ������ 3���� ���̺�
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave")
    float WaveDuration; // �� ���̺�� 10��

    //���̺� ����
    void StartWave();
    //���̺� ��
    void EndWave();
    FTimerHandle WaveTimerHandle;
};
