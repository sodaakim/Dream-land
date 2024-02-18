#include "Shop.h"
#include "Components/GridSlot.h"
#include "ItemData.h"
#include "NPC.h"
#include "Components/Button.h"


void UShop::SetShopText(const FString& ShopName)
{
    if (ShopText) { ShopText->SetText(FText::FromString(ShopName)); }
}

void UShop::NativeConstruct()
{
    Super::NativeConstruct();

    if (CloseButton)
    {
        CloseButton->OnClicked.AddDynamic(this, &UShop::CloseWidget);
    }
}

void UShop::InitializeGrid(int32 Rows, int32 Columns, ANPC* InNPC)
{
    NPC = InNPC;

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
            if (NPC && NPC->ItemsForSale.IsValidIndex(ItemIndex))
            {
                UShopSlot* ItemSlot = CreateWidget<UShopSlot>(this, ShopSlotClass);
                if (!ItemSlot)
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to create ItemSlot widget."));
                    return;
                }
                if (ItemSlot)
                {
                    ItemSlot->SetItemData(NPC->ItemsForSale[ItemIndex]);
                    ItemSlot->InitializeSlot(NPC, ItemIndex); // 여기서 설정
                    UGridSlot* Slot = ItemGrid->AddChildToGrid(ItemSlot);
                    Slot->SetRow(Row);
                    Slot->SetColumn(Column);
                    UE_LOG(LogTemp, Log, TEXT("ItemSlot widget created successfully."));
                }
            }
        }
    }
}


void UShop::CloseWidget()
{
    NPC->CloseWidget();
    RemoveFromParent();

}