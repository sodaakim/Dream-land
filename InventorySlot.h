#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ItemData.h"
#include "Components/Button.h"
#include "InventorySlot.generated.h"


UCLASS()
class MYPROJECT2_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable)
    void SetItemData(const FItemData& ItemData);

    UFUNCTION()
    void OnSlotClicked();

protected:

    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UImage* ItemImage;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemName;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemPrice;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemCount;

    UPROPERTY(meta = (BindWidget))
    UButton* ItemButton;

private:
    FItemData ItemData;	
};
