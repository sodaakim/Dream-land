#include "InventorySlot.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

#include "Kismet/KismetSystemLibrary.h"

void UInventorySlot::SetItemData(const FItemData& NewItemData)
{
    ItemData = NewItemData; // 멤버 변수에 데이터 저장

    // UI 컴포넌트에 데이터 바인딩
    if (ItemName)
    {
        ItemName->SetText(FText::FromString(ItemData.Name));
    }
    if (ItemPrice)
    {
        ItemPrice->SetText(FText::AsNumber(ItemData.Price));
    }
    if (ItemCount)
    {
        ItemCount->SetText(FText::AsNumber(ItemData.Count));
    }

    if (ItemImage && !ItemData.ImagePath.IsEmpty())
    {
        // 이미지 경로로부터 텍스처 로드 (예시 경로: "/Game/Textures/MyItem")
        UTexture2D* ItemTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ItemData.ImagePath));
        if (ItemTexture)
        {
            ItemImage->SetBrushFromTexture(ItemTexture);
        }
    }
}
