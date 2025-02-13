#include "HealingItem.h"
#include "MyCharacter.h"

AHealingItem::AHealingItem()
{
    HealAmount = 20.0f;
    ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Activator))
        {
            // 캐릭터의 체력을 회복
            PlayerCharacter->AddHealth(HealAmount);
        }

        DestroyItem();
    }
}