#include "SlowingItem.h"
#include "MyCharacter.h"

ASlowingItem::ASlowingItem()
{
    SlowAmount = 20.0f;
    ItemType = "Slowing";
}

void ASlowingItem::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Activator))
        {
            // 캐릭터의 속도를 조절
            PlayerCharacter->AddSlowing(SlowAmount);
        }

        DestroyItem();
    }
}
