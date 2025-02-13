#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ReverseControlItem.generated.h"

UCLASS()
class SPARTAPROJECT_API AReverseControlItem : public ABaseItem
{
	GENERATED_BODY()
public:
    AReverseControlItem();

protected:

    virtual void ActivateItem(AActor* Activator) override;
};
