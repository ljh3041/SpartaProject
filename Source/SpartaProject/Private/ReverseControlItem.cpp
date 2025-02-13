#include "ReverseControlItem.h"
#include "MyCharacter.h"


AReverseControlItem::AReverseControlItem()
{
    ItemType = "ReverseControl";
}

void AReverseControlItem::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Activator))
        {
            // ĳ������ �ӵ��� ����
            PlayerCharacter->ReverseControl();
        }

        DestroyItem();
    }
}
