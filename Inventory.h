#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "InventorySlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Inventory.generated.h"

UCLASS()
class MYPROJECT2_API UInventory : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	
public:
    UFUNCTION(BlueprintCallable)
    void InitializeGrid(int32 Rows, int32 InColumns, AMyProject2Character* InPlayer);

    UFUNCTION(BlueprintCallable)
    void CloseWidget();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetCoinText(const int32& Coin);

    UFUNCTION(BlueprintCallable)
	void UpdateInventoryUI();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
    int32 Columns;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* CoinText;	

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UGridPanel* ItemGrid;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UInventorySlot> InventorySlotClass;

    UPROPERTY(meta = (BindWidget))
    UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
    UCanvasPanel* CanvasPanel;

private:
    // ANPC 인스턴스에 대한 포인터
    AMyProject2Character* Player;
};
