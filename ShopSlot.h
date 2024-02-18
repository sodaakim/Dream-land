#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ItemData.h"
#include "Components/Button.h"
#include "ShopSlot.generated.h"

class ANPC;

UCLASS()
class MYPROJECT2_API UShopSlot : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SetItemData(const FItemData& ItemData);

    UFUNCTION(BlueprintCallable)
    void OnClick();

    void InitializeSlot(ANPC* InNPC, int32 InItemIndex);

    int32 ItemIndex; 

    UPROPERTY(meta = (BindWidget))
    UButton* ItemButton;


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

private:
    FItemData ItemData;	

    ANPC* NPC; 
};
