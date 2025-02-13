#include "CoinItem.h"
#include "Engine/World.h"
#include "MyGameState.h"

ACoinItem::ACoinItem()
{
    // ���� �⺻���� 0���� ����
    PointValue = 0;
    ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);
    // �÷��̾� �±� Ȯ��
    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (UWorld* World = GetWorld())
        {
            if (AMyGameState* GameState = World->GetGameState<AMyGameState>())
            {
                GameState->AddScore(PointValue);
                GameState->OnCoinCollected();
            }
        }
        // �θ� Ŭ���� (BaseItem)�� ���ǵ� ������ �ı� �Լ� ȣ��
        DestroyItem();
    }
}

