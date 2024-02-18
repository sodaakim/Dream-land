#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ShopSlot.h"
#include "Shop.generated.h"

UCLASS()
class MYPROJECT2_API UShop : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;
	
public:
    UFUNCTION(BlueprintCallable, Category = "Shop")
    void SetShopText(const FString& ShopName);

    UFUNCTION(BlueprintCallable)
    void InitializeGrid(int32 Rows, int32 Columns, ANPC* InNPC);

    UFUNCTION(BlueprintCallable)
    void CloseWidget();

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UGridPanel* ItemGrid;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UShopSlot> ShopSlotClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* ShopText;	

    UPROPERTY(meta = (BindWidget))
    UButton* CloseButton;

private:
    // ANPC 인스턴스에 대한 포인터
    ANPC* NPC;
};
