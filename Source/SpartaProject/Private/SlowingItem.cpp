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
            // ĳ������ �ӵ��� ����
            PlayerCharacter->AddSlowing(SlowAmount);
        }

        DestroyItem();
    }
}
