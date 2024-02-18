#include "Inventory.h"
#include "Components/GridSlot.h"
#include "ItemData.h"
#include "MyProject2Character.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "MyDragDropOperation.h"


void UInventory::SetCoinText(const int32& Coin)
{
    if (CoinText) { CoinText->SetText(FText::FromString(FString::FromInt(Coin))); }
}

void UInventory::NativeConstruct()
{
    Super::NativeConstruct();

    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UInventory::CloseWidget);
    }
}

void UInventory::InitializeGrid(int32 Rows, int32 Columns, AMyProject2Character* InPlayer)
{
    Player = InPlayer;

    if (!ItemGrid)
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemGrid is NULL"));
        return;
    }

    // 그리드를 초기화하기 전에, 이전에 추가된 모든 자식을 제거합니다.
    ItemGrid->ClearChildren();

    for (int32 Row = 0; Row < Rows; Row++)
    {
        for (int32 Column = 0; Column < Columns; Column++)
        {
            int32 ItemIndex = Row * Columns + Column;
            if (Player && Player->InventoryItems.IsValidIndex(ItemIndex))
            {
                UInventorySlot* ItemSlot = CreateWidget<UInventorySlot>(this, InventorySlotClass);
                if (!ItemSlot)
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to create ItemSlot widget."));
                    return;
                }

                ItemSlot->SetItemData(Player->InventoryItems[ItemIndex]);                    
                UGridSlot* Slot = ItemGrid->AddChildToGrid(ItemSlot);
                Slot->SetRow(Row);
                Slot->SetColumn(Column);
                
                UE_LOG(LogTemp, Log, TEXT("ItemSlot widget created successfully."));
            }
        }
    }
}



void UInventory::CloseWidget()
{
    Player->CloseInventory();
    RemoveFromParent();

}
FReply UInventory::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    // 드래그를 시작하기 위해 DetectDrag를 호출합니다.
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
    }

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UInventory::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    FVector2D MousePosition = InMouseEvent.GetScreenSpacePosition();
    FVector2D WidgetPosition = InGeometry.GetAbsolutePosition();
    FVector2D Offset = MousePosition - WidgetPosition;
    
    UMyDragDropOperation* DragDropOperation = NewObject<UMyDragDropOperation>();

    // 드래그 중인 위젯을 설정합니다.
    DragDropOperation->DraggedWidget = this; // 또는 드래그하려는 구체적인 위젯을 지정합니다.
    DragDropOperation->DefaultDragVisual = this;

    // 드래그 오프셋을 계산합니다.
    FVector2D DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
    DragDropOperation->DragOffset = DragOffset;

    OutOperation = DragDropOperation;
}

bool UInventory::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    UMyDragDropOperation* MyDragDropOperation = Cast<UMyDragDropOperation>(InOperation);
    if (MyDragDropOperation)
    {
        // 드래그 오프셋을 고려하여 최종 드롭 위치를 계산합니다.
        FVector2D FinalDropPosition = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition()) - MyDragDropOperation->DragOffset;

        // 여기서 CanvasPanel은 인벤토리 UI 내에 있는 CanvasPanel의 참조입니다.
        // 캔버스 패널 슬롯에 위젯을 추가하고 위치를 설정합니다.
        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(MyDragDropOperation->DraggedWidget->Slot);
        if (CanvasSlot)
        {
            CanvasSlot->SetPosition(FinalDropPosition);
            return true;
        }
    }

    return false;
}

void UInventory::UpdateInventoryUI()
{
    // 인벤토리 그리드를 초기화하기 전에 모든 자식을 제거합니다.
    ItemGrid->ClearChildren();

    // Player의 InventoryItems 배열을 사용하여 인벤토리 UI 업데이트
    for (int32 Index = 0; Index < Player->InventoryItems.Num(); ++Index)
    {
        UInventorySlot* ItemSlot = CreateWidget<UInventorySlot>(this, InventorySlotClass);
        if (!ItemSlot)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create ItemSlot widget."));
            continue;
        }

        ItemSlot->SetItemData(Player->InventoryItems[Index]);
        UGridSlot* Slot = ItemGrid->AddChildToGrid(ItemSlot);
        // 계산된 행과 열을 사용하여 슬롯 위치 설정
        int32 Row = Index / Columns; // Columns는 인벤토리 그리드의 열 수를 나타냅니다.
        int32 Column = Index % Columns;
        Slot->SetRow(Row);
        Slot->SetColumn(Column);
    }
}


