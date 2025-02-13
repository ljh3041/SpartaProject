#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SlowingItem.generated.h"


UCLASS()
class SPARTAPROJECT_API ASlowingItem : public ABaseItem
{
	GENERATED_BODY()
public:
    ASlowingItem();

protected:
    // È¸º¹·®
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slowing")
    float SlowAmount;

    virtual void ActivateItem(AActor* Activator) override;
};
