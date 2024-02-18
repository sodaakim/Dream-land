#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ItemData.h"
#include "InventorySlot.generated.h"


UCLASS()
class MYPROJECT2_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SetItemData(const FItemData& ItemData);

protected:
    UPROPERTY(meta = (BindWidget))
    class UImage* ItemImage;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemName;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemPrice;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemCount;

private:
    FItemData ItemData;	
};
